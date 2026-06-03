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
    
    // Kich thuoc man hinh (khop voi man hinh choi 1150x750)
    int W = 1150, H = 750;
    
    while (1) {
        setactivepage(trang);
        t += 0.05;
        
        // 1. GRADIENT SKY - phu toan bo chieu rong 1150, chieu cao 450
        for (int gy = 0; gy < 450; gy += 10) {
            int r = 15 + (gy * 35 / 450);
            int g = 20 + (gy * 60 / 450);
            int b = 50 + (gy * 90 / 450);
            my_bar(0, gy, W, gy + 10, COLOR(r, g, b));
        }
        
        // Ngoi sao lap lanh - phu rong 1150
        starFrame++;
        for(x = 25; x < W; x += 65) {
            for(y = 20; y < 380; y += 45) {
                int phase = (x * 17 + y * 23 + starFrame) % 20;
                if(phase < 2) my_bar(x, y, x+3, y+3, white); 
                else if(phase < 5) my_bar(x+1, y+1, x+2, y+2, COLOR(200, 200, 240)); 
            }
        }
        
        // Mat trang nho lap lanh (Goc trai)
        int mx = 200, my = 130, mr = 35;
        int glow1 = mr + 8 + (int)(2 * sin(t * 3.0));
        int glow2 = mr + 16 + (int)(4 * sin(t * 2.0));
        
        for(int dy = -glow2; dy <= glow2; dy++) {
            for(int dx = -glow2; dx <= glow2; dx++) {
                int distSq = dx*dx + dy*dy;
                if(distSq <= mr*mr) {
                    my_putpixel(mx+dx, my+dy, COLOR(255, 255, 240));
                } else if (distSq <= glow1*glow1) {
                    my_putpixel(mx+dx, my+dy, COLOR(255, 240, 180));
                } else if (distSq <= glow2*glow2 && (dx+dy + starFrame/3)%2 == 0) {
                    my_putpixel(mx+dx, my+dy, COLOR(200, 180, 120));
                }
            }
        }
        
        // Tia sang lap lanh
        int flareLen = 25 + (int)(8 * sin(t * 8.0));
        veDuongThang(mx - flareLen, my, mx + flareLen, my, white);
        veDuongThang(mx, my - flareLen, mx, my + flareLen, white);
        
        // 2. FENCE - phu rong 1150, tai y=400
        for(i = -10; i < W; i += 60) {
            my_bar(i, 400, i+25, 490, fenceWood);
            veDuongThang(i+25, 400, i+25, 490, fenceLine);
        }
        my_bar(0, 420, W, 435, fenceWood); 
        my_bar(0, 460, W, 475, fenceWood);
        veDuongThang(0, 435, W, 435, fenceLine);
        veDuongThang(0, 475, W, 475, fenceLine);
        
        // 3. GRASS - phu toan bo 1150 x (500 -> 750)
        my_bar(0, 490, W, H, bgGrassTop);
        for(px = 10; px < W; px += 50) {
            for(py = 510; py < H; py += 35) {
                if((px+py)%70 == 0) my_bar(px, py, px+6, py+6, bgGrassDark);
            }
        }
        
        // Fractal Bush (Bui co) - Koch Curve
        veDuongKoch(50, 505, 500, 505, COLOR(30, 160, 60), 4);
        
        // =========================================================================
        // 4.5 Dragon Curve - Duong cong Rong trang tri goc trai man hinh bat dau
        // Ve tai goc duoi trai (vung co) voi do sau 10, mau tim huyen bi de tao
        // cam giac ky ao, phuc tap. Dragon Curve bao phu vung tu (0,480) den (350,680)
        // =========================================================================
        //veDuongRong(30, 490, 450, 490, COLOR(120, 60, 200), 10, 1);
        
        // =========================================================================
        // 4.6 C-Curve - Duong cong C trang tri ben phai man hinh bat dau  
        // Ve tai goc duoi phai voi mau xanh duong moc song lanh, do sau 12
        // tao hieu ung song nuoc bao xung quanh man hinh chu de game
        // =========================================================================
        //veDuongC(650, 490, 1100, 490, COLOR(60, 140, 220), 10);
        
        // 4. MEO - dat o x=280, y=525 (tren co)
        veMeoCoPhuKien(280, 530, false, t, *skin, *phuKien, false);
        
        // 5. TITLE - can giua theo chieu rong 1150
        // Title block: x = 650..1110, y = 55..200
        my_bar(646, 51, 1114, 204, COLOR(50, 30, 10)); // Vien ngoai
        my_bar(650, 55, 1110, 200, titleShadow);       // Bong
        my_bar(650, 48, 1110, 192, titleWood);         // Nen go
        // Dinh oc 4 goc
        my_bar(660, 60, 670, 70, COLOR(50, 50, 70)); 
        my_bar(1090, 60, 1100, 70, COLOR(50, 50, 70));
        my_bar(660, 172, 670, 182, COLOR(50, 50, 70)); 
        my_bar(1090, 172, 1100, 182, COLOR(50, 50, 70));
        
        setbkcolor(titleWood); 
        settextjustify(CENTER_TEXT, CENTER_TEXT);
        
        settextstyle(BOLD_FONT, HORIZ_DIR, 6); 
        setcolor(COLOR(50, 40, 20)); outtextxy(882, 103, (char*)"MEO");
        setcolor(COLOR(255, 220, 50)); outtextxy(880, 100, (char*)"MEO");
        
        settextstyle(BOLD_FONT, HORIZ_DIR, 3);
        setcolor(COLOR(50, 40, 20)); outtextxy(882, 155, (char*)"HUNG DONG XU");
        setcolor(titleBlue); outtextxy(880, 152, (char*)"HUNG DONG XU");
        
        // 6. BUTTONS - can giua theo chieu rong 1150 (tam x=880)
        // BAT DAU: y=270..350, THOAT: y=390..470
        px = mousex(); py = mousey();
        int hoverStart = (px >= 680 && px <= 1080 && py >= 270 && py <= 350);
        int hoverThoat = (px >= 680 && px <= 1080 && py >= 390 && py <= 470);
        if(hoverStart) selected = 0; else if(hoverThoat) selected = 1;
        
        // BUTTON BAT DAU
        if(selected == 0) { my_bar(677, 267, 1083, 353, goldGlow); my_bar(680, 270, 1080, 350, white); my_bar(682, 272, 1078, 348, btnYellow); }
        else { my_bar(680, 280, 1080, 350, btnYellowShadow); my_bar(680, 270, 1080, 340, btnYellow); }
        setbkcolor(btnYellow); setcolor(COLOR(50,20,10)); settextstyle(BOLD_FONT, HORIZ_DIR, 4); 
        outtextxy(880, 310, (char*)"BAT DAU");
        
        // BUTTON THOAT
        if(selected == 1) { my_bar(677, 387, 1083, 473, goldGlow); my_bar(680, 390, 1080, 470, white); my_bar(682, 392, 1078, 468, btnGreen); }
        else { my_bar(680, 400, 1080, 470, btnGreenShadow); my_bar(680, 390, 1080, 460, btnGreen); }
        setbkcolor(btnGreen); setcolor(white); settextstyle(BOLD_FONT, HORIZ_DIR, 4); 
        outtextxy(880, 430, (char*)"THOAT");
        
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
                *skin = (*skin + 1) % 4;
                luuDataShop(*skin, *phuKien, *xu);
            } else if (key == 'a' || key == 'A') {
                *phuKien = (*phuKien + 1) % 4;
                luuDataShop(*skin, *phuKien, *xu);
            }
        }
        
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int mx2, my2; getmouseclick(WM_LBUTTONDOWN, mx2, my2); clearmouseclick(WM_LBUTTONDOWN);
            if (mx2 >= 680 && mx2 <= 1080 && my2 >= 270 && my2 <= 350) return 1;
            if (mx2 >= 680 && mx2 <= 1080 && my2 >= 390 && my2 <= 470) return 0;
        }
        
        delay(30);
    }
}
