#include "ManHinhBatDau.h"
#include "VeHinh.h"
#include "VatThe.h"
#include <graphics.h>
#include <conio.h>

// Ve dau meo don gian
void veDauMeoChibi(int x, int y) {
    int catPink = COLOR(245, 194, 231);
    int catDarkPink = COLOR(243, 139, 168); // Nose and inner ear
    int white = COLOR(255, 255, 255);
    int black = COLOR(17, 17, 27);
    int i;

    // Tai meo (Ears)
    for(i=0; i<30; i++) {
        veDuongThang(x-40+i/2, y-30-i, x-20+i, y-30, catPink); // Tai trai
        veDuongThang(x+40-i/2, y-30-i, x+20-i, y-30, catPink); // Tai phai
    }
    // Tai trong (Inner ears)
    for(i=0; i<15; i++) {
        veDuongThang(x-30+i/2, y-30-i, x-20+i, y-30, catDarkPink);
        veDuongThang(x+30-i/2, y-30-i, x+20-i, y-30, catDarkPink);
    }
    
    // Mat cat (Face)
    my_bar(x-40, y-30, x+40, y+30, catPink);
    my_bar(x-50, y-20, x+50, y+20, catPink);
    my_bar(x-30, y-40, x+30, y+40, catPink);
    
    // Phan trang tren mieng
    my_bar(x-20, y, x+20, y+20, white);
    my_bar(x-30, y+5, x+30, y+15, white);
    
    // Mat (Eyes)
    my_bar(x-25, y-10, x-15, y+5, black);
    my_bar(x+15, y-10, x+25, y+5, black);
    // Diem sang trong mat (Highlights)
    my_bar(x-20, y-8, x-16, y-3, white);
    my_bar(x+20, y-8, x+24, y-3, white);
    
    // Mui (Nose)
    my_bar(x-5, y+2, x+5, y+7, catDarkPink);
    
    // Ria mep (Whiskers)
    veDuongThang(x-45, y+10, x-25, y+5, black);
    veDuongThang(x-45, y+20, x-25, y+15, black);
    veDuongThang(x+25, y+5, x+45, y+10, black);
    veDuongThang(x+25, y+15, x+45, y+20, black);
}

