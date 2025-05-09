#include "k_near.h"
#include "log.h"
#include <string>
#include <cmath>
#include <vector>

void match_sizes(
    uint8_t* img1, int w1, int h1,
    uint8_t* img2, int w2, int h2,
    uint8_t*& out1, uint8_t*& out2,
    int& new_w, int& new_h
) {
    new_w = w1;
    new_h = h1;
    out1 = img1;

    out2 = new uint8_t[w1 * h1]();

    int dx = w1 - w2;
    int dy = h1 - h2;

    int x_offset_src = std::max(0, -dx / 2);
    int y_offset_src = std::max(0, -dy / 2);

    int x_offset_dst = std::max(0, dx / 2);
    int y_offset_dst = std::max(0, dy / 2);

    int copy_w = std::min(w1, w2);
    int copy_h = std::min(h1, h2);

    for (int y = 0; y < copy_h; ++y) {
        for (int x = 0; x < copy_w; ++x) {
            out2[(y + y_offset_dst) * w1 + (x + x_offset_dst)] =
                img2[(y + y_offset_src) * w2 + (x + x_offset_src)];
        }
    }
}
