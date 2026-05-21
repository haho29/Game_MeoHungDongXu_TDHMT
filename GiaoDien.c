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
#include <windows.h>
#include <mmsystem.h>
#include <string.h>

void initGiaoDien(struct GiaoDien_State* state, int skin, int phuKien, int xu) {
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

    state->meoX = 500;
    state->meoX_d = 500.0;
    state->meoY = 515;
    state->meoVx = 0;
    state->meoQuayTrai = false;
    state->playTimeSec = 0.0;
    
    state->dangSkin = skin;
    state->dangPhuKien = phuKien;
    state->tongXuTichLuy = xu;
    state->khienBaoVe = 0;
    state->thoiGianNamCham = 0;
    
    state->gameOver = false;
    
    for(i = 0; i < SO_VAT_THE; i++) state->cacVatThe[i].active = false;
    for(i = 0; i < SO_HAT; i++) state->cacHat[i].active = false;
    for(i = 0; i < SO_CHU_NOI; i++) state->cacChuNoi[i].active = false;
}

static void playSoundEffect(const char* filename, const char* alias, int fallbackFreq, int fallbackDuration) {
    char exePath[MAX_PATH];
    GetModuleFileNameA(NULL, exePath, MAX_PATH);
    char* lastSlash = strrchr(exePath, '\\');
    if (lastSlash != NULL) *lastSlash = '\0';
    
    char fullPath[MAX_PATH];
    sprintf(fullPath, "%s\\%s", exePath, filename);
    
    char closeCmd[100];
    char openCmd[MAX_PATH + 100];
    char playCmd[100];
    
    sprintf(closeCmd, "close %s", alias);
    sprintf(openCmd, "open \"%s\" type waveaudio alias %s", fullPath, alias);
    sprintf(playCmd, "play %s", alias);
    
    mciSendString(closeCmd, NULL, 0, NULL);
    if (mciSendString(openCmd, NULL, 0, NULL) == 0) {
        mciSendString(playCmd, NULL, 0, NULL);
    } else {
        if (strcmp(filename, "coin.wav") == 0) {
            sprintf(fullPath, "%s\\coin_1.wav", exePath);
            sprintf(openCmd, "open \"%s\" type waveaudio alias %s", fullPath, alias);
            if (mciSendString(openCmd, NULL, 0, NULL) == 0) {
                mciSendString(playCmd, NULL, 0, NULL);
                return;
            }
        }
        Beep(fallbackFreq, fallbackDuration);
    }
}

void taoHatBo(struct GiaoDien_State* state, int x, int y, int soLuong, int mauSac1, int mauSac2) {
    int count = 0;
    for(int i = 0; i < SO_HAT && count < soLuong; i++) {
        if(!state->cacHat[i].active) {
            state->cacHat[i].active = true;
            state->cacHat[i].x = x;
            state->cacHat[i].y = y;
            double angle = (rand() % 360) * 3.14159 / 180.0;
            double speed = 2.0 + (rand() % 40) / 10.0;
            state->cacHat[i].vx = speed * cos(angle);
            state->cacHat[i].vy = speed * sin(angle);
            state->cacHat[i].color = (rand() % 2 == 0) ? mauSac1 : mauSac2;
            state->cacHat[i].life = 20 + rand() % 15;
            count++;
        }
    }
}

void taoChuNoi(struct GiaoDien_State* state, int x, int y, const char* text, int color) {
    for(int i = 0; i < SO_CHU_NOI; i++) {
        if(!state->cacChuNoi[i].active) {
            state->cacChuNoi[i].active = true;
            state->cacChuNoi[i].x = x;
            state->cacChuNoi[i].y = y;
            strcpy(state->cacChuNoi[i].text, text);
            state->cacChuNoi[i].color = color;
            state->cacChuNoi[i].life = 30; // 30 khung hinh
            break;
        }
    }
}

