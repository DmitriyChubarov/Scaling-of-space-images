#ifndef METRIX_H
#define METRIX_H

#include <vector>
#include <cmath>
#include <algorithm>
#include <stdexcept>

double computeMSE(const std::vector<uint8_t>& original, const std::vector<uint8_t>& interpolated, int width, int height);

double computePSNR(double mse, double max_pixel = 255.0);

double computeMAE(const std::vector<uint8_t>& original, const std::vector<uint8_t>& interpolated, int width, int height);

#endif // METRIX_H
