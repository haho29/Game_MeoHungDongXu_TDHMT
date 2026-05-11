#include "Meo.h"
#include "VeHinh.h"
#include <graphics.h>

void veMeo(int x, int y) {
    int color = COLOR(245, 194, 231); // Pastel Pink
    int eyeColor = COLOR(17, 17, 27); // Dark
    int noseColor = COLOR(243, 139, 168); // Soft Red

    // Duoi (Tail)
    veDuongThang(x + 15, y + 5, x + 30, y - 5, color);
    veDuongThang(x + 30, y - 5, x + 35, y + 5, color);
    
    // Than (Body)
    veHinhElip(x, y + 18, 22, 16, color);
    toMauDeQuy(x, y + 18, color, color);

    // Dau (Head)
    veHinhElip(x, y, 18, 14, color);
    toMauDeQuy(x, y, color, color);

    // Tai trai (Left Ear)
    veDuongThang(x - 15, y - 5, x - 20, y - 18, color);
    veDuongThang(x - 20, y - 18, x - 6, y - 10, color);
    veDuongThang(x - 6, y - 10, x - 15, y - 5, color);
    toMauDeQuy(x - 14, y - 11, color, color); 

    // Tai phai (Right Ear)
    veDuongThang(x + 15, y - 5, x + 20, y - 18, color);
    veDuongThang(x + 20, y - 18, x + 6, y - 10, color);
    veDuongThang(x + 6, y - 10, x + 15, y - 5, color);
    toMauDeQuy(x + 14, y - 11, color, color); 

    // Mat (Eyes)
    veDuongTron(x - 6, y - 2, 2, eyeColor);
    toMauDeQuy(x - 6, y - 2, eyeColor, eyeColor);
    
    veDuongTron(x + 6, y - 2, 2, eyeColor);
    toMauDeQuy(x + 6, y - 2, eyeColor, eyeColor);

    // Mui (Nose)
    veHinhElip(x, y + 4, 3, 2, noseColor);
    toMauDeQuy(x, y + 4, noseColor, noseColor);
}
