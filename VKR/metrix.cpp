//#include <vector>
//#include <cmath>
//#include <algorithm>
//#include <stdexcept>
//#include "metrix.h"
//#include "log.h"


//double computeMSE(const std::vector<uint8_t>& original, const std::vector<uint8_t>& interpolated, int width, int height) {
//    /*Функция, которая вычисляет среднеквадратичную ошибку.

//    Параметры:
//      - original(const std::vector<uint8_t>&): Вектор пикселей исходного изображения.
//      - interpolated(const std::vector<uint8_t>&): Вектор пикселей интерполированного изображения.
//      - width(int): Ширина изображения.
//      - height(int): Высота изображения.

//    Возвращает:
//      - (double): Значение среднеквадратичной ошибки между двумя снимками.*/

//    if (original.size() != interpolated.size()) {
//        throw std::invalid_argument("Размеры изображений не совпадают!");
//    }

//    double mse = 0.0;
//    int pixels = width * height;

//    for (int i = 0; i < pixels; ++i) {
//        double diff = static_cast<double>(original[i]) - static_cast<double>(interpolated[i]);
//        mse += diff * diff;
//    }

//    return mse / pixels;
//}

//double computePSNR(double mse, double max_pixel) {
//    /*Функция, которая вычисляет пиковое отношение сигнала к шуму.

//    Параметры:
//      - mse(double): Среднеквадратичная ошибка.
//      - max_pixel(double): Максимальное возможное значение яркости пикселя.

//    Возвращает:
//      - (double): Значение среднеквадратичной ошибки между двумя снимками.*/

//    if (mse == 0) return INFINITY; // если изображение идентичны
//    return 10.0 * log10((max_pixel * max_pixel) / mse);
//}


//double computeMAE(const std::vector<uint8_t>& original, const std::vector<uint8_t>& interpolated, int width, int height) {
//    /*Функция, которая вычисляет среднеабсолютную ошибку.

//    Параметры:
//      - original(const std::vector<uint8_t>&): Вектор пикселей исходного изображения.
//      - interpolated(const std::vector<uint8_t>&): Вектор пикселей интерполированного изображения.
//      - width(int): Ширина изображения.
//      - height(int): Высота изображения.

//    Возвращает:
//      - (double): Значение среднеквадратичной ошибки между двумя снимками.*/

//    if (original.size() != interpolated.size()) {
//        throw std::invalid_argument("Размеры изображений не совпадают!");
//    }

//    double mae = 0.0;
//    int pixels = width * height;

//    for (int i = 0; i < pixels; ++i) {
//        mae += std::abs(static_cast<double>(original[i]) - static_cast<double>(interpolated[i]));
//    }

//    return mae / pixels;
//}
