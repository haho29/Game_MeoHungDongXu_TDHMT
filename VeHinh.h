#ifndef VEHINH_H
#define VEHINH_H

#include <stdbool.h>

// Ham ho tro to mau (thay the bar de dong bo vram)
void my_putpixel(int x, int y, int color);
void my_bar(int left, int top, int right, int bottom, int color);

// Bresenham algorithm for lines
void veDuongThang(int x1, int y1, int x2, int y2, int color);

// Midpoint algorithm for circles
void veDuongTron(int xc, int yc, int r, int color);

// Midpoint algorithm for ellipses
void veHinhElip(int xc, int yc, int rx, int ry, int color);

// Recursive Boundary Fill algorithm
void toMauDeQuy(int x, int y, int fill_color, int boundary_color);

// Fractal Koch curve
void veDuongKoch(int x1, int y1, int x2, int y2, int color, int depth);

// 2D Rotation Transformation
void PhepQuay2D(int *px, int *py, int cx, int cy, double angle);

// 2D Scaling Transformation
void PhepCoGian2D(int *px, int *py, int cx, int cy, double sx, double sy);

#endif
