#include "VeNenKhung.h"
#include "VeHinh.h"
#include "VatThe.h"
#include "TraiTim.h"
#include <graphics.h>
#include <stdio.h>
#include <math.h>

void veNenKhung(struct GiaoDien_State* state) {
    int i;
    char scoreStr[20];
    char highScoreStr[30];

    // Colors matching the new design
    int woodLight = COLOR(248, 225, 185); // Header/Footer base wood
    int woodDark = COLOR(210, 160, 90);   // Wood borders
    int skyBg = COLOR(144, 213, 245);
    int grassBg = COLOR(122, 193, 67);
    int fenceWood = COLOR(215, 160, 95);
    int fenceLine = COLOR(165, 110, 50);
    int white = COLOR(255, 255, 255);
    int textBrown = COLOR(101, 56, 24);
    int pillBg = COLOR(255, 245, 230);
    int orangeCenter = COLOR(245, 150, 40); // cho CatCatch title block
    int textGold = COLOR(255, 215, 0);

    // ===== 1. HEADER (y = 0 to 80) =====
    my_bar(0, 0, 1150, 80, woodLight);
    veDuongThang(0, 80, 1150, 80, woodDark);
    veDuongThang(0, 81, 1150, 81, woodDark);
    
    // Diem (Left Pill) - Thiết kế 3D nổi bật
    my_bar(48, 18, 252, 62, COLOR(85, 45, 30)); // Đổ bóng gỗ tối 3D
    my_bar(50, 20, 250, 60, woodDark);          // Viền gỗ ấm
    my_bar(53, 23, 247, 57, pillBg);            // Mặt kén ngà
    setbkcolor(pillBg);
    sprintf(scoreStr, "DIEM: %d", state->diem);
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    setcolor(COLOR(200, 50, 10)); // Màu đỏ thẫm sang trọng
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    outtextxy(150, 42, scoreStr);
    
    // Cao nhat (Right Pill) - Thiết kế 3D nổi bật
    my_bar(898, 18, 1102, 62, COLOR(85, 45, 30)); // Đổ bóng gỗ tối 3D
    my_bar(900, 20, 1100, 60, woodDark);          // Viền gỗ ấm
    my_bar(903, 23, 1097, 57, pillBg);            // Mặt kén ngà
    setbkcolor(pillBg);
    sprintf(highScoreStr, "CAO NHAT: %d", state->caoNhat);
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    setcolor(COLOR(200, 50, 10)); // Màu đỏ thẫm sang trọng
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    outtextxy(1000, 42, highScoreStr);
    
    // Center Title Block - Căn giữa màn hình 1150 với kén gỗ 3D
    my_bar(453, 0, 697, 72, COLOR(85, 45, 30)); // Đổ bóng gỗ
    my_bar(455, 0, 695, 70, woodDark); 
    my_bar(459, 0, 691, 65, orangeCenter);
    setbkcolor(orangeCenter);
    setcolor(COLOR(85, 45, 30)); // Đổ bóng chữ tiêu đề
    settextstyle(BOLD_FONT, HORIZ_DIR, 4);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    outtextxy(577, 34, (char*)"CatCatch!");
    setcolor(textGold);
    outtextxy(575, 32, (char*)"CatCatch!");
    
    // Mang (Lives HUD inside custom cute pink pill) - Kén hồng xinh xắn căng nét
    my_bar(485, 42, 665, 60, COLOR(50, 20, 10)); // Bóng kén
    my_bar(487, 40, 663, 58, COLOR(255, 235, 235)); // Nền kén hồng pastel ngọt ngào
    setbkcolor(COLOR(255, 235, 235));
    setcolor(COLOR(243, 139, 168)); // Màu hồng cánh sen ngọt ngào
    settextstyle(BOLD_FONT, HORIZ_DIR, 1);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    outtextxy(520, 52, (char*)"MANG:");
    for(i = 0; i < state->mang; i++) {
        veTraiTim(560 + i * 20, 48); 
    }

    // ===== 2. MAIN PLAY AREA (y = 82 to 560) =====
    int px = 8; // Kich thuoc pixel de ve retro style
    int skyDark = COLOR(25, 15, 45); // Tim den dam
    int starColor1 = COLOR(255, 255, 220);
    int starColor2 = COLOR(200, 200, 255);
    int grassTop = COLOR(50, 220, 0);
    int grassDark = COLOR(0, 150, 0);
    int dirtBg = COLOR(116, 70, 49);
    int dirtLight = COLOR(135, 85, 60);
    int dirtDark = COLOR(85, 45, 30);
    int x, y;

    // 1. Sky Base (Tim den dam)
    my_bar(10, 82, 1140, 515, skyDark); 
    
    // 2. Stars (Ngôi sao đêm lấp lánh động nhịp nhàng)
    static int playStarFrame = 0;
    playStarFrame++;
    for(x = 25; x < 1140; x += px*3) {
        for(y = 100; y < 430; y += px*3) { // Giữ sao trên chân trời núi
            int h = (x*17 + y*31) % 100;
            if(h < 3) {
                // Hiệu ứng lấp nháy động dựa vào thời gian thực
                int phase = (x + y + playStarFrame) % 8;
                if(phase < 2) my_bar(x, y, x+3, y+3, starColor1);
                else if(phase < 5) my_bar(x+1, y+1, x+2, y+2, starColor2);
            }
        }
    }

    // Vẽ Mặt Trăng Khuyết Lượng Giác Vàng Hoàng Kim (Golden Crescent Moon)
    for(int dy = -25; dy <= 25; dy++) {
        for(int dx = -25; dx <= 25; dx++) {
            if(dx*dx + dy*dy <= 25*25) {
                int cdx = dx + 10;
                int cdy = dy - 3;
                if(cdx*cdx + cdy*cdy > 23*23) {
                    my_putpixel(1050 + dx, 150 + dy, COLOR(254, 215, 0)); // Màu vàng hoàng kim
                }
            }
        }
    }

    // 2.5 PROCEDURAL GEOMETRIC MOUNTAINS (Dãy núi trùng điệp chân trời lượng giác)
    // Tự động quét và vẽ các đồi núi nhấp nhô vô cùng mềm mại tự nhiên dựa trên tổng hợp 3 tần số sóng lượng giác.
    // Tông màu tím sẫm huyền ảo tạo hiệu ứng xa xăm kỳ bí.
    for(x = 10; x < 1140; x++) {
        double wave1 = 15.0 * sin(x * 0.01);
        double wave2 = 8.0 * cos(x * 0.03);
        double wave3 = 10.0 * sin(x * 0.005 + 1.0);
        int peakY = 515 - (int)(wave1 + wave2 + wave3);
        
        if(peakY < 450) peakY = 450;
        if(peakY > 515) peakY = 515;
        
        // Vẽ cột núi dọc bằng Bresenham
        veDuongThang(x, 515, x, peakY, COLOR(35, 25, 60));
    }

    // 3. Ground Dirt Layer (y = 530 to 560)
    my_bar(10, 530, 1140, 560, dirtBg);
    for(x = 10; x < 1140; x += px) {
        for(y = 530; y < 560; y += px) {
            int h = (x*17 + y*31) % 100;
            if(h < 15) my_bar(x, y, x+px, y+px, dirtLight);
            else if(h > 85) my_bar(x, y, x+px, y+px, dirtDark);
        }
    }
    
    // 4. Grass Layer (y = 515 to 530)
    my_bar(10, 515, 1140, 530, grassTop);
    for(x = 10; x < 1140; x += px) {
        int drop = ((x/px)%2 == 0) ? px : 0;
        my_bar(x, 530, x+px, 530+drop, grassTop); // jagged grass going down
        my_bar(x, 530+drop, x+px, 530+drop+px/2, grassDark); // dark shadow edge
    }
    
    // =========================================================================
    // 4.5 Fractal Grass (Bụi cây gai Fractal tự đồng dạng - Đường cong Koch)
    // Ứng dụng: Lồng ghép cấu trúc toán học Fractal của Koch ở độ sâu đệ quy bằng 3
    // để mô phỏng chân thực các bụi cây gai dại, nhấp nhô tự nhiên nhô lên từ nền cỏ.
    // Phối màu: Sử dụng gam màu xanh tươi sáng (Pastel Green) tạo hiệu ứng tương phản
    // hài hòa với màu nền cỏ đậm, làm nổi bật tính thẩm mỹ và chiều sâu của bối cảnh rừng.
    // =========================================================================
    int fractalGrass = COLOR(180, 240, 100);
    // Vẽ bụi gai Fractal bên trái màn hình (Gồm 2 phân đoạn từ x = 30 đến x = 310)
    veDuongKoch(30, 515, 170, 515, fractalGrass, 3);
    veDuongKoch(170, 515, 310, 515, fractalGrass, 3);
    
    // Vẽ bụi gai Fractal bên phải màn hình (Gồm 2 phân đoạn đối xứng dịch chuyển từ x = 840 đến x = 1120)
    veDuongKoch(840, 515, 980, 515, fractalGrass, 3);
    veDuongKoch(980, 515, 1120, 515, fractalGrass, 3);

    // =========================================================================
    // 4.6 Hieu ung Dom Dom (Fireflies) tren bai co
    // =========================================================================
    for(int f = 0; f < 15; f++) {
        double fTime = state->playTimeSec + f * 10.0;
        int fx = 50 + ((f * 137 + (int)(40 * sin(fTime * 0.5))) % 1050);
        int fy = 450 + (int)(30 * sin(fTime * 0.8 + f)) + (f*15 % 50);
        int fPhase = ((int)(fTime * 10) + f * 5) % 20;
        
        if (fPhase < 12) { // Nhap nhay
            int glow = 150 + fPhase * 8;
            if(glow > 255) glow = 255;
            my_bar(fx, fy, fx + 2, fy + 2, COLOR(glow, 255, 100)); // Màu xanh vàng của đom đóm
            my_bar(fx-1, fy+1, fx+3, fy+1, COLOR(100, 200, 50)); // Hào quang nhẹ
        }
    }

    // Side borders for play area
    my_bar(0, 82, 10, 560, woodDark);
    my_bar(1140, 82, 1150, 560, woodDark);

    // ===== 3. FOOTER (y = 560 to 750) =====
    my_bar(0, 560, 1150, 750, woodLight);
    veDuongThang(0, 560, 1150, 560, woodDark);
    veDuongThang(0, 561, 1150, 561, woodDark);
    
    // Instruction Panel inside footer
    my_bar(20, 575, 1130, 740, woodDark);
    my_bar(22, 577, 1128, 738, pillBg);
    
    // "LUAT CHOI:" badge
    my_bar(40, 565, 175, 593, woodDark);
    my_bar(42, 567, 173, 591, orangeCenter);
    setbkcolor(orangeCenter);
    setcolor(white);
    settextstyle(BOLD_FONT, HORIZ_DIR, 1);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    outtextxy(107, 580, (char*)"LUAT CHOI:");
    
    // Instructions Text (4 dong trai)
    setbkcolor(pillBg);
    setcolor(textBrown);
    settextjustify(LEFT_TEXT, CENTER_TEXT);
    settextstyle(BOLD_FONT, HORIZ_DIR, 1); 
    
    // Dong 1 (bat dau tu y=616 de co khoang trong duoi badge)
    int px_i = 45, py = 616;
    my_bar(px_i-3, py-1, px_i+3, py+3, textBrown); 
    my_bar(px_i-6, py-4, px_i-4, py-2, textBrown); 
    my_bar(px_i-1, py-5, px_i+1, py-3, textBrown); 
    my_bar(px_i+4, py-4, px_i+6, py-2, textBrown); 
    outtextxy(px_i + 15, py + 2, (char*)"Phim [<-] [->]: Di chuyen MEO.");
    
    // Dong 2
    py = 638;
    my_bar(px_i-3, py-1, px_i+3, py+3, textBrown); 
    my_bar(px_i-6, py-4, px_i-4, py-2, textBrown); 
    my_bar(px_i-1, py-5, px_i+1, py-3, textBrown); 
    my_bar(px_i+4, py-4, px_i+6, py-2, textBrown); 
    outtextxy(px_i + 15, py + 2, (char*)"[0] Dung/Tiep, [1] Cham, [2] Nhanh, [3] Nhanh hon.");
    
    // Dong 3
    py = 660;
    my_bar(px_i-3, py-1, px_i+3, py+3, textBrown); 
    my_bar(px_i-6, py-4, px_i-4, py-2, textBrown); 
    my_bar(px_i-1, py-5, px_i+1, py-3, textBrown); 
    my_bar(px_i+4, py-4, px_i+6, py-2, textBrown); 
    outtextxy(px_i + 15, py + 2, (char*)"3 mang la thua game! Thu thap tim de hoi sinh.");
    
    // Dong 4
    py = 682;
    my_bar(px_i-3, py-1, px_i+3, py+3, textBrown); 
    my_bar(px_i-6, py-4, px_i-4, py-2, textBrown); 
    my_bar(px_i-1, py-5, px_i+1, py-3, textBrown); 
    my_bar(px_i+4, py-4, px_i+6, py-2, textBrown); 
    outtextxy(px_i + 15, py + 2, (char*)"Toc do roi tang theo diem. ESC de thoat game.");
    
    // ===== CHU THICH VAT THE (ben phai, separator x=700) =====
    // Vertical separator dashed (dai xuong theo footer moi)
    veDuongThang(698, 582, 698, 732, woodDark);
    for(int y = 582; y < 732; y+=8) veDuongThang(698, y, 698, y+4, pillBg);

    // "CHU THICH:" mini badge
    my_bar(704, 565, 810, 591, woodDark);
    my_bar(706, 567, 808, 589, orangeCenter);
    setbkcolor(orangeCenter);
    setcolor(white);
    settextstyle(BOLD_FONT, HORIZ_DIR, 1);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    outtextxy(757, 579, (char*)"CHU THICH:");

    // Icons: 6 items xep 2 cot, bat dau tu y=620 (co khoang trong duoi badge)
    setbkcolor(pillBg);
    setcolor(textBrown);
    settextjustify(LEFT_TEXT, CENTER_TEXT);
    settextstyle(BOLD_FONT, HORIZ_DIR, 1);

    // --- COT TRAI (x=720) ---
    int icL = 726; // icon center x trai
    int txL = 743; // text x trai

    // Dong xu (+diem)
    veDongXu(icL, 622, 8, 0);
    setbkcolor(pillBg); setcolor(textBrown);
    outtextxy(txL, 622, (char*)": Cong diem");

    // Xuong ca (-diem)
    veXuongCa(icL, 652, 0.0);
    setbkcolor(pillBg); setcolor(textBrown);
    outtextxy(txL, 652, (char*)": Tru diem");

    // Bom (-mang)
    veBom(icL, 683, 0.65);
    setbkcolor(pillBg); setcolor(textBrown);
    outtextxy(txL, 683, (char*)": Mat 1 mang");

    // --- COT PHAI (x=900) ---
    int icR = 906; // icon center x phai
    int txR = 923; // text x phai

    // Nam cham (hut xu)
    veNamCham(icR, 622, 0.0);
    setbkcolor(pillBg); setcolor(textBrown);
    outtextxy(txR, 622, (char*)": Hut dong xu");

    // Khien bao ve
    double kAngle = 0.0, kScale = 1.0;
    veKhiNangLuong(icR, 652, kAngle, kScale);
    setbkcolor(pillBg); setcolor(textBrown);
    outtextxy(txR, 652, (char*)": Khien bao ve");

    // Dong ho (lam cham)
    veDongHo(icR, 683, 0.0);
    setbkcolor(pillBg); setcolor(textBrown);
    outtextxy(txR, 683, (char*)": Lam cham roi");
}
