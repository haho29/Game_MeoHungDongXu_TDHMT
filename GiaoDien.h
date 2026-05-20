#ifndef GIAODIEN_H
#define GIAODIEN_H

#include <stdbool.h>

struct VatTheRoi {
    int x, y;
    int loai; // 0: Dong Xu, 1: Bom, 2: Xuong Ca, 3: Xu20, 4: Xu30, 5: Tim, 6: Khien, 7: NamCham
    bool active;
};

struct HatParticle {
    int x, y;
    double vx, vy;
    int color;
    int life; // Thoi gian song
    bool active;
};

struct ChuNoi {
    int x, y;
    char text[15];
    int color;
    int life;
    bool active;
};

#define SO_VAT_THE 8
#define SO_HAT 60
#define SO_CHU_NOI 10

struct GiaoDien_State {
    int diem;
    int mang;
    int caoNhat;
    
    // Vat ly meo
    double meoX_d;
    int meoX, meoY;
    double meoVx; // Van toc
    bool meoQuayTrai;
    
    // Trang thai
    int dangSkin; // 0: Mac dinh, 1: Vang, 2: Den
    int dangPhuKien; // 0: Khong, 1: Vuong mien, 2: Kinh ram
    int tongXuTichLuy;
    int khienBaoVe; // So luong khien dang co (max 1)
    int thoiGianNamCham; // So khung hinh con lai cua nam cham
    double playTimeSec; // Thoi gian choi de tinh toan hoat anh
    
    struct VatTheRoi cacVatThe[SO_VAT_THE]; 
    struct HatParticle cacHat[SO_HAT];
    struct ChuNoi cacChuNoi[SO_CHU_NOI];
    
    bool gameOver;
};

void initGiaoDien(struct GiaoDien_State* state, int skin, int phuKien, int xu);
void playGiaoDien(struct GiaoDien_State* state);

#endif
