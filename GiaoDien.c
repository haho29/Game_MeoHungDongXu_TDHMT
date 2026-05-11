#include "GiaoDien.h"
#include "TraiTim.h"
#include "Meo.h"
#include "VatThe.h"
#include "VeHinh.h"
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

void initGiaoDien(struct GiaoDien_State* state) {
    int i;
    state->diem = 0;
    state->mang = 3;
    state->caoNhat = 0;
    
    // Doc diem cao nhat tu file
    FILE *f = fopen("highscore.txt", "r");
    if(f) {
        fscanf(f, "%d", &state->caoNhat);
        fclose(f);
    }

    state->meoX = 400; // Giua man hinh 800
    state->meoY = 415; // Gan day cua vung choi (440)
    state->gameOver = false;
    
    for(i = 0; i < 5; i++) {
        state->cacVatThe[i].active = false;
    }
}

void veNenKhung(struct GiaoDien_State* state) {
    int i;
    char scoreStr[20];
    char highScoreStr[30];

    // Bang mau Catppuccin Mocha
    int bgPlay = COLOR(30, 30, 46); // Base
    int bgHeader = COLOR(24, 24, 37); // Mantle
    int borderColor = COLOR(137, 180, 250); // Blue
    int titleColor = COLOR(203, 166, 247); // Mauve
    int scoreColor = COLOR(166, 227, 161); // Green
    int textMain = COLOR(205, 214, 244); // Text
    int textMuted = COLOR(166, 173, 200); // Subtext
    int coinColor = COLOR(249, 226, 175); // Gold
    int bombColor = COLOR(243, 139, 168); // Red
    int fishColor = COLOR(148, 226, 213); // Teal

    // ===== NEN TOAN MAN HINH =====
    my_bar(0, 0, 800, 600, bgPlay);

    // ===== HEADER (Chieu cao 60px) =====
    my_bar(0, 0, 800, 60, bgHeader);
    
    // Duong vien noi cho header
    veDuongThang(0, 61, 800, 61, borderColor);

    // TIEU DE (Dat o tren cung)
    setbkcolor(bgHeader);
    setcolor(titleColor);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    outtextxy(400, 20, (char*)"MEO HUNG DONG XU");

    // ===== THANH THONG SO (Nam duoi Tieu de) =====
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);

    // DIEM
    settextjustify(LEFT_TEXT, CENTER_TEXT);
    setcolor(scoreColor);
    sprintf(scoreStr, "DIEM: %d", state->diem);
    outtextxy(30, 45, scoreStr);

    // MANG (Dat o giua)
    setcolor(textMain);
    outtextxy(330, 45, (char*)"MANG:");
    for(i = 0; i < state->mang; i++) {
        veTraiTim(400 + i * 25, 45); 
    }

    // CAO NHAT
    settextjustify(RIGHT_TEXT, CENTER_TEXT);
    setcolor(coinColor);
    sprintf(highScoreStr, "CAO NHAT: %d", state->caoNhat);
    outtextxy(770, 45, highScoreStr);

    // ===== VUNG CHOI =====
    // Vien kep
    veDuongThang(10, 65, 790, 65, borderColor);
    veDuongThang(10, 440, 790, 440, borderColor);
    veDuongThang(10, 65, 10, 440, borderColor);
    veDuongThang(790, 65, 790, 440, borderColor);

    // ===== FOOTER (Tu y=445 tro xuong) =====
    my_bar(0, 445, 800, 600, bgHeader); 
    
    // Vien tren cua footer
    veDuongThang(0, 444, 800, 444, borderColor);

    setbkcolor(bgHeader);
    settextstyle(SMALL_FONT, HORIZ_DIR, 5);
    
    // LUAT CHOI (Ben trai)
    settextjustify(LEFT_TEXT, TOP_TEXT);
    setcolor(titleColor);
    outtextxy(20, 455, (char*)"LUAT CHOI:");
    
    setcolor(textMuted);
    outtextxy(20, 480, (char*)"- Phim [<-] [->]: Di chuyen MEO sang trai, phai.");
    outtextxy(20, 505, (char*)"- Luu y: Toc do roi tang theo diem. Het 3 mang la thua!");
    
    // CHU THICH ICON (Ben phai, moi cai 1 dong, tach xa ra de khong bi de chu)
    settextjustify(LEFT_TEXT, CENTER_TEXT);

    // Dong Xu
    veDongXu(580, 460);
    setbkcolor(bgHeader); setcolor(coinColor);
    outtextxy(620, 460, (char*)": +10 Diem");

    // Xuong ca
    veXuongCa(580, 490);
    setcolor(fishColor);
    outtextxy(620, 490, (char*)": -5 Diem");

    // Bom
    veBom(580, 520);
    setcolor(bombColor);
    outtextxy(620, 520, (char*)": -1 Mang");
}

