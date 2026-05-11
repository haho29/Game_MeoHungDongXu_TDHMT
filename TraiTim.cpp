#include "TraiTim.h"
#include "VeHinh.h"
#include <graphics.h>

void TraiTim::ve(int x, int y) {
    int color = RED;

    VeHinh::veDuongTron(x - 4, y - 3, 4, color);
    VeHinh::toMauDeQuy(x - 4, y - 3, color, color);

    VeHinh::veDuongTron(x + 4, y - 3, 4, color);
    VeHinh::toMauDeQuy(x + 4, y - 3, color, color);

    VeHinh::veDuongThang(x - 8, y - 1, x + 8, y - 1, color);
    VeHinh::veDuongThang(x + 8, y - 1, x, y + 9, color);
    VeHinh::veDuongThang(x, y + 9, x - 8, y - 1, color);
    VeHinh::toMauDeQuy(x, y + 1, color, color);
}
