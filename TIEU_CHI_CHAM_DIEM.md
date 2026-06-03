# 📋 TIÊ CHÍ CHẤM ĐIỂM - GAME MÈO HƯỞNG ĐỒNG XU

## 📍 VỊ TRÍ CỦA CÁC TIÊU CHÍ TRONG CODE

### 1. **FILE CHÍNH: GiaoDien.c**
   - **Dòng ~150-200**: Hàm `xuLyVaCham()` - Xử lý collision và cập nhật điểm
   - **Dòng ~120-140**: Hàm `capNhatVatThe()` - Sinh vật thể ngẫu nhiên

### 2. **FILE VẼ VẬT THỂ: VatThe.c**
   - Hàm `veDongXu()` - Vẽ đồng xu với điểm hiển thị
   - Hàm `veBom()` - Vẽ bom
   - Hàm `veXuongCa()` - Vẽ xương cá
   - Hàm `veKhiNangLuong()` - Vẽ khiên bảo vệ
   - Hàm `veNamCham()` - Vẽ nam châm
   - Hàm `veDongHo()` - Vẽ đồng hồ (chưa đủ code)

### 3. **FILE VẼ CHỮ: Meo.c & TraiTim.c**
   - `Meo.c`: Vẽ nhân vật mèo với animation
   - `TraiTim.c`: Vẽ trái tim hiển thị mạng

---

## 🎯 BẢNG TIÊU CHÍ CHẤM ĐIỂM CHI TIẾT

| **Loại Vật Thể** | **Mã (loai)** | **Hiệu Ứng** | **Điểm** | **Tệp Code** | **Giao Diện** | **Ghi Chú** |
|---|---|---|---|---|---|---|
| **Đồng Xu** | 0 | Vàng lấp lánh | +10 | VatThe.c | GiaoDien.c | Vẽ bằng veDuongTron + toMauDeQuy, có dấu chân lòng bàn |
| **Bom** | 1 | Tối đen tối lửa | -1 Mạng | VatThe.c | GiaoDien.c | Vẽ sphere với lửa, nếu có khiên sẽ bảo vệ |
| **Xương Cá** | 2 | Trắng xám | -5 | VatThe.c | GiaoDien.c | Xoay được, có shadow để tạo chiều sâu |
| **Xu 20 Điểm** | 3 | Vàng sáng | +20 | VatThe.c | GiaoDien.c | Giống đồng xu nhưng lớn hơn, màu sáng hơn |
| **Xu 30 Điểm** | 4 | Vàng sáng (tối đa) | +30 | VatThe.c | GiaoDien.c | Lớn nhất, màu vàng rực rỡ nhất |
| **Trái Tim** | 5 | Hồng pastel | +1 Mạng | TraiTim.c | GiaoDien.c | Vẽ bằng 2 vòng tròn + tam giác dưới, màu hồng mềm mại |
| **Khiên Bảo Vệ** | 6 | Xanh lam sáng | +1 Khiên | VatThe.c | GiaoDien.c | Vẽ năng lượng xoay, tạo hiệu ứng bảo vệ |
| **Nam Châm** | 7 | Đỏ U & Xám | Hút XU 150f | VatThe.c | GiaoDien.c | Vẽ hình chữ U nam châm, xoay được |
| **Đồng Hồ** | 8 | Xanh dương | Chậm 200f | VatThe.c | GiaoDien.c | Chậm tốc độ game 50%, effect thời gian chậm |

---

## 📊 THỐNG KÊ SINH VẬT THỂ (GiaoDien.c ~dòng 155)

```c
// Tỉ lệ spawn ra của các vật thể:
Xu thường (0)     : 30%  (r < 300)
Xu 20 (3)         : 15%  (300-450)
Xu 30 (4)         : 10%  (450-550)
Xương Cá (2)      : 13%  (550-680)
Bom (1)           : 20%  (680-880)
Khiên (6)         : 3%   (880-910)
Nam Châm (7)      : 3%   (910-940)
Đồng Hồ (8)       : 5%   (940-990)
Trái Tim (5)      : 1%   (990-1000)
```

---

## 🎨 CHI TIẾT GIAO DIỆN

### **Giao Diện Chính (PlayGiaoDien)** - VeNenKhung.c
- **Header (0-80px)**: Hiển thị DIEM, CAO NHAT, MANG, CatCatch! title
- **Play Area (82-560px)**: Các vật thể rơi xuống, mèo ở dưới
- **Footer (560-700px)**: Nền cỏ, hàng rào gỗ

### **Sử dụng outtextxy** - GiaoDien.c
- Dòng ~250+: Hiển thị "+10", "+20", "+30" khi ăn xu
- Dòng ~260: Hiển thị "-5" khi ăn xương cá
- Dòng ~265: Hiển thị "+1 TIM" khi ăn trái tim
- Dòng ~270: Hiển thị "BAO VE" khi ăn khiên
- Dòng ~275: Hiển thị "HUT XU" khi ăn nam châm
- Dòng ~280: Hiển thị "CHAM LAI" khi ăn đồng hồ

