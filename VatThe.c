#include "VatThe.h"
#include "VeHinh.h"
#include <graphics.h>

void veDongXu(int x, int y) {
    int color = COLOR(249, 226, 175); // Gold
    int innerColor = COLOR(250, 179, 135); // Peach
    int textColor = COLOR(17, 17, 27); // Dark text
    
    // Outer circle
    veDuongTron(x, y, 12, color);
    toMauDeQuy(x, y, color, color);
    
    // Inner circle
    veDuongTron(x, y, 9, innerColor);
    
    // Text
    setbkcolor(color);
    setcolor(textColor);
    settextstyle(SMALL_FONT, HORIZ_DIR, 4);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    outtextxy(x, y, (char*)"$");
}

void veBom(int x, int y) {
    int fuseColor = COLOR(250, 179, 135); // Peach
    int bodyColor = COLOR(69, 71, 90);    // Dark surface
    int highlightColor = COLOR(166, 173, 200); // Overlay

    // Fuse (ngoi no)
    veDuongThang(x, y - 14, x + 5, y - 18, fuseColor);

    // Body (than bom)
    veDuongTron(x, y, 14, highlightColor);
    toMauDeQuy(x, y, bodyColor, highlightColor);
}

void veXuongCa(int x, int y) {
    int color = COLOR(148, 226, 213); // Teal
    int i;

    // Xuong song (spine)
    veDuongThang(x - 15, y, x + 8, y, color);
    
    // Xuong nhanh (ribs)
    for(i = -8; i <= 4; i += 6)
        veDuongThang(x + i, y - 6, x + i, y + 6, color);

    // Dau ca (Fish head) - Triangle
    veDuongThang(x + 8, y, x + 18, y - 6, color);
    veDuongThang(x + 18, y - 6, x + 18, y + 6, color);
    veDuongThang(x + 18, y + 6, x + 8, y, color);
    toMauDeQuy(x + 15, y, color, color);
}
