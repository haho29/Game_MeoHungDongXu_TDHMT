#ifndef GIAODIEN_H
#define GIAODIEN_H

#include <stdbool.h>

struct VatTheRoi {
    int x, y;
    int loai; // 0: Dong Xu, 1: Bom, 2: Xuong Ca
    bool active;
};

#define SO_VAT_THE 8

struct GiaoDien_State {
    int diem;
    int mang;
    int caoNhat;
    int meoX, meoY;
    struct VatTheRoi cacVatThe[SO_VAT_THE]; // Mang chua cac vat the roi
    bool gameOver;
};

void initGiaoDien(struct GiaoDien_State* state);
void playGiaoDien(struct GiaoDien_State* state);

#endif
