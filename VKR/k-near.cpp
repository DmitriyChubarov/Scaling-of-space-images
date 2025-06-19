#include "k_near.h"
#include "log.h"
#include <string>
#include <cmath>
#include <vector>

using namespace std;

void k_near(const uint8_t* input, int width, int height, uint8_t* output, int new_width, int new_height, double scale) {
    /*Функция масштабирования изображения методом ближайшего соседа.

    Параметры:
      - input(const uint8*): Указатель на исходное изображение.
      - width(int): Ширина исходного изображения.
      - height(int): Высота исходного изображения.
      - output(uint8*): Буфер для результата масштабирования.
      - new_width(int): Ширина выходного изображения.
      - new_height(int): Высота выходного изображения.
      - scale(double): Коэффициент масштабирования.*/

    Log::print("Начинается процесс интерполяции билинейным методом!");
    for (int i = 0; i < new_height; ++i) {
        for (int j = 0; j < new_width; ++j) {
            int x = min(static_cast<int>(round(static_cast<float>(i) / scale)), height - 1);
            int y = min(static_cast<int>(round(static_cast<float>(j) / scale)), width - 1);
            output[i * new_width + j] = input[x * width + y];
        }
    }
    Log::print("Процесс интерполяции методом ближйшего соседа завершен успешно!");
}

