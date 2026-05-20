#include "ManHinhBatDau.h"
#include "VeHinh.h"
#include "VatThe.h"
#include <graphics.h>
#include <conio.h>

// Ve dau meo don gian
void veDauMeoChibi(int x, int y) {
    int catPink = COLOR(245, 194, 231);
    int catDarkPink = COLOR(243, 139, 168); // Nose and inner ear
    int white = COLOR(255, 255, 255);
    int black = COLOR(17, 17, 27);
    int i;

    // Tai meo (Ears)
    for(i=0; i<30; i++) {
        veDuongThang(x-40+i/2, y-30-i, x-20+i, y-30, catPink); // Tai trai
        veDuongThang(x+40-i/2, y-30-i, x+20-i, y-30, catPink); // Tai phai
    }
    // Tai trong (Inner ears)
    for(i=0; i<15; i++) {
        veDuongThang(x-30+i/2, y-30-i, x-20+i, y-30, catDarkPink);
        veDuongThang(x+30-i/2, y-30-i, x+20-i, y-30, catDarkPink);
    }
    
    // Mat cat (Face)
    my_bar(x-40, y-30, x+40, y+30, catPink);
    my_bar(x-50, y-20, x+50, y+20, catPink);
    my_bar(x-30, y-40, x+30, y+40, catPink);
    
    // Phan trang tren mieng
    my_bar(x-20, y, x+20, y+20, white);
    my_bar(x-30, y+5, x+30, y+15, white);
    
    // Mat (Eyes)
    my_bar(x-25, y-10, x-15, y+5, black);
    my_bar(x+15, y-10, x+25, y+5, black);
    // Diem sang trong mat (Highlights)
    my_bar(x-20, y-8, x-16, y-3, white);
    my_bar(x+20, y-8, x+24, y-3, white);
    
    // Mui (Nose)
    my_bar(x-5, y+2, x+5, y+7, catDarkPink);
    
    // Ria mep (Whiskers)
    veDuongThang(x-45, y+10, x-25, y+5, black);
    veDuongThang(x-45, y+20, x-25, y+15, black);
    veDuongThang(x+25, y+5, x+45, y+10, black);
    veDuongThang(x+25, y+15, x+45, y+20, black);
}

