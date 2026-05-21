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
    my_bar(0, 0, 1000, 80, woodLight);
    veDuongThang(0, 80, 1000, 80, woodDark);
    veDuongThang(0, 81, 1000, 81, woodDark);
    
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
    my_bar(748, 18, 952, 62, COLOR(85, 45, 30)); // Đổ bóng gỗ tối 3D
    my_bar(750, 20, 950, 60, woodDark);          // Viền gỗ ấm
    my_bar(753, 23, 947, 57, pillBg);            // Mặt kén ngà
    setbkcolor(pillBg);
    sprintf(highScoreStr, "CAO NHAT: %d", state->caoNhat);
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    setcolor(COLOR(200, 50, 10)); // Màu đỏ thẫm sang trọng
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    outtextxy(850, 42, highScoreStr);
    
    // Center Title Block - Căn giữa màn hình 1000 với kén gỗ 3D
    my_bar(378, 0, 622, 72, COLOR(85, 45, 30)); // Đổ bóng gỗ
    my_bar(380, 0, 620, 70, woodDark); 
    my_bar(384, 0, 616, 65, orangeCenter);
    setbkcolor(orangeCenter);
    setcolor(COLOR(85, 45, 30)); // Đổ bóng chữ tiêu đề
    settextstyle(BOLD_FONT, HORIZ_DIR, 4);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    outtextxy(502, 34, (char*)"CatCatch!");
    setcolor(textGold);
    outtextxy(500, 32, (char*)"CatCatch!");
    
    // Mang (Lives HUD inside custom cute pink pill) - Kén hồng xinh xắn căng nét
    my_bar(410, 42, 590, 60, COLOR(50, 20, 10)); // Bóng kén
    my_bar(412, 40, 588, 58, COLOR(255, 235, 235)); // Nền kén hồng pastel ngọt ngào
    setbkcolor(COLOR(255, 235, 235));
    setcolor(COLOR(243, 139, 168)); // Màu hồng cánh sen ngọt ngào
    settextstyle(BOLD_FONT, HORIZ_DIR, 1);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    outtextxy(445, 52, (char*)"MANG:");
    for(i = 0; i < state->mang; i++) {
        veTraiTim(485 + i * 20, 48); 
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
    my_bar(10, 82, 990, 515, skyDark); 
    
    // 2. Stars (Ngôi sao đêm lấp lánh động nhịp nhàng)
    static int playStarFrame = 0;
    playStarFrame++;
    for(x = 25; x < 990; x += px*3) {
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
                    my_putpixel(900 + dx, 150 + dy, COLOR(254, 215, 0)); // Màu vàng hoàng kim
                }
            }
        }
    }

    // 2.5 PROCEDURAL GEOMETRIC MOUNTAINS (Dãy núi trùng điệp chân trời lượng giác)
    // Tự động quét và vẽ các đồi núi nhấp nhô vô cùng mềm mại tự nhiên dựa trên tổng hợp 3 tần số sóng lượng giác.
    // Tông màu tím sẫm huyền ảo tạo hiệu ứng xa xăm kỳ bí.
    for(x = 10; x < 990; x++) {
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
    my_bar(10, 530, 990, 560, dirtBg);
    for(x = 10; x < 990; x += px) {
        for(y = 530; y < 560; y += px) {
            int h = (x*17 + y*31) % 100;
            if(h < 15) my_bar(x, y, x+px, y+px, dirtLight);
            else if(h > 85) my_bar(x, y, x+px, y+px, dirtDark);
        }
    }
    
    // 4. Grass Layer (y = 515 to 530)
    my_bar(10, 515, 990, 530, grassTop);
    for(x = 10; x < 990; x += px) {
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
    
    // Vẽ bụi gai Fractal bên phải màn hình (Gồm 2 phân đoạn đối xứng từ x = 690 đến x = 970)
    veDuongKoch(690, 515, 830, 515, fractalGrass, 3);
    veDuongKoch(830, 515, 970, 515, fractalGrass, 3);

    // Side borders for play area
    my_bar(0, 82, 10, 560, woodDark);
    my_bar(990, 82, 1000, 560, woodDark);

    // ===== 3. FOOTER (y = 560 to 700) =====
    my_bar(0, 560, 1000, 700, woodLight);
    veDuongThang(0, 560, 1000, 560, woodDark);
    veDuongThang(0, 561, 1000, 561, woodDark);
    
    // Instruction Panel inside footer
    my_bar(20, 575, 980, 685, woodDark);
    my_bar(22, 577, 978, 683, pillBg);
    
    // "LUAT CHOI:" badge
    my_bar(40, 565, 175, 595, woodDark);
    my_bar(42, 567, 173, 593, orangeCenter);
    setbkcolor(orangeCenter);
    setcolor(white);
    settextstyle(BOLD_FONT, HORIZ_DIR, 1);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    outtextxy(107, 582, (char*)"LUAT CHOI:");
    
    // Instructions Text
    setbkcolor(pillBg);
    setcolor(textBrown);
    settextjustify(LEFT_TEXT, CENTER_TEXT);
    settextstyle(BOLD_FONT, HORIZ_DIR, 1); 
    
    // Dong 1
    int px_i = 50, py = 615;
    my_bar(px_i-3, py-1, px_i+3, py+3, textBrown); 
    my_bar(px_i-6, py-4, px_i-4, py-2, textBrown); 
    my_bar(px_i-1, py-5, px_i+1, py-3, textBrown); 
    my_bar(px_i+4, py-4, px_i+6, py-2, textBrown); 
    outtextxy(px_i + 15, py + 2, (char*)"Phim [<-] [->]: Di chuyen MEO sang trai, phai.");
    
    // Dong 2
    py = 645;
    my_bar(px_i-3, py-1, px_i+3, py+3, textBrown); 
    my_bar(px_i-6, py-4, px_i-4, py-2, textBrown); 
    my_bar(px_i-1, py-5, px_i+1, py-3, textBrown); 
    my_bar(px_i+4, py-4, px_i+6, py-2, textBrown); 
    outtextxy(px_i + 15, py + 2, (char*)"Luu y: Toc do tang theo diem. 3 mang la thua!");
    
    // Vertical separator
    veDuongThang(550, 590, 550, 670, woodDark);
    for(int y = 590; y < 670; y+=8) veDuongThang(550, y, 550, y+4, pillBg); // dashed effect
    
    // Icons layout
    int iconX = 580;
    int textX = 610;
    
    // Coin
    veDongXu(iconX, 602, 12, 0);
    setbkcolor(pillBg); setcolor(textBrown);
    outtextxy(textX, 602 + 2, (char*)": +10 Diem");
    
    // Fishbone
    veXuongCa(iconX, 632, 0.0);
    setbkcolor(pillBg); setcolor(textBrown);
    outtextxy(textX, 632 + 2, (char*)": -5 Diem");
    
    // Bomb
    veBom(iconX, 662, 1.0);
    setbkcolor(pillBg); setcolor(textBrown);
    outtextxy(textX, 662 + 2, (char*)": -1 Mang");
}
