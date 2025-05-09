#include "k_near.h"
#include "log.h"
#include <string>
#include <cmath>
#include <vector>

using namespace std;

void k_near(const uint8_t* input, int width, int height, uint8_t* output, int new_width, int new_height, double scale) {
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

