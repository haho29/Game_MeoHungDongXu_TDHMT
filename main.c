#include <graphics.h>
#include <conio.h>
#include <stdbool.h>
#include "GiaoDien.h"
#include "ManHinhBatDau.h"

int main() {
    struct GiaoDien_State gdien;
    
    initwindow(800, 600, "Meo Hung Dong Xu");

    while (true) {
        int chonBatDau = hienThiManHinhBatDau();
        if (chonBatDau == 0) {
            break; // Thoat
        }
        
        playGiaoDien(&gdien);
    }

    closegraph();
    return 0;
}
