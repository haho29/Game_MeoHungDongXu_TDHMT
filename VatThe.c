#include "VatThe.h"
#include "VeHinh.h"
#include <graphics.h>

void veDongXu(int x, int y, int banKinh, int diemCong) {
    int border_col = COLOR(235, 140, 20); // Dark orange/gold for depth
    int main_col = COLOR(255, 200, 30);   // Bright yellow
    int inner_col = COLOR(255, 220, 80);  // Lighter yellow
    int paw_col = COLOR(240, 160, 25);    // Paw print color
    int pointColor = COLOR(116, 199, 172);

    // Outer circle (with depth)
    veDuongTron(x, y + 1, banKinh, border_col); // Bottom shadow edge
    veDuongTron(x, y, banKinh, border_col);
    toMauDeQuy(x, y, main_col, border_col);
    
    // Inner ring
    if (banKinh > 6) {
        veDuongTron(x, y, banKinh - 2, inner_col);
    }
    
    // Paw print in the center
    int py = y + 1;
    my_bar(x-2, py, x+2, py+2, paw_col);       // Main pad
    my_bar(x-1, py-1, x+1, py, paw_col);
    if (banKinh > 8) {
        my_bar(x-4, py-3, x-3, py-1, paw_col); // Left toe
        my_bar(x+3, py-3, x+4, py-1, paw_col); // Right toe
        my_bar(x-1, py-4, x+1, py-2, paw_col); // Top toe
    }
    
    // Draw points text next to it
    if (diemCong > 0) {
        char diemStr[10];
        sprintf(diemStr, "+%d", diemCong);
        setbkcolor(COLOR(25, 15, 45)); 
        setcolor(pointColor);
        settextstyle(SMALL_FONT, HORIZ_DIR, 5); 
        settextjustify(LEFT_TEXT, CENTER_TEXT);
        outtextxy(x + banKinh + 5, y, diemStr);
    }
}

void veBom(int x, int y, double scale) {
    int bodyColor = COLOR(30, 30, 35);    // Darker black/grey
    int borderColor = COLOR(15, 15, 20);
    int fuseBase = COLOR(120, 120, 120);  // Grey
    int fuse = COLOR(180, 120, 50);       // Brown
    int spark1 = COLOR(255, 255, 0);      // Bright Yellow
    int spark2 = COLOR(255, 100, 0);      // Orange
    int white = COLOR(240, 240, 245);
    int black = COLOR(20, 20, 20);

    int p1x, p1y, p2x, p2y;
    
    #define DRAW_SCALED_BAR(x1, y1, x2, y2, col) do { \
        p1x = x1; p1y = y1; p2x = x2; p2y = y2; \
        PhepCoGian2D(&p1x, &p1y, x, y, scale, scale); \
        PhepCoGian2D(&p2x, &p2y, x, y, scale, scale); \
        my_bar(p1x, p1y, p2x, p2y, col); \
    } while(0)
    
    #define DRAW_SCALED_LINE(x1, y1, x2, y2, col) do { \
        p1x = x1; p1y = y1; p2x = x2; p2y = y2; \
        PhepCoGian2D(&p1x, &p1y, x, y, scale, scale); \
        PhepCoGian2D(&p2x, &p2y, x, y, scale, scale); \
        veDuongThang(p1x, p1y, p2x, p2y, col); \
    } while(0)

    // Fuse base
    DRAW_SCALED_BAR(x - 3, y - 16, x + 3, y - 12, fuseBase);
    
    // Fuse line
    DRAW_SCALED_LINE(x, y - 16, x + 4, y - 20, fuse);
    DRAW_SCALED_LINE(x + 4, y - 20, x + 6, y - 22, fuse);
    
    // Spark
    DRAW_SCALED_BAR(x + 4, y - 25, x + 8, y - 21, spark1);
    DRAW_SCALED_BAR(x + 5, y - 24, x + 7, y - 22, spark2);
    
    // Main Body
    int r = (int)(14 * scale);
    veDuongTron(x, y, r, borderColor);
    toMauDeQuy(x, y, bodyColor, borderColor);
    
    // Shine / Highlight (3D effect)
    p1x = x - 5; p1y = y - 5; PhepCoGian2D(&p1x, &p1y, x, y, scale, scale);
    veDuongTron(p1x, p1y, (int)(2 * scale), white);
    toMauDeQuy(p1x, p1y, white, white);
    
    // Skull
    DRAW_SCALED_BAR(x - 5, y - 1, x + 5, y + 3, white);
    DRAW_SCALED_BAR(x - 4, y - 3, x + 4, y - 1, white);
    DRAW_SCALED_BAR(x - 3, y + 3, x + 3, y + 7, white);
    
    // Eyes
    DRAW_SCALED_BAR(x - 3, y, x - 1, y + 2, black);
    DRAW_SCALED_BAR(x + 1, y, x + 3, y + 2, black);
    
    // Nose
    DRAW_SCALED_BAR(x, y + 3, x, y + 3, black);
    
    // Teeth lines
    DRAW_SCALED_LINE(x - 1, y + 5, x - 1, y + 6, black);
    DRAW_SCALED_LINE(x + 1, y + 5, x + 1, y + 6, black);
}

