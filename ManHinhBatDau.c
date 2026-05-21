#include "ManHinhBatDau.h"
#include "VeHinh.h"
#include "VatThe.h"
#include "Meo.h"
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>

void docDataShop(int *skin, int *phuKien, int *xu) {
    *skin = 0; *phuKien = 0; *xu = 0;
    FILE *f = fopen("shop_data.txt", "r");
    if(f) {
        fscanf(f, "%d %d %d", xu, skin, phuKien);
        fclose(f);
    }
}

void luuDataShop(int skin, int phuKien, int xu) {
    FILE *f = fopen("shop_data.txt", "w");
    if(f) {
        fprintf(f, "%d %d %d\n", xu, skin, phuKien);
        fclose(f);
    }
}

int hienThiManHinhBatDau(int *skin, int *phuKien, int *xu) {
    docDataShop(skin, phuKien, xu);
    
    int bgGrassTop = COLOR(50, 220, 0); 
    int bgGrassDark = COLOR(0, 150, 0); 
    int fenceWood = COLOR(116, 70, 49); 
    int fenceLine = COLOR(85, 45, 30);  
    int titleWood = COLOR(137, 180, 250); 
    int titleShadow = COLOR(100, 130, 200);
    int btnYellow = COLOR(249, 226, 175); 
    int btnYellowShadow = COLOR(200, 180, 140);
    int btnGreen = COLOR(166, 227, 161); 
    int btnGreenShadow = COLOR(130, 180, 120);
    int titleBlue = COLOR(245, 194, 231); 
    int white = COLOR(255, 255, 255);
    int goldGlow = COLOR(255, 215, 0); 
    
    int selected = 0; // 0: Bat Dau, 1: Thoat
    int trang = 0;
    int i, px, py, x, y;
    static int starFrame = 0;
    double t = 0.0;
    
    while (1) {
        setactivepage(trang);
        t += 0.05;
        
        // 1. GRADIENT SKY (Bau troi chuyen mau tuyet dep)
        for (int gy = 0; gy < 400; gy += 10) {
            int r = 15 + (gy * 35 / 400);
            int g = 20 + (gy * 60 / 400);
            int b = 50 + (gy * 90 / 400);
            my_bar(0, gy, 1000, gy + 10, COLOR(r, g, b));
        }
        
        // Ngoi sao lap lanh
        starFrame++;
        for(x = 25; x < 1000; x += 65) {
            for(y = 20; y < 350; y += 45) {
                int phase = (x * 17 + y * 23 + starFrame) % 20;
                if(phase < 2) my_bar(x, y, x+3, y+3, white); 
                else if(phase < 5) my_bar(x+1, y+1, x+2, y+2, COLOR(200, 200, 240)); 
            }
        }
        
        // Mat trang nho lap lanh (Goc trai)
        int mx = 200, my = 130, mr = 35;
        // Hào quang co giãn theo thời gian t
        int glow1 = mr + 8 + (int)(2 * sin(t * 3.0));
        int glow2 = mr + 16 + (int)(4 * sin(t * 2.0));
        
        for(int dy = -glow2; dy <= glow2; dy++) {
            for(int dx = -glow2; dx <= glow2; dx++) {
                int distSq = dx*dx + dy*dy;
                if(distSq <= mr*mr) {
                    my_putpixel(mx+dx, my+dy, COLOR(255, 255, 240)); // Lõi mặt trăng trắng sáng
                } else if (distSq <= glow1*glow1) {
                    my_putpixel(mx+dx, my+dy, COLOR(255, 240, 180)); // Viền vàng sáng
                } else if (distSq <= glow2*glow2 && (dx+dy + starFrame/3)%2 == 0) {
                    my_putpixel(mx+dx, my+dy, COLOR(200, 180, 120)); // Hào quang lấp lánh
                }
            }
        }
        
        // Tia sáng lấp lánh (Lens flare chéo)
        int flareLen = 25 + (int)(8 * sin(t * 8.0));
        veDuongThang(mx - flareLen, my, mx + flareLen, my, white);
        veDuongThang(mx, my - flareLen, mx, my + flareLen, white);
        
        // 2. FENCE (Hang rao)
        for(i = -10; i < 1000; i += 60) {
            my_bar(i, 360, i+25, 450, fenceWood);
            veDuongThang(i+25, 360, i+25, 450, fenceLine);
        }
        my_bar(0, 380, 1000, 395, fenceWood); 
        my_bar(0, 420, 1000, 435, fenceWood);
        veDuongThang(0, 395, 1000, 395, fenceLine);
        veDuongThang(0, 435, 1000, 435, fenceLine);
        
        // 3. GRASS (Bai co)
        my_bar(0, 440, 1000, 700, bgGrassTop);
        for(px = 10; px < 1000; px += 50) {
            for(py = 460; py < 700; py += 35) {
                if((px+py)%70 == 0) my_bar(px, py, px+6, py+6, bgGrassDark);
            }
        }
        
        // Fractal Bụi Cỏ (Làm nền cho mèo)
        veDuongKoch(50, 460, 450, 460, COLOR(30, 160, 60), 4);
        
        // 4. MEO (Chinh dien ben trai, tren bai co)
        veMeoCoPhuKien(250, 480, false, t, *skin, *phuKien, false);
        
        // 5. TITLE (Ben phai)
        my_bar(596, 56, 954, 204, COLOR(50, 30, 10)); // Vien ngoai
        my_bar(600, 60, 950, 200, titleShadow);       // Bong
        my_bar(600, 53, 950, 190, titleWood);         // Nen go
        my_bar(610, 65, 620, 75, COLOR(50, 50, 70)); my_bar(930, 65, 940, 75, COLOR(50, 50, 70)); // Dinh oc
        my_bar(610, 168, 620, 178, COLOR(50, 50, 70)); my_bar(930, 168, 940, 178, COLOR(50, 50, 70));
        
        setbkcolor(titleWood); 
        settextjustify(CENTER_TEXT, CENTER_TEXT);
        
        settextstyle(BOLD_FONT, HORIZ_DIR, 6); 
        setcolor(COLOR(50, 40, 20)); outtextxy(778, 103, (char*)"MEO");
        setcolor(COLOR(255, 220, 50)); outtextxy(775, 100, (char*)"MEO");
        
        settextstyle(BOLD_FONT, HORIZ_DIR, 3);
        setcolor(COLOR(50, 40, 20)); outtextxy(777, 153, (char*)"HUNG DONG XU");
        setcolor(titleBlue); outtextxy(775, 150, (char*)"HUNG DONG XU");
        
        // 6. BUTTONS & HOVER
        px = mousex(); py = mousey();
        int hoverStart = (px >= 625 && px <= 925 && py >= 270 && py <= 350);
        int hoverThoat = (px >= 625 && px <= 925 && py >= 390 && py <= 470);
        if(hoverStart) selected = 0; else if(hoverThoat) selected = 1;
        
        // BUTTON BAT DAU
        if(selected == 0) { my_bar(622, 267, 928, 353, goldGlow); my_bar(625, 270, 925, 350, white); my_bar(627, 272, 923, 348, btnYellow); }
        else { my_bar(625, 280, 925, 350, btnYellowShadow); my_bar(625, 270, 925, 340, btnYellow); }
        setbkcolor(btnYellow); setcolor(COLOR(50,20,10)); settextstyle(BOLD_FONT, HORIZ_DIR, 4); outtextxy(775, 310, (char*)"BAT DAU");
        
        // BUTTON THOAT
        if(selected == 1) { my_bar(622, 387, 928, 473, goldGlow); my_bar(625, 390, 925, 470, white); my_bar(627, 392, 923, 468, btnGreen); }
        else { my_bar(625, 400, 925, 470, btnGreenShadow); my_bar(625, 390, 925, 460, btnGreen); }
        setbkcolor(btnGreen); setcolor(white); settextstyle(BOLD_FONT, HORIZ_DIR, 4); outtextxy(775, 430, (char*)"THOAT");
        
        setvisualpage(trang);
        trang = 1 - trang;
        
        // 7. KEYBOARD & MOUSE EVENT
        if (kbhit()) {
            int key = getch();
            if (key == 224) {
                key = getch();
                if (key == 72) { selected--; if(selected < 0) selected = 1; }
                if (key == 80) { selected++; if(selected > 1) selected = 0; }
            } else if (key == 13) { 
                if (selected == 0) return 1; 
                if (selected == 1) return 0; 
            } else if (key == 27) { 
                return 0;
            } else if (key == 's' || key == 'S') {
                *skin = (*skin + 1) % 4; // 0, 1, 2, 3
                luuDataShop(*skin, *phuKien, *xu);
            } else if (key == 'a' || key == 'A') {
                *phuKien = (*phuKien + 1) % 4; // 0: None, 1: Crown, 2: Glasses, 3: Bow
                luuDataShop(*skin, *phuKien, *xu);
            }
        }
        
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int mx, my; getmouseclick(WM_LBUTTONDOWN, mx, my); clearmouseclick(WM_LBUTTONDOWN);
            if (mx >= 625 && mx <= 925 && my >= 270 && my <= 350) return 1;
            if (mx >= 625 && mx <= 925 && my >= 390 && my <= 470) return 0;
        }
        
        delay(30);
    }
}
