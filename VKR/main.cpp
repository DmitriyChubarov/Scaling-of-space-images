#include "stb_image.h"
#include "stb_image_write.h"
#include "log.h"
#include "bi_cub.h"
#include "bi_lin.h"
#include "k_near.h"
#include "metrix.h"
#include "resize.h"
#include "correlation.h"
#include <string>
#include <vector>
#include <chrono>
#include <filesystem>
#include <limits.h>
#include <unistd.h>

using namespace std;

string get_path(){
    char buffer[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len != -1) {
        buffer[len] = '\0';
        return string(buffer);
    }
    return 0;
}

int main() {
    double scale = 1.01;
    vector<double> cor = {0, 0.0001};
    while (cor[cor.size() - 1] > cor[cor.size() - 2]){
            //interpolation
            Log::print("-------------------------------------------------------------------------------------------------------------------------------------------");
            Log::print("Подготовка запуска процесса интерполяции!");
            int width, height, channels;
            uint8_t* img = stbi_load("/Users/dmitrij/Documents/C++/Scaling_images/pictures/IR_real_1280.jpg", &width, &height, &channels, 1);

            if (!img) {
                Log::print("Отказано в доступе к снимку в ИК-диапазоне!");
                return -1;
            } else {
                Log::print("Доступ к снимку в ИК-диапазоне получен!");
            }

            Log::print("Установлен масштаб процесса интерполяции: " + to_string(scale) + ".");
            int new_width = static_cast<int>(width * scale);
            int new_height = static_cast<int>(height * scale);
            vector<uint8_t> new_img(new_width * new_height);

//            bi_cub(img, width, height, new_img.data(), new_width, new_height, scale);
            bi_lin(img, width, height, new_img.data(), new_width, new_height);
//            k_near(img, width, height, new_img.data(), new_width, new_height, scale);

            stbi_write_jpg("/Users/dmitrij/Documents/C++/Scaling_images/pictures/IR_real_1280_new.jpg", new_width, new_height, 1, new_img.data(), 90);
            stbi_image_free(img);

            //resize
            Log::print("Подготовка запуска процесса мастшабирования!");
            int w1, h1, c1;
            int w2, h2, c2;

            uint8_t* img1 = stbi_load("/Users/dmitrij/Documents/C++/Scaling_images/pictures/Visible_real_2560.jpg", &w1, &h1, &c1, 1);
            uint8_t* img2 = stbi_load("/Users/dmitrij/Documents/C++/Scaling_images/pictures/IR_real_1280_new.jpg", &w2, &h2, &c2, 1);

            if (!img1 or !img2) {
                Log::print("Отказано в доступе к снимкам!");
                return -1;
            } else {
                Log::print("Доступ к снимкам получен!");
            }

            uint8_t *out1 = nullptr, *out2 = nullptr;
            int new_w, new_h;

            match_sizes(img1, w1, h1, img2, w2, h2, out1, out2, new_w, new_h);

            stbi_write_jpg("/Users/dmitrij/Documents/C++/Scaling_images/pictures/IR_real_1280_new.jpg", new_w, new_h, 1, out2, 90);

            if (out1 != img1) delete[] out1;
            if (out2 != img2) delete[] out2;

            stbi_image_free(img1);
            stbi_image_free(img2);

            //correlation
            int w1_, h1_, c1_;
            int w2_, h2_, c2_;

            uint8_t* img1_ = stbi_load("/Users/dmitrij/Documents/C++/Scaling_images/pictures/Visible_real_2560.jpg", &w1_, &h1_, &c1_, 1);
            uint8_t* img2_ = stbi_load("/Users/dmitrij/Documents/C++/Scaling_images/pictures/IR_real_1280_new.jpg", &w2_, &h2_, &c2_, 1);

            if (!img1_ || !img2_) {
                Log::print("Отказано в доступе к снимкам!");
                return 1;
            }

            // Проверка на совпадение размеров
            if (w1_ != w2_ || h1_ != h2_) {
                Log::print("Размеры изображений не совпадают");
                stbi_image_free(img1_);
                stbi_image_free(img2_);
                return 1;
            }

            int total_pixels = w1_ * h1_;
            vector<uint8_t> vec1(img1_, img1_ + total_pixels);
            vector<uint8_t> vec2(img2_, img2_ + total_pixels);

            double result = correlation(vec1, vec2);
            Log::print("Коэффициент корреляции: " + to_string(result));

            stbi_image_free(img1_);
            stbi_image_free(img2_);

            cor.push_back(result);
            scale += 0.01;
            Log::print("-------------------------------------------------------------------------------------------------------------------------------------------");
    }

    Log::print("Итоговый оэффициент корреляции: " + to_string(cor[cor.size() - 2]));
    Log::print("Итоговый масштаб: " + to_string(scale - 0.02));
    Log::print("-------------------------------------------------------------------------------------------------------------------------------------------");
    return 0;
}
