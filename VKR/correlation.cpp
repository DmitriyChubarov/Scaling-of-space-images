#include "correlation.h"
#include "log.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

double correlation(const vector<uint8_t>& x, const vector<uint8_t>& y) {
    /*Функция вычисления нормализованного коэффициента корреляции между двумя изображениями.

    Параметры:
      - x(const vector<uint8_t>&): Вектор яркостей пикселей первого изображения.
      - x(const vector<uint8_t>&): Вектор яркостей пикселей второго изображения.

    Возвращает:
      - (double): Значение корреляции.*/

    Log::print("Начинается процесс вычисления корреляции!");
    int n = x.size();
    double sum_x = 0.0, sum_y = 0.0;

    for (int i = 0; i < n; ++i) {
        sum_x += x[i];
        sum_y += y[i];
    }

    double mean_x = sum_x / n;
    double mean_y = sum_y / n;

    double numerator = 0.0;
    double denom_x = 0.0;
    double denom_y = 0.0;

    for (int i = 0; i < n; ++i) {
        double dx = x[i] - mean_x;
        double dy = y[i] - mean_y;
        numerator += dx * dy;
        denom_x += dx * dx;
        denom_y += dy * dy;
    }

    double denominator = sqrt(denom_x) * sqrt(denom_y);
    if (denominator == 0) return 0.5; // избегаем деления на 0

    Log::print("Процесс вычисления корреляции завершен успешно!");

    return (numerator / denominator + 1.0) / 2.0;
}


