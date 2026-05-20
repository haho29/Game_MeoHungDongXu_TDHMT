#include "VeHinh.h"
#include <graphics.h>
#include <math.h>
#include <stdlib.h>

// VRAM ao de giai quyet loi getpixel khong hoat dong tren hidden buffer cua WinBGIm
int vram[1000][700] = {0};

void my_putpixel(int x, int y, int color) {
    if (x >= 0 && x < 1000 && y >= 0 && y < 700) {
        vram[x][y] = color;
        putpixel(x, y, color);
    }
}

int my_getpixel(int x, int y) {
    if (x >= 0 && x < 1000 && y >= 0 && y < 700) {
        return vram[x][y];
    }
    return 0; // BLACK
}

void my_bar(int left, int top, int right, int bottom, int color) {
    setfillstyle(SOLID_FILL, color);
    bar(left, top, right, bottom);
    for (int x = left; x <= right; x++) {
        if (x < 0 || x >= 1000) continue;
        for (int y = top; y <= bottom; y++) {
            if (y < 0 || y >= 700) continue;
            vram[x][y] = color;
        }
    }
}

// Trien khai ham COLOR bi thieu trong thu vien winbgim cua Dev-C++
int COLOR(int r, int g, int b) {
    // WinBGIm su dung bit 0x04000000 de phan biet mau RGB va mau mac dinh cua BGI (0-15)
    return 0x04000000 | r | (g << 8) | (b << 16);
}

// =========================================================================
// THUẬT TOÁN BRESENHAM VẼ ĐOẠN THẲNG (Hỗ trợ đầy đủ tất cả 8 góc phần tư - 8 octants)
// Ý nghĩa: Sử dụng phép tính số nguyên (không dùng số thực) giúp tối ưu hóa tốc độ vẽ.
// =========================================================================
void veDuongThang(int x1, int y1, int x2, int y2, int color) {
    // Bước 1: Tính toán khoảng cách tọa độ dx, dy giữa hai điểm đầu mút
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int p;
    int x = x1;
    int y = y1;
    
    // Bước 2: Xác định hướng di chuyển (bước tiến) stepX, stepY
    // - step = 1 nếu điểm đích lớn hơn điểm đầu (di chuyển tiến)
    // - step = -1 nếu điểm đích nhỏ hơn điểm đầu (di chuyển lùi)
    // Điều này giúp thuật toán vẽ được mọi góc phần tư (trái-phải, phải-trái, trên-dưới)
    int stepX = (x2 > x1) ? 1 : -1;
    int stepY = (y2 > y1) ? 1 : -1;

    my_putpixel(x, y, color);

    // Bước 3: Phân loại trường hợp dựa trên hệ số góc m = dy/dx
    if (dx > dy) { 
        // -----------------------------------------------------------------
        // TRƯỜNG HỢP 1: |m| < 1 (Góc nghiêng nhỏ hơn 45 độ)
        // Trục X là trục tăng/giảm chính. Mỗi bước tiến X tăng/giảm 1 đơn vị.
        // -----------------------------------------------------------------
        p = 2 * dy - dx; // Tham số quyết định ban đầu p0
        for (int i = 0; i < dx; i++) {
            if (p < 0) {
                // Chọn điểm tiếp theo nằm ngang (cùng Y)
                p += 2 * dy; 
            } else {
                // Chọn điểm tiếp theo nằm chéo (thay đổi cả X và Y)
                // THỦ THUẬT CHỐNG TRÀN MÀU: Bịt kín đường chéo (4-connected)
                // Giúp thuật toán tô màu đệ quy không bị lọt qua khe chéo 1 pixel
                my_putpixel(x + stepX, y, color);
                
                p += 2 * (dy - dx);
                y += stepY; // Thay đổi Y theo hướng stepY
            }
            x += stepX; // X luôn thay đổi 1 bước tiến
            my_putpixel(x, y, color);
        }
    } else { 
        // -----------------------------------------------------------------
        // TRƯỜNG HỢP 2: |m| >= 1 (Góc nghiêng lớn hơn hoặc bằng 45 độ)
        // Trục Y là trục tăng/giảm chính. Mỗi bước tiến Y tăng/giảm 1 đơn vị.
        // -----------------------------------------------------------------
        p = 2 * dx - dy; // Tham số quyết định ban đầu p0
        for (int i = 0; i < dy; i++) {
            if (p < 0) {
                // Chọn điểm tiếp theo thẳng đứng (cùng X)
                p += 2 * dx; 
            } else {
                // Chọn điểm tiếp theo nằm chéo (thay đổi cả X và Y)
                // THỦ THUẬT CHỐNG TRÀN MÀU: Bịt kín góc chéo
                my_putpixel(x, y + stepY, color);
                
                p += 2 * (dx - dy);
                x += stepX; // Thay đổi X theo hướng stepX
            }
            y += stepY; // Y luôn thay đổi 1 bước tiến
            my_putpixel(x, y, color);
        }
    }
}

