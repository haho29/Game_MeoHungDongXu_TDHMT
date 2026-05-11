#include "VeHinh.h"
#include <graphics.h>
#include <math.h>
#include <stdlib.h>

// VRAM ao de giai quyet loi getpixel khong hoat dong tren hidden buffer cua WinBGIm
int vram[800][600] = {0};

void my_putpixel(int x, int y, int color) {
    if (x >= 0 && x < 800 && y >= 0 && y < 600) {
        vram[x][y] = color;
        putpixel(x, y, color);
    }
}

int my_getpixel(int x, int y) {
    if (x >= 0 && x < 800 && y >= 0 && y < 600) {
        return vram[x][y];
    }
    return 0; // BLACK
}

void my_bar(int left, int top, int right, int bottom, int color) {
    setfillstyle(SOLID_FILL, color);
    bar(left, top, right, bottom);
    for (int x = left; x <= right; x++) {
        if (x < 0 || x >= 800) continue;
        for (int y = top; y <= bottom; y++) {
            if (y < 0 || y >= 600) continue;
            vram[x][y] = color;
        }
    }
}

// Trien khai ham COLOR bi thieu trong thu vien winbgim cua Dev-C++
int COLOR(int r, int g, int b) {
    // WinBGIm su dung bit 0x04000000 de phan biet mau RGB va mau mac dinh cua BGI (0-15)
    return 0x04000000 | r | (g << 8) | (b << 16);
}

// Thuat toan Bresenham ve duong thang
void veDuongThang(int x1, int y1, int x2, int y2, int color) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int p;
    int x = x1;
    int y = y1;
    
    // Xac dinh huong ve de ho tro du 8 octant
    int stepX = (x2 > x1) ? 1 : -1;
    int stepY = (y2 > y1) ? 1 : -1;

    my_putpixel(x, y, color);

    if (dx > dy) { 
        // Truong hop |m| < 1 (Goc nghieng nho hon 45 do)
        p = 2 * dy - dx;
        for (int i = 0; i < dx; i++) {
            if (p < 0) {
                p += 2 * dy; // Diem tiep theo cung y
            } else {
                // Bit kin duong cheo de chong tran mau (4-connected)
                my_putpixel(x + stepX, y, color);
                
                p += 2 * (dy - dx);
                y += stepY; // y thay doi theo huong
            }
            x += stepX; // x luon thay doi
            my_putpixel(x, y, color);
        }
    } else { 
        // Truong hop |m| >= 1 (Goc nghieng lon hon hoac bang 45 do)
        p = 2 * dx - dy;
        for (int i = 0; i < dy; i++) {
            if (p < 0) {
                p += 2 * dx; // Diem tiep theo cung x
            } else {
                // Bit kin duong cheo
                my_putpixel(x, y + stepY, color);
                
                p += 2 * (dx - dy);
                x += stepX; // x thay doi theo huong
            }
            y += stepY; // y luon thay doi
            my_putpixel(x, y, color);
        }
    }
}

// Thuat toan Midpoint ve duong tron
void veDuongTron(int xc, int yc, int r, int color) {
    int x = 0;
    int y = r;
    int p = 1 - r; 

    while (x < y) {
        my_putpixel(xc + x, yc + y, color);
        my_putpixel(xc - x, yc + y, color);
        my_putpixel(xc + x, yc - y, color);
        my_putpixel(xc - x, yc - y, color);
        my_putpixel(xc + y, yc + x, color);
        my_putpixel(xc - y, yc + x, color);
        my_putpixel(xc + y, yc - x, color);
        my_putpixel(xc - y, yc - x, color);
        
        x++;
        if (p < 0) {
            p += 2 * x + 1; 
        } else {
            // Bit kin goc cheo
            my_putpixel(xc + x, yc + y, color);
            my_putpixel(xc - x, yc + y, color);
            my_putpixel(xc + x, yc - y, color);
            my_putpixel(xc - x, yc - y, color);
            my_putpixel(xc + y, yc + x, color);
            my_putpixel(xc - y, yc + x, color);
            my_putpixel(xc + y, yc - x, color);
            my_putpixel(xc - y, yc - x, color);
            
            y--;
            p += 2 * (x - y) + 1; 
        }
    }
    
    if (x == y) {
        my_putpixel(xc + x, yc + y, color);
        my_putpixel(xc - x, yc + y, color);
        my_putpixel(xc + x, yc - y, color);
        my_putpixel(xc - x, yc - y, color);
    }
}