void veXuongCa(int x, int y, double angle) {
    int boneCol = COLOR(245, 245, 250); // Bright white-grey
    int shadowCol = COLOR(180, 180, 190); // Shadow for depth
    int eye = COLOR(50, 50, 50);
    
    int p1x, p1y, p2x, p2y;
    
    #define DRAW_ROTATED_LINE(x1, y1, x2, y2, col) do { \
        p1x = x1; p1y = y1; p2x = x2; p2y = y2; \
        PhepQuay2D(&p1x, &p1y, x, y, angle); \
        PhepQuay2D(&p2x, &p2y, x, y, angle); \
        veDuongThang(p1x, p1y, p2x, p2y, col); \
    } while(0)
    
    // Spine
    DRAW_ROTATED_LINE(x - 6, y - 6, x + 8, y + 8, boneCol);
    DRAW_ROTATED_LINE(x - 5, y - 6, x + 9, y + 8, shadowCol); 
    
    // Rib 1
    DRAW_ROTATED_LINE(x - 5, y + 1, x + 1, y - 5, boneCol);
    DRAW_ROTATED_LINE(x - 4, y + 1, x + 2, y - 5, shadowCol);
    // Rib 2
    DRAW_ROTATED_LINE(x - 1, y + 5, x + 5, y - 1, boneCol);
    DRAW_ROTATED_LINE(x, y + 5, x + 6, y - 1, shadowCol);
    // Rib 3
    DRAW_ROTATED_LINE(x + 3, y + 9, x + 9, y + 3, boneCol);
    DRAW_ROTATED_LINE(x + 4, y + 9, x + 10, y + 3, shadowCol);
    
    // Head (Top-Left)
    p1x = x - 9; p1y = y - 9; PhepQuay2D(&p1x, &p1y, x, y, angle);
    veDuongTron(p1x, p1y, 5, shadowCol); // Shadow layer
    
    p2x = x - 10; p2y = y - 10; PhepQuay2D(&p2x, &p2y, x, y, angle);
    veDuongTron(p2x, p2y, 5, boneCol); // Top layer
    toMauDeQuy(p2x, p2y, boneCol, boneCol);
    
    // Eye
    int ex1 = x - 12, ey1 = y - 12; PhepQuay2D(&ex1, &ey1, x, y, angle);
    my_bar(ex1 - 1, ey1 - 1, ex1 + 1, ey1 + 1, eye); // Draw eye using small bar at rotated center
    
    // Tail
    DRAW_ROTATED_LINE(x + 8, y + 8, x + 12, y + 6, boneCol);
    DRAW_ROTATED_LINE(x + 8, y + 8, x + 6, y + 12, boneCol);
    DRAW_ROTATED_LINE(x + 12, y + 6, x + 6, y + 12, boneCol);
    
    int tx = x + 9, ty = y + 9; PhepQuay2D(&tx, &ty, x, y, angle);
    my_bar(tx - 1, ty - 1, tx + 1, ty + 1, shadowCol); // Fill tail roughly
}

