#include "ManHinhKetThuc.h"
#include "VeNenKhung.h"
#include "VeHinh.h"
#include <graphics.h>
#include <stdio.h>
#include <conio.h>

void hienThiManHinhKetThuc(struct GiaoDien_State* state, int trang, bool isNewHigh) {
    // Hien thi Game Over (Modal ket thuc)
    setactivepage(trang);
    veNenKhung(state);
    
    int white = COLOR(255, 255, 255);
    int panelBg = COLOR(248, 238, 204);
    int textBrown = COLOR(101, 56, 24);
    int redRibbon = COLOR(210, 40, 40);
    int redRibbonDark = COLOR(150, 20, 20);
    int gold = COLOR(255, 204, 0);
    int scoreBlue = COLOR(20, 80, 180);
    int scoreRed = COLOR(200, 50, 30);
    int boxBg = COLOR(255, 248, 220); // light cream cho box diem
    char scoreStr[20];
    char highScoreStr[20];
    int i;
    
    // 1. CONFETTI (Phao giay) - Phủ rộng 1000x700
    int colors[] = {COLOR(255, 50, 50), COLOR(50, 255, 50), COLOR(50, 150, 255), COLOR(255, 255, 50), COLOR(255, 150, 50)};
    for(i=0; i<50; i++) {
        int cx = (i * 83) % 1000;
        int cy = (i * 101) % 700;
        int col = colors[i % 5];
        my_bar(cx, cy, cx+8, cy+8, col);
    }
    
    // 2. MAIN PANEL - Căn giữa 1000
    my_bar(250, 245, 750, 535, textBrown); // Vien
    my_bar(255, 250, 745, 530, panelBg);   // Nen
    
    // 3. CROWN (Vuong mien tren panel) - Căn giữa 1000
    my_bar(450, 230, 550, 245, gold); // De vuong mien
    my_bar(450, 200, 465, 230, gold); // Gai trai
    my_bar(490, 190, 510, 230, gold); // Gai giua
    my_bar(535, 200, 550, 230, gold); // Gai phai
    // Ngoc tren vuong mien
    my_bar(453, 195, 462, 205, redRibbon);
    my_bar(495, 185, 505, 195, scoreBlue);
    my_bar(538, 195, 547, 205, redRibbon);
    
    // 4. RED RIBBON - Căn giữa 1000
    // Duoi ruy bang
    my_bar(290, 160, 400, 210, redRibbonDark); 
    my_bar(600, 160, 710, 210, redRibbonDark);
    // Than ruy bang
    my_bar(320, 140, 680, 200, redRibbon);
    
    // Text "KET THUC"
    setbkcolor(redRibbon);
    setcolor(gold);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 6);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    outtextxy(502, 177, (char*)"KET THUC");
    setcolor(COLOR(255, 255, 150)); // Sang bong
    outtextxy(500, 175, (char*)"KET THUC");
    
    // 5. SCORE BOXES (Ben trai)
    // Box 1: Diem vua choi
    my_bar(280, 290, 480, 370, textBrown); // Shadow/Border
    my_bar(282, 292, 478, 368, boxBg);
    setbkcolor(boxBg);
    setcolor(textBrown);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    outtextxy(380, 310, (char*)"DIEM VUA CHOI");
    setcolor(scoreBlue);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 4);
    sprintf(scoreStr, "%d", state->diem);
    outtextxy(380, 340, scoreStr);
    
    // Box 2: Ky luc
    my_bar(280, 400, 480, 480, textBrown); // Shadow/Border
    my_bar(282, 402, 478, 478, boxBg);
    setbkcolor(boxBg);
    setcolor(textBrown);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    outtextxy(380, 420, (char*)"KY LUC");
    setcolor(scoreRed);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 4);
    sprintf(highScoreStr, "%d", state->caoNhat);
    outtextxy(380, 450, highScoreStr);
    
    // Tem "MOI!" neu pha ky luc
    if(isNewHigh) {
        my_bar(450, 430, 510, 460, redRibbon);
        setbkcolor(redRibbon);
        setcolor(white);
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
        outtextxy(480, 445, (char*)"MOI!");
    }
    
    // 6. CUTE CAT WINKING (Ben phai) - Căn giữa 1000
    int catPink = COLOR(245, 194, 231);
    int catDarkPink = COLOR(243, 139, 168); // Nose and inner ear
    int black = COLOR(17, 17, 27);
    int cx = 610, cy = 400;
    
    // Tai (Ears)
    for(i=0; i<40; i++) {
        veDuongThang(cx-50+i/2, cy-50-i, cx-10+i, cy-50, catPink); 
        veDuongThang(cx+50-i/2, cy-50-i, cx+10-i, cy-50, catPink); 
    }
    // Tai trong (Inner ears)
    for(i=0; i<20; i++) {
        veDuongThang(cx-40+i/2, cy-50-i, cx-20+i, cy-50, catDarkPink);
        veDuongThang(cx+40-i/2, cy-50-i, cx+20-i, cy-50, catDarkPink);
    }
    
    // Mat cat (Face)
    my_bar(cx-60, cy-40, cx+60, cy+40, catPink);
    my_bar(cx-70, cy-20, cx+70, cy+20, catPink);
    my_bar(cx-40, cy-60, cx+40, cy+60, catPink);
    
    // Phan trang tren mieng
    my_bar(cx-45, cy, cx+45, cy+50, white);
    my_bar(cx-55, cy+10, cx+55, cy+40, white);
    
    // Mat trai (mo)
    my_bar(cx-35, cy-20, cx-15, cy+5, black);
    my_bar(cx-30, cy-15, cx-20, cy-5, white); // diem sang
    
    // Mat phai (nhay mat nheo lai - dau >)
    veDuongThang(cx+15, cy-5, cx+35, cy-5, black);
    veDuongThang(cx+15, cy-6, cx+35, cy-6, black); 
    veDuongThang(cx+15, cy-4, cx+35, cy-4, black); 
    
    // Mui
    my_bar(cx-10, cy+5, cx+10, cy+15, catDarkPink);
    
    // Mieng cuoi (chu V rong)
    my_bar(cx-20, cy+25, cx+20, cy+45, black);
    my_bar(cx-15, cy+35, cx+15, cy+45, catDarkPink); // luoi
    
    // Ria mep
    veDuongThang(cx-80, cy+10, cx-50, cy+5, black);
    veDuongThang(cx-80, cy+25, cx-50, cy+20, black);
    veDuongThang(cx+50, cy+5, cx+80, cy+10, black);
    veDuongThang(cx+50, cy+20, cx+80, cy+25, black);
    
    // 7. Thoat
    int bgPlay = COLOR(15, 20, 40);
    setbkcolor(bgPlay); // Dung mau nen the hien o duoi
    setcolor(white);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    outtextxy(500, 580, (char*)"[ Nhan Phim / Chuot de tiep tuc ]");

    setvisualpage(trang);
    
    // Don dep bo dem phim va chuot roi moi doi nguoi choi nhan phim
    while(kbhit()) getch();
    clearmouseclick(WM_LBUTTONDOWN);
    
    while(!kbhit() && !ismouseclick(WM_LBUTTONDOWN)) {
        delay(100);
    }
    if(ismouseclick(WM_LBUTTONDOWN)) clearmouseclick(WM_LBUTTONDOWN);
    else getch();
}
