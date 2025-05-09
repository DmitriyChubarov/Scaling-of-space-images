#include <vector>
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include "metrix.h"
#include "log.h"


double computeMSE(const std::vector<uint8_t>& original, const std::vector<uint8_t>& interpolated, int width, int height) {
    if (original.size() != interpolated.size()) {
        throw std::invalid_argument("Размеры изображений не совпадают!");
    }

    double mse = 0.0;
    int pixels = width * height;

    for (int i = 0; i < pixels; ++i) {
        double diff = static_cast<double>(original[i]) - static_cast<double>(interpolated[i]);
        mse += diff * diff;
    }

    return mse / pixels;
}

double computePSNR(double mse, double max_pixel) {
    if (mse == 0) return INFINITY; // если изображение идентичны
    return 10.0 * log10((max_pixel * max_pixel) / mse);
}


double computeMAE(const std::vector<uint8_t>& original, const std::vector<uint8_t>& interpolated, int width, int height) {
    if (original.size() != interpolated.size()) {
        throw std::invalid_argument("Размеры изображений не совпадают!");
    }

    double mae = 0.0;
    int pixels = width * height;

    for (int i = 0; i < pixels; ++i) {
        mae += std::abs(static_cast<double>(original[i]) - static_cast<double>(interpolated[i]));
    }

    return mae / pixels;
}
