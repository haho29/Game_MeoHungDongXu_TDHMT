#include "Meo.h"
#include "VeHinh.h"
#include <graphics.h>
#include <math.h>

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

void veMeoCoPhuKien(int x, int y, bool quayTrai, double timeSec, int skinLoai, int accessoryLoai, bool coKhien) {
    int color = COLOR(245, 194, 231); // Pastel Pink (Default)
    if(skinLoai == 1) color = COLOR(249, 168, 70); // Mướp vàng
    if(skinLoai == 2) color = COLOR(40, 40, 45);   // Mun đen
    if(skinLoai == 3) color = COLOR(250, 250, 255); // Mèo trắng

    int eyeColor = COLOR(17, 17, 27); // Dark
    if(skinLoai == 2) eyeColor = COLOR(255, 215, 0); // Mắt vàng cho mèo đen
    if(skinLoai == 3) eyeColor = COLOR(50, 150, 255); // Mắt xanh cho mèo trắng
    int noseColor = COLOR(243, 139, 168); // Soft Red
    
    // Tinh toan nhun nhay (Squash & Stretch) khi di chuyen
    double sy = 1.0 + 0.05 * sin(timeSec * 25.0); 
    int dy = y + (int)(18 * (1.0 - sy)); // ha thap trong tam neu bi bep
    
    // Macro de ho tro bien doi diem
    #define TRANSFORM_PT(px, py) do { \
        int ox = (px), oy = (py); \
        PhepCoGian2D(&ox, &oy, x, dy, 1.0, sy); \
        PhepDoiXung2D(&ox, &oy, x, quayTrai); \
        (px) = ox; (py) = oy; \
    } while(0)

    #define DRAW_LINE_T(x1, y1, x2, y2, col) do { \
        int p1x = x1, p1y = y1, p2x = x2, p2y = y2; \
        TRANSFORM_PT(p1x, p1y); TRANSFORM_PT(p2x, p2y); \
        veDuongThang(p1x, p1y, p2x, p2y, col); \
    } while(0)
    
    #define FILL_T(fx, fy, fillCol, boundCol) do { \
        int pfx = fx, pfy = fy; TRANSFORM_PT(pfx, pfy); \
        toMauDeQuy(pfx, pfy, fillCol, boundCol); \
    } while(0)


    
    // 1. Ve Duoi (Tail)
    double tailAngle = 0.3 * sin(timeSec * 15.0);
    int t1x = x + 16, t1y = dy - 8;
    int t2x = x + 28, t2y = dy - 18;
    int t3x = x + 35, t3y = dy - 10;
    PhepQuay2D(&t2x, &t2y, t1x, t1y, tailAngle);
    PhepQuay2D(&t3x, &t3y, t1x, t1y, tailAngle);
    for(int w = -2; w <= 2; w++) {
        DRAW_LINE_T(t1x+w, t1y, t2x+w, t2y, color);
        DRAW_LINE_T(t2x+w, t2y, t3x+w, t3y, color);
    }
    
    // 2. Chan sau (Back Legs)
    int blx = x - 12, bly = dy - 4; TRANSFORM_PT(blx, bly);
    veHinhElip(blx, bly, 5, (int)(4*sy), color); toMauDeQuy(blx, bly, color, color);
    int brx = x + 12, bry = dy - 4; TRANSFORM_PT(brx, bry);
    veHinhElip(brx, bry, 5, (int)(4*sy), color); toMauDeQuy(brx, bry, color, color);
    
    // 3. Tai (Ears)
    int e1x = x - 16, e1y = dy - 32;
    int e2x = x - 6,  e2y = dy - 40;
    int e3x = x - 18, e3y = dy - 55;
    DRAW_LINE_T(e1x, e1y, e2x, e2y, color); DRAW_LINE_T(e2x, e2y, e3x, e3y, color); DRAW_LINE_T(e3x, e3y, e1x, e1y, color);
    FILL_T(x - 14, dy - 42, color, color);
    
    int re1x = x + 16, re1y = dy - 32;
    int re2x = x + 6,  re2y = dy - 40;
    int re3x = x + 18, re3y = dy - 55;
    DRAW_LINE_T(re1x, re1y, re2x, re2y, color); DRAW_LINE_T(re2x, re2y, re3x, re3y, color); DRAW_LINE_T(re3x, re3y, re1x, re1y, color);
    FILL_T(x + 14, dy - 42, color, color);
    
    // 4. Than (Body)
    int cbx = x, cby = dy - 12; TRANSFORM_PT(cbx, cby);
    veHinhElip(cbx, cby, 16, (int)(12*sy), color); toMauDeQuy(cbx, cby, color, color);
    
    // 5. Chan truoc (Front Legs)
    int flx = x - 7, fly = dy - 2; TRANSFORM_PT(flx, fly);
    veHinhElip(flx, fly, 4, (int)(3*sy), color); toMauDeQuy(flx, fly, color, color);
    int frx = x + 7, fry = dy - 2; TRANSFORM_PT(frx, fry);
    veHinhElip(frx, fry, 4, (int)(3*sy), color); toMauDeQuy(frx, fry, color, color);
    
    // 6. Dau (Head)
    int chx = x, chy = dy - 28; TRANSFORM_PT(chx, chy);
    veHinhElip(chx, chy, 23, (int)(18*sy), color); toMauDeQuy(chx, chy, color, color);
    
    // 7. Khuon mat (Face)
    int white = COLOR(255, 255, 255);
    int blushCol = COLOR(255, 150, 180); // Ma hong
    int bllx = x - 14, blly = dy - 24; TRANSFORM_PT(bllx, blly);
    veHinhElip(bllx, blly, 4, (int)(2*sy), blushCol); toMauDeQuy(bllx, blly, blushCol, blushCol);
    int blrx = x + 14, blry = dy - 24; TRANSFORM_PT(blrx, blry);
    veHinhElip(blrx, blry, 4, (int)(2*sy), blushCol); toMauDeQuy(blrx, blry, blushCol, blushCol);

    if(accessoryLoai != 2) { // Mat bieng (Big anime eyes)
        int elx = x - 8, ely = dy - 27; TRANSFORM_PT(elx, ely);
        veHinhElip(elx, ely, 4, (int)(6*sy), eyeColor); toMauDeQuy(elx, ely, eyeColor, eyeColor);
        my_putpixel(elx - 1, ely - 2, white); my_putpixel(elx, ely - 2, white); 
        my_putpixel(elx - 1, ely - 3, white); my_putpixel(elx, ely - 3, white);
        my_putpixel(elx, ely + 3, white);
        
        int erx = x + 8, ery = dy - 27; TRANSFORM_PT(erx, ery);
        veHinhElip(erx, ery, 4, (int)(6*sy), eyeColor); toMauDeQuy(erx, ery, eyeColor, eyeColor);
        my_putpixel(erx - 1, ery - 2, white); my_putpixel(erx, ery - 2, white); 
        my_putpixel(erx - 1, ery - 3, white); my_putpixel(erx, ery - 3, white);
        my_putpixel(erx, ery + 3, white);
    } else { // Kinh ram
        int glassCol = COLOR(20, 20, 20);
        DRAW_LINE_T(x - 22, dy - 27, x + 22, dy - 27, glassCol); 
        DRAW_LINE_T(x - 22, dy - 26, x + 22, dy - 26, glassCol); 
        int glx = x - 9, gly = dy - 26; TRANSFORM_PT(glx, gly);
        veHinhElip(glx, gly, 7, (int)(5*sy), glassCol); toMauDeQuy(glx, gly, glassCol, glassCol);
        int grx = x + 9, gry = dy - 26; TRANSFORM_PT(grx, gry);
        veHinhElip(grx, gry, 7, (int)(5*sy), glassCol); toMauDeQuy(grx, gry, glassCol, glassCol);
    }

    // Mui
    int nx = x, ny = dy - 22; TRANSFORM_PT(nx, ny);
    veDuongTron(nx, ny, 1, noseColor); toMauDeQuy(nx, ny, noseColor, noseColor);
    
    // Mieng chu W
    DRAW_LINE_T(x - 4, dy - 20, x - 2, dy - 18, eyeColor);
    DRAW_LINE_T(x - 2, dy - 18, x, dy - 20, eyeColor);
    DRAW_LINE_T(x, dy - 20, x + 2, dy - 18, eyeColor);
    DRAW_LINE_T(x + 2, dy - 18, x + 4, dy - 20, eyeColor);
    
    // Rau
    DRAW_LINE_T(x - 17, dy - 25, x - 26, dy - 27, eyeColor);
    DRAW_LINE_T(x - 18, dy - 22, x - 27, dy - 22, eyeColor);
    DRAW_LINE_T(x + 17, dy - 25, x + 26, dy - 27, eyeColor);
    DRAW_LINE_T(x + 18, dy - 22, x + 27, dy - 22, eyeColor);

    // 8. Phu kien: Vuong Mien hoac No Do
    if(accessoryLoai == 1) {
        int crownCol = COLOR(255, 215, 0);
        int cwY = dy - 52 + (int)(3 * sin(timeSec * 5.0)); 
        DRAW_LINE_T(x - 10, cwY, x + 10, cwY, crownCol);
        DRAW_LINE_T(x - 10, cwY, x - 12, cwY - 10, crownCol);
        DRAW_LINE_T(x - 12, cwY - 10, x - 5, cwY - 4, crownCol);
        DRAW_LINE_T(x - 5, cwY - 4, x, cwY - 12, crownCol);
        DRAW_LINE_T(x, cwY - 12, x + 5, cwY - 4, crownCol);
        DRAW_LINE_T(x + 5, cwY - 4, x + 12, cwY - 10, crownCol);
        DRAW_LINE_T(x + 12, cwY - 10, x + 10, cwY, crownCol);
        FILL_T(x, cwY - 3, crownCol, crownCol);
    }
    else if(accessoryLoai == 3) { // No do (Red Bow tie)
        int bowCol = COLOR(220, 30, 50);
        
        DRAW_LINE_T(x - 10, dy - 15, x - 10, dy - 5, bowCol);
        DRAW_LINE_T(x - 10, dy - 15, x, dy - 10, bowCol);
        DRAW_LINE_T(x - 10, dy - 5, x, dy - 10, bowCol);
        FILL_T(x - 6, dy - 10, bowCol, bowCol);
        
        DRAW_LINE_T(x + 10, dy - 15, x + 10, dy - 5, bowCol);
        DRAW_LINE_T(x + 10, dy - 15, x, dy - 10, bowCol);
        DRAW_LINE_T(x + 10, dy - 5, x, dy - 10, bowCol);
        FILL_T(x + 6, dy - 10, bowCol, bowCol);
        
        int cx = x, cy = dy - 10; TRANSFORM_PT(cx, cy);
        veDuongTron(cx, cy, 3, bowCol);
        toMauDeQuy(cx, cy, bowCol, bowCol);
    }
    
    // 9. Ve Khiên Bảo Vệ
    if(coKhien) {
        int aura1 = COLOR(100, 255, 255);
        double sa = timeSec * 3.0; 
        for(int i = 0; i < 6; i++) {
            int px = x + (int)(32);
            int py = dy - (int)(25);
            PhepQuay2D(&px, &py, x, dy - 25, sa + i * 1.047);
            veDuongTron(px, py, 3, aura1);
            toMauDeQuy(px, py, aura1, aura1);
        }
        veHinhElip(x, dy - 25, 38, 30, aura1); // Vien mong
    }
}
