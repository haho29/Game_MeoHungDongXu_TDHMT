#include "GiaoDien.h"
#include "TraiTim.h"
#include "Meo.h"
#include "VatThe.h"
#include "VeHinh.h"
#include "VeNenKhung.h"
#include "ManHinhKetThuc.h"
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <windows.h> // De su dung Beep() cho am thanh

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

void capNhatVatThe(struct GiaoDien_State* state) {
    int i;
    int tocDo = 5 + (state->diem / 50); 
    if(tocDo > 18) tocDo = 18; // Tang gioi han toc do cho hop voi chieu cao moi

    for(i = 0; i < 5; i++) {
        if(state->cacVatThe[i].active) {
            state->cacVatThe[i].y += tocDo;
            if(state->cacVatThe[i].y > 420) { // Duoi day cua vung choi
                state->cacVatThe[i].active = false;
            }
        } else {
            bool tooClose = false;
            for(int j = 0; j < 5; j++) {
                if(state->cacVatThe[j].active && state->cacVatThe[j].y < 140) { 
                    tooClose = true;
                    break;
                }
            }
            
            if(!tooClose && rand() % 100 < 5) {
                state->cacVatThe[i].active = true;
                state->cacVatThe[i].x = 40 + rand() % 720; 
                state->cacVatThe[i].y = 75; // Tu dinh vung choi
                
                int r = rand() % 100;
                if(r < 40) state->cacVatThe[i].loai = 0;      // 40%: 10 diem
                else if(r < 60) state->cacVatThe[i].loai = 3; // 20%: 20 diem
                else if(r < 70) state->cacVatThe[i].loai = 4; // 10%: 30 diem
                else if(r < 90) state->cacVatThe[i].loai = 2; // 20%: Xuong ca
                else state->cacVatThe[i].loai = 1;            // 10%: Bom
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
                    Beep(1000, 50); // Am thanh vang cao khi an xu
                } else if(state->cacVatThe[i].loai == 3) { 
                    state->diem += 20;
                    Beep(1200, 50); // Xu lon am cao hon
                } else if(state->cacVatThe[i].loai == 4) { 
                    state->diem += 30;
                    Beep(1400, 50); // Xu khong lo
                } else if(state->cacVatThe[i].loai == 1) { 
                    state->mang -= 1;
                    Beep(150, 300); // Am tram, dai khi no bom
                    if(state->mang <= 0) state->gameOver = true;
                } else if(state->cacVatThe[i].loai == 2) { 
                    state->diem -= 5;
                    Beep(300, 100); // Am thap khi dung xuong ca
                    if(state->diem < 0) state->diem = 0;
                }
            }
        }
    }
}

void playGiaoDien(struct GiaoDien_State* state) {
    int trang = 0;
    int i;
    int delayTime = 40; // Bien toc do de dieu khien
    bool isPaused = false;
    
    initGiaoDien(state);
    srand(time(NULL));

    while(!state->gameOver) {
        if(kbhit()) {
            int key = getch();
            if(key == 224) key = getch(); 
            
            if(key == 27) { // ESC
                state->gameOver = true;
            } else if(key == 75 && !isPaused) { // Trai
                state->meoX -= 35;
                if(state->meoX < 40) state->meoX = 40;
            } else if(key == 77 && !isPaused) { // Phai
                state->meoX += 35;
                if(state->meoX > 760) state->meoX = 760;
            } else if(key == '0') {
                isPaused = !isPaused; // 0: Dung/Tiep tuc
            } else if(key == '1') {
                delayTime = 70; // 1: Cham
            } else if(key == '2') {
                delayTime = 40; // 2: Nhanh/Binh thuong
            } else if(key == '3') {
                delayTime = 20; // 3: Nhanh hon
            }
        }

        if(isPaused) {
            delay(50);
            continue; // Dung vong lap cap nhat khi Pause
        }

        setactivepage(trang);

        veNenKhung(state);

        capNhatVatThe(state);
        xuLyVaCham(state);

        for(i = 0; i < 5; i++) {
            if(state->cacVatThe[i].active) {
                if(state->cacVatThe[i].loai == 0) veDongXu(state->cacVatThe[i].x, state->cacVatThe[i].y, 10, 10);
                else if(state->cacVatThe[i].loai == 3) veDongXu(state->cacVatThe[i].x, state->cacVatThe[i].y, 12, 20);
                else if(state->cacVatThe[i].loai == 4) veDongXu(state->cacVatThe[i].x, state->cacVatThe[i].y, 14, 30);
                else if(state->cacVatThe[i].loai == 1) {
                    double scale = 1.0 + 0.15 * sin(state->cacVatThe[i].y * 0.1); // Hieu ung pulse (phinh to thu nho)
                    veBom(state->cacVatThe[i].x, state->cacVatThe[i].y, scale);
                }
                else if(state->cacVatThe[i].loai == 2) {
                    double angle = state->cacVatThe[i].y * 0.05; // Xoay dua tren y
                    veXuongCa(state->cacVatThe[i].x, state->cacVatThe[i].y, angle);
                }
            }
        }

        veMeo(state->meoX, state->meoY);

        setvisualpage(trang);
        
        trang = 1 - trang;

        delay(delayTime);
    }
    
    bool isNewHigh = false;
    if(state->diem > state->caoNhat) {
        FILE *f = fopen("highscore.txt", "w");
        if(f) {
            fprintf(f, "%d\n", state->diem);
            fclose(f);
            state->caoNhat = state->diem;
            isNewHigh = true;
        }
    }
    
    // Hien thi man hinh ket thuc thong qua module rieng biet
    hienThiManHinhKetThuc(state, trang, isNewHigh);
}