int hienThiManHinhBatDau() {
    int bgSky = COLOR(25, 15, 45); // Gameplay Sky Dark
    int bgGrassTop = COLOR(50, 220, 0); // Gameplay Grass Top
    int bgGrassDark = COLOR(0, 150, 0); // Gameplay Grass Dark
    int fenceWood = COLOR(116, 70, 49); // Dirt color
    int fenceLine = COLOR(85, 45, 30);  // Dirt dark color
    
    int titleWood = COLOR(137, 180, 250); // Catppuccin Sapphire / Blueish pastel
    int titleShadow = COLOR(100, 130, 200);
    
    int btnYellow = COLOR(249, 226, 175); // Pastel Yellow
    int btnYellowShadow = COLOR(200, 180, 140);
    int btnGreen = COLOR(166, 227, 161); // Pastel Green
    int btnGreenShadow = COLOR(130, 180, 120);
    
    int panelBg = COLOR(30, 30, 46); // Crust
    int textBrown = COLOR(205, 214, 244); // Text white/blueish
    int titleBlue = COLOR(245, 194, 231); // Pink text
    int white = COLOR(255, 255, 255);
    
    int selected = 0; // 0: Bat Dau, 2: Thoat
    int trang = 0;
    int i, px, py, x, y;
    
    while (1) {
        setactivepage(trang);
        
        // 1. SKY (Night sky with stars)
        my_bar(0, 0, 800, 300, bgSky);
        // Sao nhap nhay
        for(x = 20; x < 800; x += 30) {
            for(y = 20; y < 230; y += 40) {
                if((x+y)%7 == 0 && rand()%10 > 2) my_bar(x, y, x+2, y+2, white);
            }
        }
        
        // 2. FENCE (Dat mau go/dat)
        for(i = -10; i < 800; i += 40) {
            my_bar(i, 230, i+30, 350, fenceWood);
            my_bar(i+5, 220, i+25, 230, fenceWood); // bo tron tren
            veDuongThang(i+30, 230, i+30, 350, fenceLine);
        }
        
        // 3. GRASS
        my_bar(0, 320, 800, 600, bgGrassTop);
        for(px=20; px<800; px+=40) {
            for(py=340; py<600; py+=30) {
                if((px+py)%70 == 0) {
                    my_bar(px, py, px+4, py+4, bgGrassDark);
                }
            }
        }
        
        // 4. BIG CAT FACE
        veDauMeoChibi(400, 220);
        
        // 5. TITLE BOARD
        my_bar(150, 20, 650, 130, titleShadow);
        my_bar(150, 15, 650, 120, titleWood);
        // Dinh tan tren bang go
        my_bar(160, 25, 170, 35, titleShadow);
        my_bar(630, 25, 640, 35, titleShadow);
        my_bar(160, 100, 170, 110, titleShadow);
        my_bar(630, 100, 640, 110, titleShadow);
        
        setbkcolor(titleWood);
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 6);
        settextjustify(CENTER_TEXT, CENTER_TEXT);
        // Chu MEO
        setcolor(white); outtextxy(402, 52, (char*)"MEO");
        setcolor(COLOR(255, 220, 50)); outtextxy(400, 50, (char*)"MEO");
        
        // Chu HUNG DONG XU
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 4);
        setcolor(white); outtextxy(402, 102, (char*)"HUNG DONG XU");
        setcolor(titleBlue); outtextxy(400, 100, (char*)"HUNG DONG XU");
        
        // 6. BUTTONS
        // BAT DAU
        if (selected == 0) {
            my_bar(245, 295, 555, 365, white);
            my_bar(250, 300, 550, 360, btnYellow);
        } else {
            my_bar(250, 305, 550, 365, btnYellowShadow);
            my_bar(250, 300, 550, 360, btnYellow);
        }
        setbkcolor(btnYellow);
        setcolor(textBrown);
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
        outtextxy(400, 330, (char*)"BAT DAU");
        
        // THOAT (Thay chuc nang cho nut Huong Dan xanh la)
        if (selected == 2) {
            my_bar(295, 375, 505, 435, white);
            my_bar(300, 380, 500, 430, btnGreen);
        } else {
            my_bar(300, 385, 500, 435, btnGreenShadow);
            my_bar(300, 380, 500, 430, btnGreen);
        }
        setbkcolor(btnGreen);
        setcolor(white);
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
        outtextxy(400, 405, (char*)"THOAT");
        
        // 7. INSTRUCTION PANEL
        my_bar(150, 460, 650, 580, COLOR(210, 190, 160)); // Vien
        my_bar(150, 455, 650, 575, panelBg); // Nen
        
        setbkcolor(panelBg);
        setcolor(textBrown);
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
        outtextxy(400, 475, (char*)"* HUONG DAN *");
        
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
        outtextxy(400, 500, (char*)"Phim [TRAI] [PHAI] hoac di chuot de dieu khien");
        outtextxy(400, 520, (char*)"meo hung cac vat pham roi tu tren cao xuong.");
        
        // Icons
        settextjustify(LEFT_TEXT, CENTER_TEXT);
        veDongXu(230, 555, 12, 0);
        setbkcolor(panelBg); setcolor(textBrown);
        outtextxy(250, 555, (char*)": +10 Diem");
        
        veXuongCa(370, 555, 0.0);
        setbkcolor(panelBg); setcolor(textBrown);
        outtextxy(390, 555, (char*)": -5 Diem");
        
        veBom(500, 555, 1.0);
        setbkcolor(panelBg); setcolor(textBrown);
        outtextxy(525, 555, (char*)": -1 Mang");
        
        setvisualpage(trang);
        trang = 1 - trang;
        
        if (kbhit()) {
            int key = getch();
            if (key == 224) {
                key = getch();
                if (key == 72 || key == 80 || key == 75 || key == 77) {
                    selected = (selected == 0) ? 2 : 0;
                }
            } else if (key == 13) { // Enter
                if (selected == 0) return 1; // Bat dau
                if (selected == 2) return 0; // Thoat
            } else if (key == 27) { // ESC
                return 0;
            }
        }
        
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int mx, my;
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            clearmouseclick(WM_LBUTTONDOWN);
            if (mx >= 250 && mx <= 550 && my >= 300 && my <= 360) return 1; // BAT DAU
            if (mx >= 300 && mx <= 500 && my >= 380 && my <= 430) return 0; // THOAT
        }
        
        delay(50);
    }
}
