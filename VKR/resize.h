#ifndef RESIZE_H
#define RESIZE_H

#include <string>

void match_sizes(
    uint8_t* img1, int w1, int h1,
    uint8_t* img2, int w2, int h2,
    uint8_t*& out1, uint8_t*& out2,
    int& new_w, int& new_h
);

#endif // RESIZE_H