void veKhiNangLuong(int x, int y, double angle, double scale) {
    int coreCol = COLOR(180, 240, 255);
    int auraCol1 = COLOR(100, 200, 255);
    int auraCol2 = COLOR(50, 150, 255);
    
    int p1x, p1y, p2x, p2y;
    
    // Lõi phát sáng
    int rCore = (int)(8 * scale);
    veDuongTron(x, y, rCore, coreCol);
    toMauDeQuy(x, y, coreCol, coreCol);
    
    // Vòng năng lượng xoay
    for(int i = 0; i < 4; i++) {
        double currentAngle = angle + i * 1.5708; // 90 do
        p1x = x + (int)(15 * scale); p1y = y;
        p2x = x; p2y = y + (int)(15 * scale);
        
        PhepQuay2D(&p1x, &p1y, x, y, currentAngle);
        PhepQuay2D(&p2x, &p2y, x, y, currentAngle);
        
        veDuongTron(p1x, p1y, (int)(3 * scale), auraCol1);
        toMauDeQuy(p1x, p1y, auraCol1, auraCol1);
        
        veDuongTron(p2x, p2y, (int)(2 * scale), auraCol2);
        toMauDeQuy(p2x, p2y, auraCol2, auraCol2);
    }
}

void veNamCham(int x, int y, double angle) {
    int redU = COLOR(220, 50, 50);
    int grayPole = COLOR(200, 200, 200);
    
    int p1x, p1y, p2x, p2y;
    
    // Ve hinh chu U cua nam cham (Ve bang cac doan thang day dac de lap day khoang trong do toMauDeQuy hoi kho dung neu xoay)
    // De gian luoc va an toan khi xoay, ta ve bang tap hop cac diem
    for(int i = -10; i <= 10; i++) {
        for(int j = -12; j <= 5; j++) {
            // Tao hinh chu U
            if(i < -4 || i > 4 || j > 0) {
                if(i >= -10 && i <= 10 && j >= -12 && j <= 12) {
                    p1x = x + i; p1y = y + j;
                    PhepQuay2D(&p1x, &p1y, x, y, angle);
                    
                    if(j > 5) {
                        my_putpixel(p1x, p1y, grayPole); // Cuc tu
                    } else {
                        my_putpixel(p1x, p1y, redU); // Than nam cham
                    }
                }
            }
        }
    }
}

void veDongHo(int x, int y, double angle) {
    int gold = COLOR(255, 215, 0);
    int blueBg = COLOR(50, 150, 255);
    int white = COLOR(255, 255, 255);
    int shadow = COLOR(200, 150, 0);

    // Vẽ vành ngoài đồng hồ
    veDuongTron(x, y + 1, 14, shadow);
    veDuongTron(x, y, 14, gold);
    toMauDeQuy(x, y, gold, gold);
    
    // Mặt đồng hồ màu xanh nhạt
    veDuongTron(x, y, 11, blueBg);
    toMauDeQuy(x, y, blueBg, blueBg);

    int p1x, p1y, p2x, p2y;
    
    // Kim phút
    p1x = x; p1y = y;
    p2x = x; p2y = y - 8;
    PhepQuay2D(&p2x, &p2y, x, y, angle * 2.0);
    veDuongThang(p1x, p1y, p2x, p2y, white);
    veDuongThang(p1x+1, p1y, p2x+1, p2y, white);
    
    // Kim giờ
    p2x = x + 5; p2y = y + 5;
    PhepQuay2D(&p2x, &p2y, x, y, angle * 0.5);
    veDuongThang(p1x, p1y, p2x, p2y, white);
    veDuongThang(p1x+1, p1y+1, p2x+1, p2y+1, white);
    
    // Dấu chấm tâm
    veDuongTron(x, y, 2, white);
    toMauDeQuy(x, y, white, white);
}
