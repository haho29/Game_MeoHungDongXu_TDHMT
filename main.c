#include <graphics.h>
#include <conio.h>
#include "GiaoDien.h"

int main() {
    struct GiaoDien_State gdien;
    
    initwindow(800, 600, "Meo Hung Dong Xu");

    playGiaoDien(&gdien);

    closegraph();
    return 0;
}