void capNhatVatThe(struct GiaoDien_State* state) {
    int i;
    int tocDo = 5 + (state->diem / 50); 
    if(tocDo > 18) tocDo = 18; // Tang gioi han toc do cho hop voi chieu cao moi

    for(i = 0; i < 5; i++) {
        if(state->cacVatThe[i].active) {
            state->cacVatThe[i].y += tocDo;
            if(state->cacVatThe[i].y > 420) { // Duoi day cua vung choi (440)
                state->cacVatThe[i].active = false;
            }
        } else {
            if(rand() % 100 < 5) {
                state->cacVatThe[i].active = true;
                state->cacVatThe[i].x = 40 + rand() % 720; 
                state->cacVatThe[i].y = 75; // Tu dinh vung choi (65)
                
                int r = rand() % 100;
                if(r < 60) state->cacVatThe[i].loai = 0;      
                else if(r < 85) state->cacVatThe[i].loai = 2; 
                else state->cacVatThe[i].loai = 1;            
            }
        }
    }
}

void xuLyVaCham(struct GiaoDien_State* state) {
    int i;
    for(i = 0; i < 5; i++) {
        if(state->cacVatThe[i].active) {
            if(abs(state->cacVatThe[i].x - state->meoX) < 30 && abs(state->cacVatThe[i].y - state->meoY) < 30) {
                state->cacVatThe[i].active = false;
                
                if(state->cacVatThe[i].loai == 0) { 
                    state->diem += 10;
                } else if(state->cacVatThe[i].loai == 1) { 
                    state->mang -= 1;
                    if(state->mang <= 0) state->gameOver = true;
                } else if(state->cacVatThe[i].loai == 2) { 
                    state->diem -= 5;
                    if(state->diem < 0) state->diem = 0;
                }
            }
        }
    }
}

void playGiaoDien(struct GiaoDien_State* state) {
    int trang = 0;
    int i;
    
    initGiaoDien(state);
    srand(time(NULL));

    while(!state->gameOver) {
        setactivepage(trang);

        veNenKhung(state);

        if(kbhit()) {
            int key = getch();
            if(key == 224) key = getch(); 
            
            if(key == 27) { // ESC
                state->gameOver = true;
            } else if(key == 75) { // Trai
                state->meoX -= 35; // Tang toc do di chuyen cho hop voi man hinh lon
                if(state->meoX < 40) state->meoX = 40;
            } else if(key == 77) { // Phai
                state->meoX += 35;
                if(state->meoX > 760) state->meoX = 760;
            }
        }

        capNhatVatThe(state);
        xuLyVaCham(state);

        for(i = 0; i < 5; i++) {
            if(state->cacVatThe[i].active) {
                if(state->cacVatThe[i].loai == 0) veDongXu(state->cacVatThe[i].x, state->cacVatThe[i].y);
                else if(state->cacVatThe[i].loai == 1) veBom(state->cacVatThe[i].x, state->cacVatThe[i].y);
                else if(state->cacVatThe[i].loai == 2) veXuongCa(state->cacVatThe[i].x, state->cacVatThe[i].y);
            }
        }

        veMeo(state->meoX, state->meoY);

        setvisualpage(trang);
        
        trang = 1 - trang;

        delay(40); // Giam delay 1 chut de game chay muot hon
    }
    
    setactivepage(trang);
    veNenKhung(state);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 5);
    setcolor(RED);
    outtextxy(400, 250, (char*)"GAME OVER");
    setvisualpage(trang);
    
    if(state->diem > state->caoNhat) {
        FILE *f = fopen("highscore.txt", "w");
        if(f) {
            fprintf(f, "%d", state->diem);
            fclose(f);
        }
    }
    
    getch();
}
