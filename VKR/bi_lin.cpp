#include "bi_lin.h"
#include "log.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void bi_lin(const uint8_t* input, int width, int height, uint8_t* output, int new_width, int new_height)
{
 Log::print("Начинается процесс интерполяции билинейным методом!");
 float scale_x = static_cast<float>(width) / new_width;
 float scale_y = static_cast<float>(height) / new_height;

 for (int y = 0; y < new_height; ++y){
     for (int x = 0; x < new_width; ++x){

         //вычисление координат в исходном снимке
         float src_x = x * scale_x;
         float src_y = y * scale_y;

         //определяем 4 ближайших пикселя
         int x0 = static_cast<int>(src_x);
         int y0 = static_cast<int>(src_y);
         int x1 = min(x0 + 1, width - 1); //проверка на выход за границы
         int y1 = min(y0 + 1, height + 1);

         //дробные части координат

         float dx = src_x - x0;
         float dy = src_y - y0;

         //значения 4 пикселей в ЧБ
         float i00 = input[y0 * width + x0];
         float i10 = input[y0 * width + x1];
         float i01 = input[y1 * width + x0];
         float i11 = input[y1 * width + x1];

         //билинейная интерполяция
         float val = (i00 * (1 - dx) + i10 * dx) * (1-dy) + (i01 * (1-dx) + i11 * dx) * dy;

         //Приводти к uint8_t
         output[y * new_width + x] = static_cast<uint8_t>(round(val));
     }
 }
 Log::print("Процесс интерполяции билинейным методом завершен успешно!");
}
