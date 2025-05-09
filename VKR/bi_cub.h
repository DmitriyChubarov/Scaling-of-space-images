#ifndef BI_CUB_H
#define BI_CUB_H

#include <iostream>

float cubicInterpolate(float p0, float p1, float p2, float p3, float t);
void bi_cub(const uint8_t* input, int width, int height, uint8_t* output, int new_width, int new_height, double scale);

#endif // BI_CUB_H