void capNhatVatThe(struct GiaoDien_State* state) {
    int i;
    int tocDo = 5 + (state->diem / 50); 
    if(tocDo > 18) tocDo = 18; 

    for(i = 0; i < SO_VAT_THE; i++) {
        if(state->cacVatThe[i].active) {
            // Logic nam cham hut xu
            if(state->thoiGianNamCham > 0 && 
              (state->cacVatThe[i].loai == 0 || state->cacVatThe[i].loai == 3 || state->cacVatThe[i].loai == 4)) {
                int dx = state->meoX - state->cacVatThe[i].x;
                int dy = state->meoY - state->cacVatThe[i].y;
                double dist = sqrt(dx*dx + dy*dy);
                if(dist < 300) {
                    state->cacVatThe[i].x += (int)(8.0 * dx / dist);
                    state->cacVatThe[i].y += (int)(8.0 * dy / dist);
                } else {
                    state->cacVatThe[i].y += tocDo;
                }
            } else {
                state->cacVatThe[i].y += tocDo;
            }
            
            if(state->cacVatThe[i].y > 520) { 
                state->cacVatThe[i].active = false;
            }
        } else {
            bool tooCloseVertically = false;
            for(int j = 0; j < SO_VAT_THE; j++) {
                if(state->cacVatThe[j].active && state->cacVatThe[j].y < 135) { 
                    tooCloseVertically = true; break;
                }
            }
            
            if(!tooCloseVertically && rand() % 100 < 8) { 
                int spawnedX = 40 + rand() % 920; 
                state->cacVatThe[i].active = true;
                state->cacVatThe[i].x = spawnedX;
                state->cacVatThe[i].y = 75;
                
                int r = rand() % 1000;
                // Ti le moi: Xu=55%, Bom=25%, Xuong=13%, Khien=3%, NamCham=3%, Tim=1%
                if(r < 300) state->cacVatThe[i].loai = 0;      
                else if(r < 450) state->cacVatThe[i].loai = 3; 
                else if(r < 550) state->cacVatThe[i].loai = 4; 
                else if(r < 680) state->cacVatThe[i].loai = 2; // Xuong ca
                else if(r < 930) state->cacVatThe[i].loai = 1; // Bom
                else if(r < 960) state->cacVatThe[i].loai = 6; // Khien
                else if(r < 990) state->cacVatThe[i].loai = 7; // Nam cham
                else state->cacVatThe[i].loai = 5;             // Tim
            }
        }
    }
}

void xuLyVaCham(struct GiaoDien_State* state) {
    int i;
    for(i = 0; i < SO_VAT_THE; i++) {
        if(state->cacVatThe[i].active) {
            if(abs(state->cacVatThe[i].x - state->meoX) < 40 && abs(state->cacVatThe[i].y - state->meoY) < 35) {
                state->cacVatThe[i].active = false;
                
                int vType = state->cacVatThe[i].loai;
                if(vType == 0 || vType == 3 || vType == 4) { 
                    int d = (vType == 0) ? 10 : (vType == 3 ? 20 : 30);
                    state->diem += d;
                    state->tongXuTichLuy += d; // Cong vao xu luon
                    
                    char s[10]; sprintf(s, "+%d", d);
                    taoChuNoi(state, state->meoX, state->meoY - 40, s, COLOR(255, 215, 0));
                    taoHatBo(state, state->meoX, state->meoY, 10, COLOR(255, 215, 0), COLOR(255, 255, 200));
                    playSoundEffect("coin.wav", "coinSound", 1000 + d*10, 50);
                    
                } else if(vType == 1) { // Bom
                    if(state->khienBaoVe > 0) {
                        state->khienBaoVe = 0;
                        taoChuNoi(state, state->meoX, state->meoY - 40, "KHIEN!", COLOR(100, 255, 255));
                        taoHatBo(state, state->meoX, state->meoY, 20, COLOR(100, 200, 255), COLOR(255, 255, 255));
                        playSoundEffect("shield_break.wav", "shieldBreak", 400, 150);
                    } else {
                        state->mang -= 1;
                        taoChuNoi(state, state->meoX, state->meoY - 40, "-1 MANG", COLOR(255, 50, 50));
                        taoHatBo(state, state->meoX, state->meoY, 20, COLOR(255, 50, 50), COLOR(255, 150, 0));
                        playSoundEffect("bomb.wav", "bombSound", 150, 300);
                        if(state->mang <= 0) state->gameOver = true;
                    }
                } else if(vType == 2) { // Xuong ca
                    state->diem -= 5;
                    if(state->diem < 0) state->diem = 0;
                    taoChuNoi(state, state->meoX, state->meoY - 40, "-5", COLOR(200, 200, 200));
                    playSoundEffect("bone.wav", "boneSound", 300, 100);
                    
                } else if(vType == 5) { // Tim
                    if(state->mang < 5) state->mang++;
                    taoChuNoi(state, state->meoX, state->meoY - 40, "+1 TIM", COLOR(255, 100, 150));
                    taoHatBo(state, state->meoX, state->meoY, 15, COLOR(255, 100, 150), COLOR(255, 200, 220));
                    playSoundEffect("heal.wav", "healSound", 1500, 150);
                    
                } else if(vType == 6) { // Khien
                    state->khienBaoVe = 1;
                    taoChuNoi(state, state->meoX, state->meoY - 40, "BAO VE", COLOR(100, 255, 255));
                    playSoundEffect("shield_up.wav", "shieldUp", 1200, 100);
                    
                } else if(vType == 7) { // Nam cham
                    state->thoiGianNamCham = 150; // 150 khung hinh
                    taoChuNoi(state, state->meoX, state->meoY - 40, "HUT XU", COLOR(255, 100, 100));
                }
            }
        }
    }
}

