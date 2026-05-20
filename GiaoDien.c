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
#include <mmsystem.h> // De su dung mciSendString() phat am thanh hieu ung

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

    state->meoX = 500; // Giua man hinh 1000
    state->meoY = 515; // Gan day cua vung choi (540)
    state->gameOver = false;
    
    for(i = 0; i < SO_VAT_THE; i++) {
        state->cacVatThe[i].active = false;
    }
}

void capNhatVatThe(struct GiaoDien_State* state) {
    int i;
    int tocDo = 5 + (state->diem / 50); 
    if(tocDo > 18) tocDo = 18; // Tang gioi han toc do cho hop voi chieu cao moi

    for(i = 0; i < SO_VAT_THE; i++) {
        if(state->cacVatThe[i].active) {
            state->cacVatThe[i].y += tocDo;
            if(state->cacVatThe[i].y > 520) { // Duoi day cua vung choi (540)
                state->cacVatThe[i].active = false;
            }
        } else {
            // De tranh vat the roi trung chong hoac qua gan nhau theo chieu doc khi sinh
            bool tooCloseVertically = false;
            for(int j = 0; j < SO_VAT_THE; j++) {
                if(state->cacVatThe[j].active && state->cacVatThe[j].y < 135) { 
                    tooCloseVertically = true;
                    break;
                }
            }
            
            if(!tooCloseVertically && rand() % 100 < 8) { // Tang ty le sinh len 8% thay vi 5%
                int spawnedX = 0;
                int attempts = 0;
                bool validX = false;
                
                while(attempts < 15 && !validX) {
                    spawnedX = 40 + rand() % 920; // phu hop voi chieu rong 1000
                    validX = true;
                    
                    // Kiem tra khoang cach ngang voi tat ca cac vat the dang roi o nua tren man hinh
                    for(int j = 0; j < SO_VAT_THE; j++) {
                        if(state->cacVatThe[j].active && state->cacVatThe[j].y < 340) {
                            if(abs(spawnedX - state->cacVatThe[j].x) < 150) {
                                validX = false; // X qua gan vat the j
                                break;
                            }
                        }
                    }
                    attempts++;
                }
                
                if(validX) {
                    state->cacVatThe[i].active = true;
                    state->cacVatThe[i].x = spawnedX;
                    state->cacVatThe[i].y = 75; // Tu dinh vung choi
                    
                    int r = rand() % 100;
                    // Tang dang ke xac suat bom len 25% (truoc day la 10%)
                    if(r < 35) state->cacVatThe[i].loai = 0;      // 35%: Dong xu 10 diem
                    else if(r < 50) state->cacVatThe[i].loai = 3; // 15%: Dong xu 20 diem
                    else if(r < 60) state->cacVatThe[i].loai = 4; // 10%: Dong xu 30 diem
                    else if(r < 75) state->cacVatThe[i].loai = 2; // 15%: Xuong ca (-5đ)
                    else state->cacVatThe[i].loai = 1;            // 25%: Bom (-1 mang)
                }
            }
        }
    }
}

