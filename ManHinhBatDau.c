#include "ManHinhBatDau.h"
#include "VeHinh.h"
#include "VatThe.h"
#include "Meo.h"
#include <graphics.h>
#include <conio.h>
#include <stdio.h>

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
    
    int bgSky = COLOR(25, 15, 45); 
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
    int btnBlue = COLOR(137, 180, 250);
    int btnBlueShadow = COLOR(100, 130, 200);
    int panelBg = COLOR(30, 30, 46); 
    int textBrown = COLOR(205, 214, 244); 
    int titleBlue = COLOR(245, 194, 231); 
    int white = COLOR(255, 255, 255);
    int goldGlow = COLOR(255, 215, 0); 
    
    int selected = 0; // 0: Bat Dau, 1: Cua Hang, 2: Thoat
    int inShop = 0;   // Trang thai trong cua hang
    int shopSelect = 0; // 0: Mac dinh, 1: Vang(100), 2: Den(200), 3: Vuong mien(150), 4: Kinh(50)
    
    int trang = 0;
    int i, px, py, x, y;
    static int starFrame = 0;
    double t = 0.0;
    
    // Gia ca
    int priceSkinVang = 100, priceSkinDen = 200;
    int priceCrown = 150, priceGlass = 50;
    
    // Trang thai mo khoa (De don gian, neu du tien cho phep deo, hoac chi dung `xu` tieu)
    // De gian luoc, cu chon la tieu tien neu chua so huu. Ta kiem tra qua skin/phuKien hien tai,
    // nhung neu ho doi lai mac dinh thi sao? Tot nhat ta chi kiem tra don gian.

    while (1) {
        setactivepage(trang);
        t += 0.05;
        
        // 1. SKY
        my_bar(0, 0, 1000, 350, bgSky);
        starFrame++;
        for(x = 25; x < 980; x += 45) {
            for(y = 20; y < 270; y += 35) {
                int phase = (x * 17 + y * 23 + starFrame) % 15;
                if(phase < 2) my_bar(x, y, x+3, y+3, white); 
                else if(phase < 5) my_bar(x+1, y+1, x+2, y+2, COLOR(200, 200, 240)); 
            }
        }
        
        for(int dy = -40; dy <= 40; dy++) {
            for(int dx = -40; dx <= 40; dx++) {
                if(dx*dx + dy*dy <= 40*40) {
                    int cdx = dx + 15, cdy = dy - 5;
                    if(cdx*cdx + cdy*cdy > 38*38) {
                        my_putpixel(850 + dx, 80 + dy, COLOR(254, 215, 0)); 
                    }
                }
            }
        }
        
        // 2. FENCE
        for(i = -10; i < 1000; i += 40) {
            my_bar(i, 280, i+30, 400, fenceWood);
            my_bar(i+5, 270, i+25, 280, fenceWood); 
            veDuongThang(i+30, 280, i+30, 400, fenceLine);
        }
        
        // 3. GRASS
        my_bar(0, 370, 1000, 700, bgGrassTop);
        for(px=20; px<1000; px+=40) {
            for(py=390; py<700; py+=30) {
                if((px+py)%70 == 0) my_bar(px, py, px+4, py+4, bgGrassDark);
            }
        }
        
        if(!inShop) {
            // MEO DEMO MENU
            veMeoCoPhuKien(500, 250, false, t, *skin, *phuKien, false);
            
            // TITLE
            my_bar(246, 24, 754, 134, COLOR(50, 30, 10)); 
            my_bar(250, 20, 750, 130, titleShadow);
            my_bar(250, 15, 750, 120, titleWood);
            my_bar(260, 25, 270, 35, COLOR(50, 50, 70)); my_bar(730, 25, 740, 35, COLOR(50, 50, 70));
            my_bar(260, 100, 270, 110, COLOR(50, 50, 70)); my_bar(730, 100, 740, 110, COLOR(50, 50, 70));
            
            setbkcolor(titleWood); settextstyle(TRIPLEX_FONT, HORIZ_DIR, 6); settextjustify(CENTER_TEXT, CENTER_TEXT);
            setcolor(COLOR(50, 40, 20)); outtextxy(503, 53, (char*)"MEO");
            setcolor(COLOR(255, 220, 50)); outtextxy(500, 50, (char*)"MEO");
            settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 4);
            setcolor(COLOR(50, 40, 20)); outtextxy(503, 103, (char*)"HUNG DONG XU");
            setcolor(titleBlue); outtextxy(500, 100, (char*)"HUNG DONG XU");
            
            // HOVER
            px = mousex(); py = mousey();
            int hoverStart = (px >= 350 && px <= 650 && py >= 320 && py <= 380);
            int hoverShop  = (px >= 350 && px <= 650 && py >= 400 && py <= 460);
            int hoverThoat = (px >= 350 && px <= 650 && py >= 480 && py <= 540);
            if(hoverStart) selected = 0; else if(hoverShop) selected = 1; else if(hoverThoat) selected = 2;
            
            // BUTTON BAT DAU
            if(selected == 0) { my_bar(343, 313, 657, 387, goldGlow); my_bar(345, 315, 655, 385, white); my_bar(347, 317, 653, 383, btnYellow); }
            else { my_bar(350, 325, 650, 385, btnYellowShadow); my_bar(350, 320, 650, 380, btnYellow); }
            setbkcolor(btnYellow); setcolor(COLOR(50,20,10)); settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3); outtextxy(500, 350, (char*)"BAT DAU");
            
            // BUTTON CUA HANG
            if(selected == 1) { my_bar(343, 393, 657, 467, goldGlow); my_bar(345, 395, 655, 465, white); my_bar(347, 397, 653, 463, btnBlue); }
            else { my_bar(350, 405, 650, 465, btnBlueShadow); my_bar(350, 400, 650, 460, btnBlue); }
            setbkcolor(btnBlue); setcolor(COLOR(50,20,10)); outtextxy(500, 430, (char*)"CUA HANG");
            
            // BUTTON THOAT
            if(selected == 2) { my_bar(343, 473, 657, 547, goldGlow); my_bar(345, 475, 655, 545, white); my_bar(347, 477, 653, 543, btnGreen); }
            else { my_bar(350, 485, 650, 545, btnGreenShadow); my_bar(350, 480, 650, 540, btnGreen); }
            setbkcolor(btnGreen); setcolor(white); outtextxy(500, 510, (char*)"THOAT");
            
        } else {
            // TRONG CUA HANG
            veMeoCoPhuKien(250, 450, false, t, *skin, *phuKien, false);
            
            my_bar(450, 50, 950, 650, COLOR(80, 50, 30)); 
            my_bar(455, 55, 945, 645, COLOR(255, 240, 210)); 
            
            setbkcolor(COLOR(255, 240, 210)); setcolor(COLOR(50, 20, 10));
            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4); settextjustify(CENTER_TEXT, CENTER_TEXT);
            outtextxy(700, 100, (char*)"CUA HANG");
            
            char xuStr[50]; sprintf(xuStr, "Xu cua ban: %d", *xu);
            settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
            outtextxy(700, 140, xuStr);
            
            px = mousex(); py = mousey();
            
            // Cac mon do
            char* items[] = {"Meo Mac Dinh", "Meo Muop Vang (100x)", "Meo Mun (200x)", "Bo Phu Kien Mac Dinh", "Vuong Mien (150x)", "Kinh Ram (50x)", "QUAY LAI"};
            int ys[] = {200, 260, 320, 380, 440, 500, 580};
            
            for(i=0; i<7; i++) {
                int isHover = (px >= 500 && px <= 900 && py >= ys[i]-25 && py <= ys[i]+25);
                if(isHover) shopSelect = i;
                
                int bg = (shopSelect == i) ? goldGlow : white;
                my_bar(500, ys[i]-20, 900, ys[i]+20, COLOR(150, 150, 150));
                my_bar(500, ys[i]-22, 900, ys[i]+18, bg);
                setbkcolor(bg); setcolor(COLOR(50,20,10));
                
                char textOut[50]; strcpy(textOut, items[i]);
                if(i == 0 && *skin == 0) strcat(textOut, " [DANG DUNG]");
                if(i == 1 && *skin == 1) strcat(textOut, " [DANG DUNG]");
                if(i == 2 && *skin == 2) strcat(textOut, " [DANG DUNG]");
                if(i == 3 && *phuKien == 0) strcat(textOut, " [DANG DUNG]");
                if(i == 4 && *phuKien == 1) strcat(textOut, " [DANG DUNG]");
                if(i == 5 && *phuKien == 2) strcat(textOut, " [DANG DUNG]");
                
                outtextxy(700, ys[i], textOut);
            }
        }
        
        setvisualpage(trang);
        trang = 1 - trang;
        
        if (kbhit()) {
            int key = getch();
            if (key == 224) {
                key = getch();
                if(inShop) {
                    if (key == 72) { shopSelect--; if(shopSelect < 0) shopSelect = 6; }
                    if (key == 80) { shopSelect++; if(shopSelect > 6) shopSelect = 0; }
                } else {
                    if (key == 72) { selected--; if(selected < 0) selected = 2; }
                    if (key == 80) { selected++; if(selected > 2) selected = 0; }
                }
            } else if (key == 13) { 
                if(!inShop) {
                    if (selected == 0) return 1; 
                    if (selected == 1) inShop = 1;
                    if (selected == 2) return 0; 
                } else {
                    if(shopSelect == 0) *skin = 0;
                    else if(shopSelect == 1) { if(*xu >= 100 || *skin == 1) { if(*skin!=1) *xu -= 100; *skin = 1; } }
                    else if(shopSelect == 2) { if(*xu >= 200 || *skin == 2) { if(*skin!=2) *xu -= 200; *skin = 2; } }
                    else if(shopSelect == 3) *phuKien = 0;
                    else if(shopSelect == 4) { if(*xu >= 150 || *phuKien == 1) { if(*phuKien!=1) *xu -= 150; *phuKien = 1; } }
                    else if(shopSelect == 5) { if(*xu >= 50  || *phuKien == 2) { if(*phuKien!=2) *xu -= 50;  *phuKien = 2; } }
                    else if(shopSelect == 6) { inShop = 0; luuDataShop(*skin, *phuKien, *xu); }
                }
            } else if (key == 27) { 
                if(inShop) { inShop = 0; luuDataShop(*skin, *phuKien, *xu); }
                else return 0;
            }
        }
        
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int mx, my; getmouseclick(WM_LBUTTONDOWN, mx, my); clearmouseclick(WM_LBUTTONDOWN);
            if(!inShop) {
                if (mx >= 350 && mx <= 650 && my >= 320 && my <= 380) return 1;
                if (mx >= 350 && mx <= 650 && my >= 400 && my <= 460) inShop = 1;
                if (mx >= 350 && mx <= 650 && my >= 480 && my <= 540) return 0;
            } else {
                int ys[] = {200, 260, 320, 380, 440, 500, 580};
                for(i=0; i<7; i++) {
                    if(mx >= 500 && mx <= 900 && my >= ys[i]-25 && my <= ys[i]+25) {
                        if(i == 0) *skin = 0;
                        else if(i == 1) { if(*xu >= 100 || *skin == 1) { if(*skin!=1) *xu -= 100; *skin = 1; } }
                        else if(i == 2) { if(*xu >= 200 || *skin == 2) { if(*skin!=2) *xu -= 200; *skin = 2; } }
                        else if(i == 3) *phuKien = 0;
                        else if(i == 4) { if(*xu >= 150 || *phuKien == 1) { if(*phuKien!=1) *xu -= 150; *phuKien = 1; } }
                        else if(i == 5) { if(*xu >= 50  || *phuKien == 2) { if(*phuKien!=2) *xu -= 50;  *phuKien = 2; } }
                        else if(i == 6) { inShop = 0; luuDataShop(*skin, *phuKien, *xu); }
                    }
                }
            }
        }
        
        delay(30);
    }
}