---

## 🔧 HÀM VẼ CHÍNH VÀ CÁCH HOẠT ĐỘNG

### **VeHinh.c - Công cụ vẽ cơ bản:**
```c
void veDuongThang(x1, y1, x2, y2, color)      // Bresenham algorithm
void veDuongTron(xc, yc, r, color)             // Midpoint circle
void veHinhElip(xc, yc, rx, ry, color)         // Midpoint ellipse
void toMauDeQuy(x, y, fill_color, bound_color) // Flood fill (Recursive)
void toMauDeQuy_Safe(x, y, fill_color, bound_color, depth) // Safe version with depth limit
```

### **VatThe.c - Vẽ các vật thể:**
```c
void veDongXu(x, y, banKinh, diemCong)         // Vẽ xu với điểm hiển thị
void veBom(x, y, scale)                        // Vẽ bom với lửa
void veXuongCa(x, y, angle)                    // Vẽ xương cá xoay được
void veKhiNangLuong(x, y, angle, scale)        // Vẽ khiên năng lượng
void veNamCham(x, y, angle)                    // Vẽ nam châm U xoay được
```

---

## ⚙️ TỐI ƯU HÓA THUẬT TOÁN TÔ MÀU ĐỆ QUY

### **Vấn đề hiện tại:**
- Stack overflow do đệ quy quá sâu (> 15000)
- Không phù hợp cho các vùng lớn

### **Giải pháp hiện tại (VeHinh.c):**
```c
void toMauDeQuy_Safe(x, y, fill_color, boundary_color, depth) {
    if(depth > 15000) return;  // Giới hạn độ sâu
    // Chỉ tô khi pixel hiện tại không phải biên hoặc màu tô
}
```

### **Cải thiện đề xuất:**
1. Kiểm tra biên trước khi gọi recursion
2. Dùng VRAM cache để tránh getpixel chậm
3. Có thể chuyển sang queue-based flood fill (iterative) trong tương lai

---

## 📸 HIỆU ỨNG VISUAL

### **Đồng Xu (veDongXu)**
- Vẽ 2 vòng tròn: ngoài (gold), trong (light yellow)
- Dấu chân lòng bàn ở giữa
- Hiển thị "+10", "+20", hoặc "+30" bên cạnh

### **Bom (veBom)**
- Hình tròn đen tối
- Lửa cam/vàng ở trên
- Hộp đầu lâu trắng
- Scale nhỏ để "có vẻ tinh tế"

### **Xương Cá (veXuongCa)**
- Xương sống chính (trắng)
- 3 cặp xương sườn
- Đầu tròn bên trên
- Đuôi bên dưới
- Có shadow (xám) để tạo chiều sâu

### **Trái Tim (veTraiTim)**
- 2 vòng tròn hồng (trên)
- Tam giác hồng (dưới)
- Màu pastel hồng mềm

### **Khiên (veKhiNangLuong)**
- Core sáng (cyan)
- 4 vòng tròn năng lượng xoay quanh
- Hiệu ứng bảo vệ 1 lần va đập

### **Nam Châm (veNamCham)**
- Hình U từ tính
- Nửa trên đỏ (U positive)
- Nửa dưới xám (U negative)
- Xoay được theo hướng rơi

---

## 🎮 LUỒNG TRẠ CHƠI

1. **Sinh vật thể**: `capNhatVatThe()` - Random spawn các loại
2. **Di chuyển**: Rơi xuống với tốc độ tăng theo điểm
3. **Nam châm**: Nếu kích hoạt, các xu hút về mèo
4. **Đồng hồ**: Nếu kích hoạt, tốc độ rơi giảm 50%
5. **Va chạm**: `xuLyVaCham()` - Kiểm tra collider mèo vs vật thể
6. **Cập nhật**: Cộng/trừ điểm, mạng, hiệu ứng
7. **Hiển thị**: `outtextxy` hiển thị "+10", "-5" v.v.

---

## 🎨 CẤU TRÚC MÀU SẮC HÀI HÒA

- **Xu**: Vàng gold (255, 200, 30) / Vàng nhạt (255, 220, 80)
- **Bom**: Đen tối (30, 30, 35) / Lửa cam (255, 100, 0)
- **Xương**: Trắng (245, 245, 250) / Xám shadow (180, 180, 190)
- **Tim**: Hồng pastel (243, 139, 168) - Catppuccin Red
- **Khiên**: Xanh cyan (100, 200, 255) / Xanh đậm (50, 150, 255)
- **Nam châm**: Đỏ (220, 50, 50) / Xám (200, 200, 200)

---

**Cập nhật: 2026-06-03**
**Phiên bản: 1.0**