void capNhatVaVeHieuUng(struct GiaoDien_State* state) {
    // Hat
    for(int i = 0; i < SO_HAT; i++) {
        if(state->cacHat[i].active) {
            state->cacHat[i].x += (int)state->cacHat[i].vx;
            state->cacHat[i].y += (int)state->cacHat[i].vy;
            state->cacHat[i].vy += 0.2; // Trong luc nhe
            state->cacHat[i].life--;
            
            if(state->cacHat[i].life <= 0) state->cacHat[i].active = false;
            else my_bar(state->cacHat[i].x, state->cacHat[i].y, state->cacHat[i].x+2, state->cacHat[i].y+2, state->cacHat[i].color);
        }
    }
    
    // Chu noi
    for(int i = 0; i < SO_CHU_NOI; i++) {
        if(state->cacChuNoi[i].active) {
            state->cacChuNoi[i].y -= 2; // Bay len
            state->cacChuNoi[i].life--;
            
            if(state->cacChuNoi[i].life <= 0) state->cacChuNoi[i].active = false;
            else {
                setbkcolor(COLOR(25, 15, 45)); // BG sky
                setcolor(state->cacChuNoi[i].color);
                settextstyle(BOLD_FONT, HORIZ_DIR, 1);
                settextjustify(CENTER_TEXT, CENTER_TEXT);
                outtextxy(state->cacChuNoi[i].x, state->cacChuNoi[i].y, state->cacChuNoi[i].text);
            }
        }
    }
}