static void playSoundEffect(const char* filename, const char* alias, int fallbackFreq, int fallbackDuration) {
    char exePath[MAX_PATH];
    GetModuleFileNameA(NULL, exePath, MAX_PATH);
    char* lastSlash = strrchr(exePath, '\\');
    if (lastSlash != NULL) {
        *lastSlash = '\0';
    }
    
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
        // Fallback tìm tên thay thế coin_1.wav nếu không tìm thấy coin.wav
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

void xuLyVaCham(struct GiaoDien_State* state) {
    int i;
    for(i = 0; i < SO_VAT_THE; i++) {
        if(state->cacVatThe[i].active) {
            if(abs(state->cacVatThe[i].x - state->meoX) < 30 && abs(state->cacVatThe[i].y - state->meoY) < 30) {
                state->cacVatThe[i].active = false;
                
                if(state->cacVatThe[i].loai == 0 || state->cacVatThe[i].loai == 3 || state->cacVatThe[i].loai == 4) { 
                    // Cộng điểm tùy thuộc loại đồng xu
                    int freq = 1000;
                    if(state->cacVatThe[i].loai == 0) {
                        state->diem += 10;
                        freq = 1000;
                    } else if(state->cacVatThe[i].loai == 3) {
                        state->diem += 20;
                        freq = 1200;
                    } else {
                        state->diem += 30;
                        freq = 1400;
                    }

                    // Phát âm thanh đồng xu
                    playSoundEffect("coin.wav", "coinSound", freq, 50);
                } else if(state->cacVatThe[i].loai == 1) { 
                    state->mang -= 1;
                    
                    // Phát âm thanh nổ bom
                    playSoundEffect("bomb.wav", "bombSound", 150, 300);
                    
                    if(state->mang <= 0) state->gameOver = true;
                } else if(state->cacVatThe[i].loai == 2) { 
                    state->diem -= 5;
                    
                    // Phát âm thanh xương cá
                    playSoundEffect("bone.wav", "boneSound", 300, 100);
                    
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
        // =========================================================================
        // TIÊU CHÍ 5.2: TƯƠNG TÁC NGƯỜI DÙNG & ĐA DẠNG TỐC ĐỘ (Điều khiển game)
        // Xử lý mượt mà các phím điều khiển để dừng/điều chỉnh tốc độ trễ (delayTime) của game:
        // - Phím '0': Dừng game (Pause) / Tiếp tục chơi.
        // - Phím '1': Tốc độ Chậm (delayTime = 70ms).
        // - Phím '2': Tốc độ Nhanh/Bình thường (delayTime = 40ms).
        // - Phím '3': Tốc độ Nhanh hơn (delayTime = 20ms).
        // =========================================================================
        if(kbhit()) {
            int key = getch();
            if(key == 224) key = getch(); // Đọc mã mở rộng cho phím mũi tên
            
            if(key == 27) { // Phím ESC để thoát game
                state->gameOver = true;
            } else if(key == 75 && !isPaused) { // Phím mũi tên TRÁI -> Di chuyển mèo sang trái
                state->meoX -= 35;
                if(state->meoX < 40) state->meoX = 40;
            } else if(key == 77 && !isPaused) { // Phím mũi tên PHẢI -> Di chuyển mèo sang phải
                state->meoX += 35;
                if(state->meoX > 960) state->meoX = 960;
            } else if(key == '0') {
                isPaused = !isPaused; // Phím 0: Tạm dừng / Tiếp tục chơi
            } else if(key == '1') {
                delayTime = 70; // Phím 1: Chậm
            } else if(key == '2') {
                delayTime = 40; // Phím 2: Nhanh (Mặc định)
            } else if(key == '3') {
                delayTime = 20; // Phím 3: Nhanh hơn
            }
        }

        if(isPaused) {
            delay(50);
            continue; // Tạm ngưng cập nhật khung hình khi đang tạm dừng
        }

        setactivepage(trang);

        veNenKhung(state);

        // =========================================================================
        // TIÊU CHÍ 5.1: VẬN DỤNG CHUYỂN ĐỘNG AFFINE VÀO GAME
        // - Phép Tịnh Tiến (Translation): Di chuyển tịnh tiến vật thể rơi dọc trục Y: 
        //   y_next = y + tocDo. Cập nhật trong capNhatVatThe().
        // =========================================================================
        capNhatVatThe(state);
        
        // =========================================================================
        // TIÊU CHÍ 5.3: HIỆU ỨNG ÂM THANH KHI VA CHẠM / GHI ĐIỂM
        // - Nhặt đồng xu (10đ, 20đ, 30đ): Phát âm thanh tần số cao (1000Hz - 1400Hz) vui tai.
        // - Trúng bom: Phát âm thanh nổ trầm, kéo dài (150Hz trong 300ms) báo mất mạng.
        // - Ăn phải xương cá: Phát âm trầm ngắn (300Hz) cảnh báo trừ điểm.
        // =========================================================================
        xuLyVaCham(state);

        // Vẽ các vật thể đang rơi với các phép biến đổi hình học tương ứng
        for(i = 0; i < SO_VAT_THE; i++) {
            if(state->cacVatThe[i].active) {
                if(state->cacVatThe[i].loai == 0) veDongXu(state->cacVatThe[i].x, state->cacVatThe[i].y, 10, 10);
                else if(state->cacVatThe[i].loai == 3) veDongXu(state->cacVatThe[i].x, state->cacVatThe[i].y, 12, 20);
                else if(state->cacVatThe[i].loai == 4) veDongXu(state->cacVatThe[i].x, state->cacVatThe[i].y, 14, 30);
                else if(state->cacVatThe[i].loai == 1) {
                    // -----------------------------------------------------------------
                    // PHÉP BIẾN ĐỔI AFFINE: CO GIÃN (Scaling)
                    // Áp dụng hàm sin tuần hoàn dựa trên tọa độ y để tạo hiệu ứng
                    // quả bom phình to thu nhỏ (pulsing animation) liên tục cực sinh động.
                    // Sử dụng hàm PhepCoGian2D() để scale tọa độ từng đỉnh vẽ.
                    // -----------------------------------------------------------------
                    double scale = 1.0 + 0.15 * sin(state->cacVatThe[i].y * 0.1); 
                    veBom(state->cacVatThe[i].x, state->cacVatThe[i].y, scale);
                }
                else if(state->cacVatThe[i].loai == 2) {
                    // -----------------------------------------------------------------
                    // PHÉP BIẾN ĐỔI AFFINE: XOAY (Rotation)
                    // Tính toán góc quay liên tục thay đổi theo tọa độ y rơi của xương cá.
                    // Sử dụng hàm PhepQuay2D() để xoay xương cá quanh tâm hình học của nó.
                    // -----------------------------------------------------------------
                    double angle = state->cacVatThe[i].y * 0.05; 
                    veXuongCa(state->cacVatThe[i].x, state->cacVatThe[i].y, angle);
                }
            }
        }

        // Vẽ nhân vật mèo (Vị trí x thay đổi dựa trên phím bấm tịnh tiến của người chơi)
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