// Thuat toan Midpoint ve hinh Elip
void veHinhElip(int xc, int yc, int rx, int ry, int color) {
    int x = 0, y = ry;
    long rx2 = rx * rx;
    long ry2 = ry * ry;
    long tworx2 = 2 * rx2;
    long twory2 = 2 * ry2;
    long px = 0;
    long py = tworx2 * y;
    
    // Phan 1: Vung co do doc tiep tuyen > -1
    double p1 = ry2 - (rx2 * ry) + (0.25 * rx2);
    while (px < py) {
        my_putpixel(xc + x, yc + y, color);
        my_putpixel(xc - x, yc + y, color);
        my_putpixel(xc + x, yc - y, color);
        my_putpixel(xc - x, yc - y, color);
        x++;
        px += twory2;
        if (p1 < 0) {
            p1 += ry2 + px;
        } else {
            // Bit kin goc cheo
            my_putpixel(xc + x, yc + y, color);
            my_putpixel(xc - x, yc + y, color);
            my_putpixel(xc + x, yc - y, color);
            my_putpixel(xc - x, yc - y, color);
            y--;
            py -= tworx2;
            p1 += ry2 + px - py;
        }
    }
    
    // Phan 2: Vung co do doc tiep tuyen <= -1
    double p2 = ry2 * (x + 0.5) * (x + 0.5) + rx2 * (y - 1) * (y - 1) - rx2 * ry2;
    while (y >= 0) {
        my_putpixel(xc + x, yc + y, color);
        my_putpixel(xc - x, yc + y, color);
        my_putpixel(xc + x, yc - y, color);
        my_putpixel(xc - x, yc - y, color);
        y--;
        py -= tworx2;
        if (p2 > 0) {
            p2 += rx2 - py;
        } else {
            // Bit kin goc cheo
            my_putpixel(xc + x, yc + y, color);
            my_putpixel(xc - x, yc + y, color);
            my_putpixel(xc + x, yc - y, color);
            my_putpixel(xc - x, yc - y, color);
            x++;
            px += twory2;
            p2 += rx2 - py + px;
        }
    }
}

// Ham ho tro chong Stack Overflow
void toMauDeQuy_Safe(int x, int y, int fill_color, int boundary_color, int depth) {
    if(x < 0 || y < 0 || x >= 800 || y >= 600) return;
    if(depth > 15000) return; // Tang gioi han vi dung VRAM rat an toan va nhanh

    int current_color = my_getpixel(x, y); // Su dung VRAM thay vi getpixel
    
    // Kiem tra mau truc tiep vi VRAM luu chinh xac 100% ma mau
    if (current_color != boundary_color && current_color != fill_color) {
        my_putpixel(x, y, fill_color);
        toMauDeQuy_Safe(x + 1, y, fill_color, boundary_color, depth + 1);
        toMauDeQuy_Safe(x - 1, y, fill_color, boundary_color, depth + 1);
        toMauDeQuy_Safe(x, y + 1, fill_color, boundary_color, depth + 1);
        toMauDeQuy_Safe(x, y - 1, fill_color, boundary_color, depth + 1);
    }
}

// Thuat toan to mau de quy (Boundary Fill) 4 huong
void toMauDeQuy(int x, int y, int fill_color, int boundary_color) {
    toMauDeQuy_Safe(x, y, fill_color, boundary_color, 0);
}