void playGiaoDien(struct GiaoDien_State* state) {
    int trang = 0;
    int delayTime = 30; 
    bool isPaused = false;
    bool lastZeroState = false; // Trạng thái phím 0 ở frame trước
    
    srand(time(NULL));

    while(!state->gameOver) {
        // Tương tác người dùng: Đa dạng tốc độ (0, 1, 2, 3)
        bool currentZeroState = (GetAsyncKeyState('0') & 0x8000) != 0;
        if(currentZeroState && !lastZeroState) {
            isPaused = !isPaused; // Toggle Tạm Dừng
        }
        lastZeroState = currentZeroState;

        if(GetAsyncKeyState('1') & 0x8000) { isPaused = false; delayTime = 45; } // 1-Chậm
        if(GetAsyncKeyState('2') & 0x8000) { isPaused = false; delayTime = 25; } // 2-Nhanh
        if(GetAsyncKeyState('3') & 0x8000) { isPaused = false; delayTime = 12; } // 3-Nhanh hơn
        
        // Xy ly ESC
        if(GetAsyncKeyState(VK_ESCAPE) & 0x8000) state->gameOver = true;
        
        if (isPaused) {
            setactivepage(trang);
            veNenKhung(state); // Vẽ nền tĩnh
            
            // Vẽ lớp mờ & Chữ Pause sắc nét (Sử dụng outtextxy)
            settextjustify(CENTER_TEXT, CENTER_TEXT);
            
            // Đổ bóng chữ
            setbkcolor(COLOR(25, 15, 45)); 
            setcolor(COLOR(50, 50, 50));
            settextstyle(BOLD_FONT, HORIZ_DIR, 5);
            outtextxy(504, 354, "TAM DUNG");
            settextstyle(BOLD_FONT, HORIZ_DIR, 2);
            outtextxy(502, 412, "Nhan 0 de tiep tuc");
            
            // Chữ chính
            setcolor(COLOR(255, 215, 0));
            settextstyle(BOLD_FONT, HORIZ_DIR, 5);
            outtextxy(500, 350, "TAM DUNG");
            setcolor(COLOR(255, 255, 255));
            settextstyle(BOLD_FONT, HORIZ_DIR, 2);
            outtextxy(500, 410, "Nhan 0 de tiep tuc");
            
            setvisualpage(trang);
            trang = 1 - trang;
            delay(50);
            continue;
        }

        state->playTimeSec += 0.03;
        if(state->thoiGianNamCham > 0) state->thoiGianNamCham--;

        // Xu ly di chuyen muot voi GetAsyncKeyState (Phim Mui Ten)
        if(GetAsyncKeyState(VK_LEFT) & 0x8000) {
            state->meoVx -= 2.0;
            state->meoQuayTrai = true;
        } else if(GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            state->meoVx += 2.0;
            state->meoQuayTrai = false;
        } else {
            // Quan tinh
            state->meoVx *= 0.8;
        }
        
        // Gioi han van toc
        if(state->meoVx > 12.0) state->meoVx = 12.0;
        if(state->meoVx < -12.0) state->meoVx = -12.0;
        
        state->meoX_d += state->meoVx;
        if(state->meoX_d < 40) { state->meoX_d = 40; state->meoVx = 0; }
        if(state->meoX_d > 960) { state->meoX_d = 960; state->meoVx = 0; }
        state->meoX = (int)state->meoX_d;

        setactivepage(trang);
        veNenKhung(state);

        capNhatVatThe(state);
        xuLyVaCham(state);

        // Ve vat the
        for(int i = 0; i < SO_VAT_THE; i++) {
            if(state->cacVatThe[i].active) {
                int vx = state->cacVatThe[i].x;
                int vy = state->cacVatThe[i].y;
                int type = state->cacVatThe[i].loai;
                
                if(type == 0) veDongXu(vx, vy, 10, 10);
                else if(type == 3) veDongXu(vx, vy, 12, 20);
                else if(type == 4) veDongXu(vx, vy, 14, 30);
                else if(type == 1) {
                    double scale = 1.0 + 0.15 * sin(vy * 0.1); 
                    veBom(vx, vy, scale);
                }
                else if(type == 2) {
                    double angle = vy * 0.05; 
                    veXuongCa(vx, vy, angle);
                }
                else if(type == 5) {
                    veTraiTim(vx, vy); // Tai su dung
                }
                else if(type == 6) {
                    double angle = vy * 0.1;
                    double scale = 1.0 + 0.1 * sin(state->playTimeSec * 10);
                    veKhiNangLuong(vx, vy, angle, scale);
                }
                else if(type == 7) {
                    double angle = sin(state->playTimeSec * 5) * 0.5;
                    veNamCham(vx, vy, angle);
                }
            }
        }
        
        capNhatVaVeHieuUng(state);

        veMeoCoPhuKien(state->meoX, state->meoY, state->meoQuayTrai, state->playTimeSec, 
                       state->dangSkin, state->dangPhuKien, (state->khienBaoVe > 0));

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
    
    // Luu file shop_data
    FILE *fs = fopen("shop_data.txt", "w");
    if(fs) {
        fprintf(fs, "%d %d %d\n", state->tongXuTichLuy, state->dangSkin, state->dangPhuKien);
        fclose(fs);
    }
    
    hienThiManHinhKetThuc(state, trang, isNewHigh);
}