// =========================================================================
// THUẬT TOÁN MIDPOINT VẼ ĐƯỜNG TRÒN
// Ý nghĩa: Tận dụng tính đối xứng 8 phần (8-way symmetry) để chỉ cần tính toán 
// cho 1/8 đường tròn, sau đó lấy đối xứng ra toàn bộ đường tròn.
// =========================================================================
void veDuongTron(int xc, int yc, int r, int color) {
    int x = 0;
    int y = r;
    int p = 1 - r; // Giá trị quyết định ban đầu tại điểm (0, r)

    while (x < y) {
        // Vẽ 8 điểm đối xứng qua tâm đường tròn (xc, yc)
        my_putpixel(xc + x, yc + y, color); // Phần 1
        my_putpixel(xc - x, yc + y, color); // Phần 2
        my_putpixel(xc + x, yc - y, color); // Phần 3
        my_putpixel(xc - x, yc - y, color); // Phần 4
        my_putpixel(xc + y, yc + x, color); // Phần 5
        my_putpixel(xc - y, yc + x, color); // Phần 6
        my_putpixel(xc + y, yc - x, color); // Phần 7
        my_putpixel(xc - y, yc - x, color); // Phần 8
        
        x++;
        if (p < 0) {
            // Chọn điểm tiếp theo nằm ngang (E): x_next = x + 1, y_next = y
            p += 2 * x + 1; 
        } else {
            // Chọn điểm tiếp theo nằm chéo xuống dưới (SE): x_next = x + 1, y_next = y - 1
            // THỦ THUẬT BỊT KÍN KHE CHÉO: Vẽ điểm lân cận để tránh lọt màu khi tô đệ quy
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
    
    // Vẽ điểm giao nhau cuối cùng khi x == y
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

// =========================================================================
// THUẬT TOÁN TÔ MÀU ĐỆ QUY (Boundary Fill Algorithm - 4-Connected)
// Ý nghĩa: Bắt đầu từ một điểm hạt giống (seed point) có tọa độ (x, y), 
// loang màu tô (fill_color) ra 4 phía xung quanh (Đông, Tây, Nam, Bắc) 
// cho đến khi chạm vào đường biên có màu sắc chỉ định (boundary_color).
// =========================================================================

// Hàm hỗ trợ đệ quy an toàn tránh tràn ngăn xếp (Stack Overflow)
void toMauDeQuy_Safe(int x, int y, int fill_color, int boundary_color, int depth) {
    // Trường hợp biên 1: Vượt ngoài giới hạn màn hình (1000x700) -> Dừng loang
    if(x < 0 || y < 0 || x >= 1000 || y >= 700) return;
    
    // Trường hợp biên 2: Giới hạn độ sâu đệ quy để tránh tràn bộ nhớ ngăn xếp (Stack Overflow)
    // Hệ thống dùng VRAM ảo đọc ghi cực nhanh nên giới hạn 15000 là tối ưu và an toàn tuyệt đối.
    if(depth > 15000) return; 

    // Đọc màu sắc hiện tại của điểm ảnh từ mảng bộ nhớ ảo VRAM thay vì dùng getpixel().
    // LÝ DO: Hàm getpixel() mặc định của WinBGIm bị lỗi không đọc được màu sắc
    // khi vẽ trên vùng nhớ đệm ẩn (hidden double buffer). VRAM ảo khắc phục triệt để lỗi này.
    int current_color = my_getpixel(x, y); 
    
    // Điều kiện loang tiếp:
    // Điểm ảnh hiện tại CHƯA PHẢI là màu biên (boundary_color) 
    // và CŨNG CHƯA ĐƯỢC tô bằng màu mới (fill_color)
    if (current_color != boundary_color && current_color != fill_color) {
        // Tô điểm ảnh hiện tại bằng màu tô mới
        my_putpixel(x, y, fill_color);
        
        // Gọi đệ quy loang màu ra 4 hướng (4-connected):
        toMauDeQuy_Safe(x + 1, y, fill_color, boundary_color, depth + 1); // Loang sang phải (Đông)
        toMauDeQuy_Safe(x - 1, y, fill_color, boundary_color, depth + 1); // Loang sang trái (Tây)
        toMauDeQuy_Safe(x, y + 1, fill_color, boundary_color, depth + 1); // Loang xuống dưới (Nam)
        toMauDeQuy_Safe(x, y - 1, fill_color, boundary_color, depth + 1); // Loang lên trên (Bắc)
    }
}

// Hàm khởi chạy thuật toán tô màu đệ quy
void toMauDeQuy(int x, int y, int fill_color, int boundary_color) {
    // Bắt đầu đệ quy từ độ sâu ban đầu là 0
    toMauDeQuy_Safe(x, y, fill_color, boundary_color, 0);
}

// =========================================================================
// THUẬT TOÁN ĐỆ QUY VẼ ĐƯỜNG CONG FRACTAL KOCH (Bông tuyết Koch)
// Ý nghĩa: Kiến tạo cấu trúc tự đồng dạng (self-similar) từ công thức toán học.
// Ứng dụng thực tế: Được lồng ghép làm bụi cây gai tự nhiên hai bên màn hình game.
// =========================================================================
void veDuongKoch(int x1, int y1, int x2, int y2, int color, int depth) {
    // Trường hợp cơ bản (Base Case): Độ sâu đệ quy bằng 0 -> Vẽ đoạn thẳng trực tiếp
    if (depth == 0) {
        veDuongThang(x1, y1, x2, y2, color);
    } else {
        // Tính toán khoảng cách vector dy, dx giữa hai đầu mút
        int dx = x2 - x1;
        int dy = y2 - y1;
        
        // Bước 1: Xác định điểm chia 1/3 thứ nhất (P1)
        int p1x = x1 + dx / 3;
        int p1y = y1 + dy / 3;
        
        // Bước 2: Xác định điểm chia 2/3 thứ hai (P3)
        int p3x = x1 + 2 * dx / 3;
        int p3y = y1 + 2 * dy / 3;
        
        // Bước 3: Xác định đỉnh nhọn ở giữa (P2) bằng phép xoay vector 60 độ ngược chiều kim đồng hồ
        // Công thức xoay vector v = (dx/3, dy/3) đi một góc -60 độ (nhọn hướng lên trên):
        // x' = x*cos(-60) - y*sin(-60) = x*0.5 + y*0.866
        // y' = x*sin(-60) + y*cos(-60) = -x*0.866 + y*0.5
        double cos60 = 0.5;
        double sin60 = 0.86602540378; // Giá trị chính xác của sin(60 độ)
        
        double vx = dx / 3.0;
        double vy = dy / 3.0;
        
        // Điểm P2 là điểm nhọn nhô lên
        int p2x = p1x + (int)(vx * cos60 + vy * sin60);
        int p2y = p1y + (int)(-vx * sin60 + vy * cos60);
        
        // Bước 4: Gọi đệ quy vẽ 4 phân đoạn tự đồng dạng với độ sâu đệ quy giảm đi 1 (depth - 1)
        veDuongKoch(x1, y1, p1x, p1y, color, depth - 1);       // Phân đoạn 1: Từ đầu mút 1 đến điểm 1/3
        veDuongKoch(p1x, p1y, p2x, p2y, color, depth - 1);     // Phân đoạn 2: Lên đỉnh nhọn
        veDuongKoch(p2x, p2y, p3x, p3y, color, depth - 1);     // Phân đoạn 3: Xuống khỏi đỉnh nhọn
        veDuongKoch(p3x, p3y, x2, y2, color, depth - 1);       // Phân đoạn 4: Từ điểm 2/3 đến đầu mút 2
    }
}

// Phep bien doi 2 chieu (Quay quanh tam)
void PhepQuay2D(int *px, int *py, int cx, int cy, double angle) {
    int dx = *px - cx;
    int dy = *py - cy;
    
    *px = cx + (int)(dx * cos(angle) - dy * sin(angle));
    *py = cy + (int)(dx * sin(angle) + dy * cos(angle));
}

// Phep bien doi 2 chieu (Co gian quanh tam)
void PhepCoGian2D(int *px, int *py, int cx, int cy, double sx, double sy) {
    int dx = *px - cx;
    int dy = *py - cy;
    
    *px = cx + (int)(dx * sx);
    *py = cy + (int)(dy * sy);
}

// Phep bien doi 2 chieu (Doi xung truc doc / Lat ngang)
void PhepDoiXung2D(int *px, int *py, int cx, bool flipHorizontal) {
    if (flipHorizontal) {
        int dx = *px - cx;
        *px = cx - dx; // Lat x qua cx
    }
}
