#include "TraiTim.h"
#include "VeHinh.h"
#include <graphics.h>

void veTraiTim(int x, int y) {
    int color = COLOR(243, 139, 168); // Catppuccin Red (Hong do)

    veDuongTron(x - 4, y - 3, 4, color);
    toMauDeQuy(x - 4, y - 3, color, color);

    veDuongTron(x + 4, y - 3, 4, color);
    toMauDeQuy(x + 4, y - 3, color, color);

    veDuongThang(x - 8, y - 1, x + 8, y - 1, color);
    veDuongThang(x + 8, y - 1, x, y + 9, color);
    veDuongThang(x, y + 9, x - 8, y - 1, color);
    toMauDeQuy(x, y + 1, color, color);
}
