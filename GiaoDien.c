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
            if(rand() % 100 < 5) {
                state->cacVatThe[i].active = true;
                state->cacVatThe[i].x = 40 + rand() % 720; 
                state->cacVatThe[i].y = 75; // Tu dinh vung choi
                
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
                state->meoX -= 35; // Tang toc do di chuyen
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

        delay(40);
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
