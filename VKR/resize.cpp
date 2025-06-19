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
)
/*Функция подгоняет два изображения разных размеров под один общий размер. Центрирует меньшее изображения на новом фоне.

Параметры:
  - img1(uint8_t*): Вектор пикселей первого изображения.
  - w1(int): Ширина первого изображения.
  - h1(int): Высота первого изображения.
  - img2(uint8_t*): Вектор пикселей второго изображения.
  - w2(int): Ширина второго изображения.
  - h2(int): Высота второго изображения.
  - out1(uint8_t*&): Ссылка на указатель, куда будет сохранено изображения img1.
  - out2(uint8_t*&): Ссылка на указатель, куда будет создано новое изображение.
  - new_w(int&): Ссылка на новую ширину.
  - new_h(int&): Ссылка на новую высоту.*/

  {
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
