#include "bi_cub.h"
#include "log.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

template <typename T>
const T &qBound(const T & min, const T &val, const T & max)
/*Функция-шаблон, которая ограничевает значения по границам.

Параметры:
  - min(T): Минимально допустимое значение.
  - val(T): Минимально текущее значение.
  - mac(T): Максимально допустимое значение.

Возвращает:
  - val(T): Возвращает текущее значение, если оно удовлетворяет условию. Иначе возвращает ближайшую границу.*/

{
    return (val < min) ? min : (max < val) ? max : val;
}

float cubicInterpolate(float p0, float p1, float p2, float p3, float t) {
    /*Функция кубической интерполяции между четырьмя точками.

    Параметры:
      - p0, p1, p2, p3(float): Значения в четырёх соседних точках.
      - t(float): Интерполяционный коэффициент.

    Возвращает:
      - (float): Значение, полученное по формуле бикубической интерполяции.*/

    return p1 + 0.5f * t * (p2 - p0 + t * (2*p0 - 5*p1 + 4*p2 - p3 + t * (3*(p1 - p2) + p3 - p0)));
}

void bi_cub(const uint8_t* input, int width, int height, uint8_t* output, int new_width, int new_height, double scale) {
    /*Функция масштабирования изображения методом бикубической интерполяции

    Параметры:
      - input(const uint8*): Указатель на исходное изображение.
      - width(int): Ширина исходного изображения.
      - height(int): Высота исходного изображения.
      - output(uint8*): Буфер для результата масштабирования.
      - new_width(int): Ширина выходного изображения.
      - new_height(int): Высота выходного изображения.
      - scale(double): Коэффициент масштабирования.*/

    Log::print("Начинается процесс интерполяции бикубическим методом!");
    for (int i = 0; i < new_height; ++i) {
        for (int j = 0; j < new_width; ++j) {
            float x = static_cast<float>(i) / scale;
            float y = static_cast<float>(j) / scale;

            int xi = static_cast<int>(floor(x));
            int yi = static_cast<int>(floor(y));

            float dx = x - xi;
            float dy = y - yi;

            int x0 = max(0, xi - 1);
            int x1 = xi;
            int x2 = min(height - 1, xi + 1);
            int x3 = min(height - 1, xi + 2);

            int y0 = max(0, yi - 1);
            int y1 = yi;
            int y2 = min(width - 1, yi + 1);
            int y3 = min(width - 1, yi + 2);

            float I1 = cubicInterpolate(input[x0 * width + y0], input[x1 * width + y0], input[x2 * width + y0], input[x3 * width + y0], dx);
            float I2 = cubicInterpolate(input[x0 * width + y1], input[x1 * width + y1], input[x2 * width + y1], input[x3 * width + y1], dx);
            float I3 = cubicInterpolate(input[x0 * width + y2], input[x1 * width + y2], input[x2 * width + y2], input[x3 * width + y2], dx);
            float I4 = cubicInterpolate(input[x0 * width + y3], input[x1 * width + y3], input[x2 * width + y3], input[x3 * width + y3], dx);

            float value = cubicInterpolate(I1, I2, I3, I4, dy);
            output[i * new_width + j] = static_cast<uint8_t>(qBound(round(value), 0.0f, 255.0f));
        }
    }
    Log::print("Процесс интерполяции бикубическим методом завершен успешно!");
}
