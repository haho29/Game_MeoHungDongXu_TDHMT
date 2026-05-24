#include <graphics.h>
#include <conio.h>
#include <stdbool.h>
#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <string.h>

#include "GiaoDien.h"
#include "ManHinhBatDau.h"

#pragma comment(lib, "winmm.lib")

// =====================================================
// HAM PHAT NHAC NEN
// =====================================================
void phatNhacNen() {

    char exePath[MAX_PATH];

    // Lay duong dan file exe
    GetModuleFileNameA(NULL, exePath, MAX_PATH);

    // Cat ten file exe
    char* lastSlash = strrchr(exePath, '\\');

    if (lastSlash != NULL) {
        *lastSlash = '\0';
    }

    // Tao duong dan file nhac
    char fullPath[MAX_PATH];

    sprintf(fullPath, "%s\\nhacnen.wav", exePath);

    printf("\n=========================================\n");
    printf("          KIEM TRA AM THANH\n");
    printf("=========================================\n");
    printf("Thu muc game : %s\n", exePath);
    printf("File nhac    : %s\n", fullPath);

    // Kiem tra file ton tai
    FILE* f = fopen(fullPath, "rb");

    if (f == NULL) {

        printf("KHONG TIM THAY FILE nhacnen.wav\n");
        printf("Hay dat file vao cung thu muc voi file .exe\n");
        printf("=========================================\n");

        return;
    }

    fclose(f);

    printf("DA TIM THAY FILE NHAC\n");

    // Phat nhac
    BOOL ketQua = PlaySoundA(
        fullPath,
        NULL,
        SND_FILENAME | SND_ASYNC | SND_LOOP
    );

    if (ketQua) {

        printf("PHAT NHAC THANH CONG!\n");

    } else {

        printf("PHAT NHAC THAT BAI!\n");
        printf("Kiem tra lai dinh dang WAV\n");
        printf("Nen dung WAV PCM 16bit\n");
    }

    printf("=========================================\n");
}

// =====================================================
// HAM DUNG NHAC
// =====================================================
void dungNhacNen() {

    PlaySoundA(NULL, NULL, 0);
}

// =====================================================
// MAIN
// =====================================================
int main() {

    struct GiaoDien_State gdien;

    // Tao cua so game
    initwindow(1150, 750, "Meo Hung Dong Xu");

    // Delay tranh loi audio
    delay(500);

    // Phat nhac nen
    phatNhacNen();

    // =================================================
    // VONG LAP GAME
    // =================================================
    while (true) {

        int skin = 0, phuKien = 0, xu = 0;
        // Hien thi man hinh bat dau
        int chonBatDau = hienThiManHinhBatDau(&skin, &phuKien, &xu);

        // Neu chon thoat
        if (chonBatDau == 0) {
            break;
        }

        // Khoi tao state cua game
        initGiaoDien(&gdien, skin, phuKien, xu);

        // Chay game
        playGiaoDien(&gdien);
    }

    // =================================================
    // THOAT GAME
    // =================================================

    // Tat nhac
    dungNhacNen();

    // Dong graphics
    closegraph();

    return 0;
}
