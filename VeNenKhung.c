#include "VeNenKhung.h"
#include "VeHinh.h"
#include "VatThe.h"
#include "TraiTim.h"
#include <graphics.h>
#include <stdio.h>

void veNenKhung(struct GiaoDien_State* state) {
    int i;
    char scoreStr[20];
    char highScoreStr[30];

    // Colors matching the new design
    int woodLight = COLOR(248, 225, 185); // Header/Footer base wood
    int woodDark = COLOR(210, 160, 90);   // Wood borders
    int skyBg = COLOR(144, 213, 245);
    int grassBg = COLOR(122, 193, 67);
    int fenceWood = COLOR(215, 160, 95);
    int fenceLine = COLOR(165, 110, 50);
    int white = COLOR(255, 255, 255);
    int textBrown = COLOR(101, 56, 24);
    int pillBg = COLOR(255, 245, 230);
    int orangeCenter = COLOR(245, 150, 40); // cho CatCatch title block
    int textGold = COLOR(255, 215, 0);

    // ===== 1. HEADER (y = 0 to 80) =====
    my_bar(0, 0, 800, 80, woodLight);
    veDuongThang(0, 80, 800, 80, woodDark);
    veDuongThang(0, 81, 800, 81, woodDark);
    
    // Diem (Left Pill)
    my_bar(50, 20, 250, 60, woodDark); // shadow/border
    my_bar(52, 22, 248, 58, pillBg);
    setbkcolor(pillBg);
    setcolor(textBrown);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    outtextxy(150, 30, (char*)"DIEM");
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
    setcolor(COLOR(220, 80, 20));
    sprintf(scoreStr, "%d", state->diem);
    outtextxy(150, 50, scoreStr);
    
    // Cao nhat (Right Pill)
    my_bar(550, 20, 750, 60, woodDark); // shadow/border
    my_bar(552, 22, 748, 58, pillBg);
    setbkcolor(pillBg);
    setcolor(textBrown);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    outtextxy(650, 30, (char*)"CAO NHAT");
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
    setcolor(COLOR(220, 80, 20));
    sprintf(highScoreStr, "%d", state->caoNhat);
    outtextxy(650, 50, highScoreStr);
    
    // Center Title Block
    my_bar(280, 0, 520, 70, woodDark); 
    my_bar(285, 0, 515, 65, orangeCenter);
    setbkcolor(orangeCenter);
    setcolor(white);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    outtextxy(402, 22, (char*)"CatCatch!");
    setcolor(textGold);
    outtextxy(400, 20, (char*)"CatCatch!");
    
    // Mang
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    setcolor(white);
    outtextxy(360, 50, (char*)"MANG:");
    for(i = 0; i < state->mang; i++) {
        veTraiTim(400 + i * 20, 50); 
    }

    // ===== 2. MAIN PLAY AREA (y = 82 to 460) =====
    int px = 8; // Kich thuoc pixel de ve retro style
    int skyDark = COLOR(25, 15, 45); // Tim den dam
    int starColor1 = COLOR(255, 255, 220);
    int starColor2 = COLOR(200, 200, 255);
    int grassTop = COLOR(50, 220, 0);
    int grassDark = COLOR(0, 150, 0);
    int dirtBg = COLOR(116, 70, 49);
    int dirtLight = COLOR(135, 85, 60);
    int dirtDark = COLOR(85, 45, 30);
    int x, y;

    // 1. Sky Base (Tim den dam)
    my_bar(10, 82, 790, 460, skyDark); 
    
    // 2. Stars (Ngoi sao lap lanh)
    for(x = 20; x < 790; x += px*3) {
        for(y = 100; y < 400; y += px*3) {
            int h = (x*17 + y*31) % 100;
            if(h < 3) {
                // Sao lon hon 1 xiu, lap lanh nhe (hien 80%)
                if(rand() % 5 != 0) my_bar(x, y, x+3, y+3, starColor1);
            } else if(h > 96) {
                // Sao rat nho, lap lanh nhieu (hien 50%)
                if(rand() % 2 == 0) my_bar(x, y, x+2, y+2, starColor2);
            } else if(h == 50) {
                // Sao dac biet hinh dau cong (hien 90%)
                if(rand() % 10 != 0) {
                    my_bar(x+2, y, x+4, y+6, starColor1);
                    my_bar(x, y+2, x+6, y+4, starColor1);
                }
            }
        }
    }

    // 3. Ground Dirt Layer
    my_bar(10, 430, 790, 460, dirtBg);
    for(x = 10; x < 790; x += px) {
        for(y = 430; y < 460; y += px) {
            int h = (x*17 + y*31) % 100;
            if(h < 15) my_bar(x, y, x+px, y+px, dirtLight);
            else if(h > 85) my_bar(x, y, x+px, y+px, dirtDark);
        }
    }
    
    // 4. Grass Layer
    my_bar(10, 415, 790, 430, grassTop);
    for(x = 10; x < 790; x += px) {
        int drop = ((x/px)%2 == 0) ? px : 0;
        my_bar(x, 430, x+px, 430+drop, grassTop); // jagged grass going down
        my_bar(x, 430+drop, x+px, 430+drop+px/2, grassDark); // dark shadow edge
    }
    
    // 4.5 Fractal Grass (Koch Curve Bush)
    // Tich hop thuat toan Fractal theo tieu chi cham diem
    int fractalGrass = COLOR(180, 240, 100);
    veDuongKoch(30, 415, 150, 415, fractalGrass, 3);
    veDuongKoch(150, 415, 270, 415, fractalGrass, 3);
    veDuongKoch(500, 415, 620, 415, fractalGrass, 3);
    veDuongKoch(620, 415, 740, 415, fractalGrass, 3);

    // Side borders for play area
    my_bar(0, 82, 10, 460, woodDark);
    my_bar(790, 82, 800, 460, woodDark);

    // ===== 3. FOOTER (y = 460 to 600) =====
    my_bar(0, 460, 800, 600, woodLight);
    veDuongThang(0, 460, 800, 460, woodDark);
    veDuongThang(0, 461, 800, 461, woodDark);
    
    // Instruction Panel inside footer
    my_bar(20, 475, 780, 585, woodDark);
    my_bar(22, 477, 778, 583, pillBg);
    
    // "LUAT CHOI:" badge
    my_bar(40, 465, 170, 495, woodDark);
    my_bar(42, 467, 168, 493, orangeCenter);
    setbkcolor(orangeCenter);
    setcolor(white);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    outtextxy(105, 480, (char*)"LUAT CHOI:");
    
    // Instructions Text
    setbkcolor(pillBg);
    setcolor(textBrown);
    settextjustify(LEFT_TEXT, CENTER_TEXT);
    settextstyle(SMALL_FONT, HORIZ_DIR, 5); // Chon font chu nho gon hon
    
    // Dong 1
    int px_i = 50, py = 525;
    my_bar(px_i-3, py-1, px_i+3, py+3, textBrown); 
    my_bar(px_i-6, py-4, px_i-4, py-2, textBrown); 
    my_bar(px_i-1, py-5, px_i+1, py-3, textBrown); 
    my_bar(px_i+4, py-4, px_i+6, py-2, textBrown); 
    outtextxy(px_i + 15, py, (char*)"Phim [<-] [->]: Di chuyen MEO sang trai, phai.");
    
    // Dong 2
    py = 555;
    my_bar(px_i-3, py-1, px_i+3, py+3, textBrown); 
    my_bar(px_i-6, py-4, px_i-4, py-2, textBrown); 
    my_bar(px_i-1, py-5, px_i+1, py-3, textBrown); 
    my_bar(px_i+4, py-4, px_i+6, py-2, textBrown); 
    outtextxy(px_i + 15, py, (char*)"Luu y: Toc do roi tang theo diem. Het 3 mang la thua!");
    
    // Vertical separator
    veDuongThang(480, 490, 480, 570, woodDark);
    for(int y = 490; y < 570; y+=8) veDuongThang(480, y, 480, y+4, pillBg); // dashed effect
    
    // Icons layout
    int iconX = 540;
    int textX = 570;
    
    // Coin
    veDongXu(iconX, 502, 12, 0);
    setbkcolor(pillBg); setcolor(textBrown);
    outtextxy(textX, 502, (char*)": +10 Diem");
    
    // Fishbone
    veXuongCa(iconX, 532, 0.0);
    setbkcolor(pillBg); setcolor(textBrown);
    outtextxy(textX, 532, (char*)": -5 Diem");
    
    // Bomb
    veBom(iconX, 562, 1.0);
    setbkcolor(pillBg); setcolor(textBrown);
    outtextxy(textX, 562, (char*)": -1 Mang");
}