int hienThiManHinhBatDau() {
    int bgSky = COLOR(25, 15, 45); // Gameplay Sky Dark
    int bgGrassTop = COLOR(50, 220, 0); // Gameplay Grass Top
    int bgGrassDark = COLOR(0, 150, 0); // Gameplay Grass Dark
    int fenceWood = COLOR(116, 70, 49); // Dirt color
    int fenceLine = COLOR(85, 45, 30);  // Dirt dark color
    
    int titleWood = COLOR(137, 180, 250); // Catppuccin Sapphire / Blueish pastel
    int titleShadow = COLOR(100, 130, 200);
    
    int btnYellow = COLOR(249, 226, 175); // Pastel Yellow
    int btnYellowShadow = COLOR(200, 180, 140);
    int btnGreen = COLOR(166, 227, 161); // Pastel Green
    int btnGreenShadow = COLOR(130, 180, 120);
    
    int panelBg = COLOR(30, 30, 46); // Crust
    int textBrown = COLOR(205, 214, 244); // Text white/blueish
    int titleBlue = COLOR(245, 194, 231); // Pink text
    int white = COLOR(255, 255, 255);
    
    int selected = 0; // 0: Bat Dau, 2: Thoat
    int trang = 0;
    int i, px, py, x, y;
    
    // Biến lưu trạng thái thời gian thực cho sao lấp lánh
    static int starFrame = 0;
    
    while (1) {
        setactivepage(trang);
        
        // 1. SKY (Night sky with stars) - Phủ rộng 1000
        my_bar(0, 0, 1000, 350, bgSky);
        
        // Sao nhấp nháy tuần hoàn theo thời gian thực (Twinkling stars)
        starFrame++;
        for(x = 25; x < 980; x += 45) {
            for(y = 20; y < 270; y += 35) {
                int phase = (x * 17 + y * 23 + starFrame) % 15;
                if(phase < 2) {
                    my_bar(x, y, x+3, y+3, white); // Sao sáng rực
                } else if(phase < 5) {
                    my_bar(x+1, y+1, x+2, y+2, COLOR(200, 200, 240)); // Sao mờ dịu
                }
            }
        }
        
        // Vẽ Mặt Trăng Khuyết Lượng Giác Vàng Hoàng Kim (Golden Crescent Moon)
        // Áp dụng giải thuật quét pixel đường tròn lồng nhau: dx^2 + dy^2 <= 40^2 cắt cdx^2 + cdy^2 > 38^2
        for(int dy = -40; dy <= 40; dy++) {
            for(int dx = -40; dx <= 40; dx++) {
                if(dx*dx + dy*dy <= 40*40) {
                    int cdx = dx + 15;
                    int cdy = dy - 5;
                    if(cdx*cdx + cdy*cdy > 38*38) {
                        my_putpixel(850 + dx, 80 + dy, COLOR(254, 215, 0)); // Vàng hoàng kim
                    }
                }
            }
        }
        
        // 2. FENCE (Dat mau go/dat) - Dịch xuống và phủ rộng 1000
        for(i = -10; i < 1000; i += 40) {
            my_bar(i, 280, i+30, 400, fenceWood);
            my_bar(i+5, 270, i+25, 280, fenceWood); // bo tron tren
            veDuongThang(i+30, 280, i+30, 400, fenceLine);
        }
        
        // 3. GRASS - Phủ rộng 1000
        my_bar(0, 370, 1000, 700, bgGrassTop);
        for(px=20; px<1000; px+=40) {
            for(py=390; py<700; py+=30) {
                if((px+py)%70 == 0) {
                    my_bar(px, py, px+4, py+4, bgGrassDark);
                }
            }
        }
        
        // 4. BIG CAT FACE - Căn giữa 1000
        veDauMeoChibi(500, 270);
        
        // 5. TITLE BOARD - Bảng gỗ tiêu đề đa tầng sang trọng
        my_bar(246, 24, 754, 134, COLOR(50, 30, 10)); // Đổ bóng gỗ tối bên dưới 3D
        my_bar(250, 20, 750, 130, titleShadow);
        my_bar(250, 15, 750, 120, titleWood);
        // Đinh tán kim loại sang trọng
        my_bar(260, 25, 270, 35, COLOR(50, 50, 70));
        my_bar(730, 25, 740, 35, COLOR(50, 50, 70));
        my_bar(260, 100, 270, 110, COLOR(50, 50, 70));
        my_bar(730, 100, 740, 110, COLOR(50, 50, 70));
        
        setbkcolor(titleWood);
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 6);
        settextjustify(CENTER_TEXT, CENTER_TEXT);
        // Chữ MEO đổ bóng sang trọng
        setcolor(COLOR(50, 40, 20)); outtextxy(503, 53, (char*)"MEO");
        setcolor(COLOR(255, 220, 50)); outtextxy(500, 50, (char*)"MEO");
        
        // Chữ HUNG DONG XU
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 4);
        setcolor(COLOR(50, 40, 20)); outtextxy(503, 103, (char*)"HUNG DONG XU");
        setcolor(titleBlue); outtextxy(500, 100, (char*)"HUNG DONG XU");
        
        // 6. BUTTONS - Căn giữa 1000 với hiệu ứng Hover chuột động tương tác
        int btnYellowHover = COLOR(254, 240, 200); // Vàng sáng khi hover
        int btnGreenHover = COLOR(190, 245, 185); // Xanh sáng khi hover
        int goldGlow = COLOR(255, 215, 0); // Viền vàng hoàng kim phát sáng
        
        // Kiểm tra tương tác chuột
        px = mousex();
        py = mousey();
        int hoverStart = (px >= 350 && px <= 650 && py >= 340 && py <= 400);
        int hoverThoat = (px >= 400 && px <= 600 && py >= 420 && py <= 470);
        
        if (hoverStart) {
            selected = 0; // Đồng bộ chuột sang phím bấm
        } else if (hoverThoat) {
            selected = 2; // Đồng bộ chuột sang phím bấm
        }
        
        // NÚT BẮT ĐẦU (START BUTTON)
        if (selected == 0) {
            // Trạng thái hover/selected: Scale-up to hơn một chút và phát sáng viền vàng
            my_bar(343, 333, 657, 407, goldGlow);
            my_bar(345, 335, 655, 405, white);
            my_bar(347, 337, 653, 403, hoverStart ? btnYellowHover : btnYellow);
            setbkcolor(hoverStart ? btnYellowHover : btnYellow);
        } else {
            // Trạng thái bình thường có đổ bóng
            my_bar(350, 345, 650, 405, btnYellowShadow);
            my_bar(350, 340, 650, 400, btnYellow);
            setbkcolor(btnYellow);
        }
        setcolor(textBrown);
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
        settextjustify(CENTER_TEXT, CENTER_TEXT);
        outtextxy(500, 370, (char*)"BAT DAU");
        
        // NÚT THOÁT (EXIT BUTTON)
        if (selected == 2) {
            // Trạng thái hover/selected: Scale-up to hơn một chút và phát sáng viền
            my_bar(393, 413, 607, 477, goldGlow);
            my_bar(395, 415, 605, 475, white);
            my_bar(397, 417, 603, 473, hoverThoat ? btnGreenHover : btnGreen);
            setbkcolor(hoverThoat ? btnGreenHover : btnGreen);
        } else {
            // Trạng thái bình thường có đổ bóng
            my_bar(400, 425, 600, 475, btnGreenShadow);
            my_bar(400, 420, 600, 470, btnGreen);
            setbkcolor(btnGreen);
        }
        setcolor(white);
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
        settextjustify(CENTER_TEXT, CENTER_TEXT);
        outtextxy(500, 445, (char*)"THOAT");
        
        // 7. INSTRUCTION PANEL - Căn giữa 1000
        my_bar(250, 520, 750, 660, COLOR(210, 190, 160)); // Vien
        my_bar(250, 515, 750, 655, panelBg); // Nen
        
        setbkcolor(panelBg);
        setcolor(textBrown);
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
        settextjustify(CENTER_TEXT, CENTER_TEXT);
        outtextxy(500, 535, (char*)"* HUONG DAN *");
        
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
        outtextxy(500, 565, (char*)"Phim [TRAI] [PHAI] hoac di chuot de dieu khien");
        outtextxy(500, 585, (char*)"meo hung cac vat pham roi tu tren cao xuong.");
        
        // Icons
        settextjustify(LEFT_TEXT, CENTER_TEXT);
        veDongXu(330, 625, 12, 0);
        setbkcolor(panelBg); setcolor(textBrown);
        outtextxy(350, 625, (char*)": +10 Diem");
        
        veXuongCa(470, 625, 0.0);
        setbkcolor(panelBg); setcolor(textBrown);
        outtextxy(490, 625, (char*)": -5 Diem");
        
        veBom(600, 625, 1.0);
        setbkcolor(panelBg); setcolor(textBrown);
        outtextxy(625, 625, (char*)": -1 Mang");
        
        setvisualpage(trang);
        trang = 1 - trang;
        
        if (kbhit()) {
            int key = getch();
            if (key == 224) {
                key = getch();
                if (key == 72 || key == 80 || key == 75 || key == 77) {
                    selected = (selected == 0) ? 2 : 0;
                }
            } else if (key == 13) { // Enter
                if (selected == 0) return 1; // Bat dau
                if (selected == 2) return 0; // Thoat
            } else if (key == 27) { // ESC
                return 0;
            }
        }
        
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int mx, my;
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            clearmouseclick(WM_LBUTTONDOWN);
            if (mx >= 350 && mx <= 650 && my >= 340 && my <= 400) return 1; // BAT DAU
            if (mx >= 400 && mx <= 600 && my >= 420 && my <= 470) return 0; // THOAT
        }
        
        delay(50);
    }
}
