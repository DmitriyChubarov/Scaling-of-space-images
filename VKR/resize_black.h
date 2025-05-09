#ifndef RESIZE_BLACK_H
#define RESIZE_BLACK_H

#include <string>

void pad_with_black(uint8_t* src, int src_w, int src_h, uint8_t* dst, int dst_w, int dst_h);

void match_sizes_(
    uint8_t* img1, int w1, int h1,
    uint8_t* img2, int w2, int h2,
    uint8_t*& out1, uint8_t*& out2,
    int& new_w, int& new_h);

#endif // RESIZE_BLACK_H
