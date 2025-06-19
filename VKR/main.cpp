#include "stb_image.h"
#include "stb_image_write.h"
#include "log.h"
#include "bi_cub.h"
#include "bi_lin.h"
#include "k_near.h"
#include "metrix.h"
#include "resize.h"
#include "correlation.h"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <filesystem>
#include <limits.h>
#include <unistd.h>

using namespace std;

const string visible_path = "/home/sers/Desktops/Desktop1/Chubarov_astra/RGRTU/NIR_2/pictures/Visible_real_2560.jpg";
const string ir_original_path = "/home/sers/Desktops/Desktop1/Chubarov_astra/RGRTU/NIR_2/pictures/IR_real_1280.jpg";
const string ir_new_path = "/home/sers/Desktops/Desktop1/Chubarov_astra/RGRTU/NIR_2/pictures/IR_real_1280_new.jpg";

uint8_t* load_image(const string& path, int& w, int& h, int& c) {
    /*Функция, которая загружает изображение в градациях серого.

    Параметры:
      - path(const string&): Путь к изображению на диске.
      - w(int&): Переменная для ширины изображения. Заполняется внутри функции.
      - h(int&): Переменная для высоты изображения. Заполняется внутри функции.
      - c(int&): Переменная для количества каналов. Заполняется внутри функции.

    Возвращает:
      - img(uint8*): Указатель на загруженное изображение в формате 8-бит на пиксель. Возвращает nullptr, если не уадлось загрузить изображение.*/

    uint8_t* img = stbi_load(path.c_str(), &w, &h, &c, 1);
    if (!img) {
        Log::print("Отказано в доступе к " + path + "!");
    } else {
        Log::print("Доступ к " + path + " получен!");
    }
    return img;
}

void free_images(initializer_list<uint8_t*> images) {
    /*Функция, которая освобождает память, выделенную под изображения.

    Параметры:
      - images(initializer_list<uint8_t*>): Список указателей на изображения, память у которых необходимо освободить.*/

    for (auto img : images) {
        if (img) stbi_image_free(img);
    }
}

int main() {
    /*Главная управляющая функция*/

    double scale = 1.01;
    vector<double> cor = {0, 0.0001};

    int x;
    cout << "Введите значение:" << "\n" << "1 - бикубическая интерполяция" << "\n" << "2 - билинейная интерполяция" << "\n" << "3 - метод ближайшего соседа" << "\n";
    cin >> x;

    while (cor.back() > cor[cor.size() - 2]) {
        Log::print(string(135, '-'));
        Log::print("Подготовка запуска процесса интерполяции!");

        int width, height, channels;
        uint8_t* img = load_image(ir_original_path, width, height, channels);
        if (!img) return -1;

        Log::print("Установлен масштаб процесса интерполяции: " + to_string(scale));
        int new_width = static_cast<int>(width * scale);
        int new_height = static_cast<int>(height * scale);
        vector<uint8_t> new_img(new_width * new_height);

        if (x == 1){
            bi_cub(img, width, height, new_img.data(), new_width, new_height, scale);
        } else if (x == 2){
            bi_lin(img, width, height, new_img.data(), new_width, new_height);
        }else if (x == 3){
            k_near(img, width, height, new_img.data(), new_width, new_height, scale);
        }else {
            Log::print("Оператор ввёл некорректное значение");
            return 0;
        }

        stbi_write_jpg(ir_new_path.c_str(), new_width, new_height, 1, new_img.data(), 90);
        stbi_image_free(img);

        Log::print("Подготовка запуска процесса мастшабирования!");
        int w1, h1, c1, w2, h2, c2;
        uint8_t* img1 = load_image(visible_path, w1, h1, c1);
        uint8_t* img2 = load_image(ir_new_path, w2, h2, c2);
        if (!img1 || !img2) return -1;

        uint8_t *out1 = nullptr, *out2 = nullptr;
        int new_w, new_h;
        match_sizes(img1, w1, h1, img2, w2, h2, out1, out2, new_w, new_h);

        stbi_write_jpg(ir_new_path.c_str(), new_w, new_h, 1, out2, 90);
        if (out1 != img1) delete[] out1;
        if (out2 != img2) delete[] out2;
        free_images({img1, img2});

        Log::print("Подготовка запуска процесса корреляции!");
        int w1_, h1_, c1_, w2_, h2_, c2_;
        uint8_t* img1_ = load_image(visible_path, w1_, h1_, c1_);
        uint8_t* img2_ = load_image(ir_new_path, w2_, h2_, c2_);

        if (!img1_ || !img2_) return 1;
        if (w1_ != w2_ || h1_ != h2_) {
            Log::print("Размеры изображений не совпадают");
            free_images({img1_, img2_});
            return 1;
        }

        int total_pixels = w1_ * h1_;
        vector<uint8_t> vec1(img1_, img1_ + total_pixels);
        vector<uint8_t> vec2(img2_, img2_ + total_pixels);

        double result = correlation(vec1, vec2);
        Log::print("Коэффициент корреляции: " + to_string(result));

        free_images({img1_, img2_});
        cor.push_back(result);
        scale += 0.01;
    }

    Log::print("Итоговый коэффициент корреляции: " + to_string(cor[cor.size() - 2]));
    Log::print("Итоговый масштаб: " + to_string(scale - 0.02));
    Log::print(string(135, '-'));


    return 0;
}

