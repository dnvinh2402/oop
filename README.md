# BÁO CÁO ĐỒ ÁN OOP
## MÔN LẬP TRÌNH HƯỚNG ĐỐI TƯỢNG 

# ĐỀ TÀI: SPACE INVADERS

**Ngôn ngữ lập trình:** C++  
**Thư viện đồ họa & âm thanh:** SFML 3

---

# LỜI MỞ ĐẦU

Trong bài tập lớn môn **Lập trình Hướng đối tượng**, nhóm thực hiện xây dựng trò chơi **Space Invaders** bằng ngôn ngữ **C++**, kết hợp thư viện **SFML 3** để xử lý đồ họa và âm thanh.

Dự án được xây dựng với mục tiêu vận dụng các kiến thức lập trình hướng đối tượng vào một sản phẩm phần mềm có cấu trúc tương đối hoàn chỉnh. Thông qua việc tổ chức các thực thể trong game thành các class riêng biệt, dự án tập trung thể hiện bốn đặc trưng quan trọng của OOP gồm **Kế thừa (Inheritance)**, **Đa hình (Polymorphism)**, **Đóng gói (Encapsulation)** và **Trừu tượng (Abstraction)**.

Bên cạnh phần xử lý gameplay, chương trình cũng được phân chia thành các module quản lý thực thể, va chạm, tài nguyên, âm thanh và giao diện. Cách tổ chức này giúp mã nguồn có cấu trúc rõ ràng, thuận tiện cho việc phát triển, kiểm thử và mở rộng trong tương lai.

---

# 1. GIỚI THIỆU ĐỀ TÀI

## 1.1. Thông tin chung

| Nội dung | Thông tin |
|---|---|
| **Tên dự án** | Space Invaders |
| **Ngôn ngữ lập trình** | C++ |
| **Thư viện đồ họa & âm thanh** | SFML 3 |
| **Môn học** | Lập trình Hướng đối tượng |

## 1.2. Ý tưởng trò chơi

Người chơi bước vào một cuộc chiến sinh tử giữa nhân loại và những kẻ xâm lược ngoài hành tinh. Không có lời cảnh báo, không có đàm phán – chỉ có một làn sóng quái vật không gian đang ồ ạt tiến xuống Trái Đất.

Người chơi đóng vai trò là **tuyến phòng thủ cuối cùng**, điều khiển một khẩu pháo laser đơn độc để chống lại lực lượng Alien.

Mục tiêu chính của trò chơi là:

- Điều khiển phi thuyền người chơi.
- Bắn hạ từng kẻ địch.
- Sống sót trong quá trình chiến đấu.
- Tiêu diệt toàn bộ **Alien**.

---

# 2. LUẬT CHƠI VÀ LUỒNG HOẠT ĐỘNG

## 2.1. Vai trò của người chơi

Người chơi điều khiển thực thể **Player**, đại diện cho phi thuyền của tuyến phòng thủ cuối cùng.

Trong quá trình chơi, người chơi phải:

- Điều khiển **Player**.
- Sử dụng **Bullt** để tiêu diệt **Alien**.
- Tận dụng các hiệu ứng **Buff** khi nhặt được item.
- Cố gắng sống sót và hoàn thành mục tiêu tiêu diệt toàn bộ Alien.

## 2.2. Luồng tổng quát của trò chơi

Luồng giao diện chính của chương trình được tổ chức theo trình tự:

**Main Menu → Vào Game → PauseMenu → Game Over → ScoreHistoryMenu**

Trong đó:

- **MainMenu:** giao diện menu chính.
- **Game:** khu vực diễn ra gameplay.
- **PauseMenu:** giao diện tạm dừng trò chơi.
- **GameOverMenu:** giao diện khi trò chơi kết thúc.
- **ScoreHistoryMenu:** giao diện xem lịch sử điểm.

---

# 3. THIẾT KẾ HỆ THỐNG

## 3.1. Kiến trúc tổng quan

Hệ thống được tổ chức thành nhiều class và module với các trách nhiệm tương đối rõ ràng. Các thực thể trong game được xây dựng dựa trên class nền tảng **GameObject**, trong khi những hệ thống quản lý chuyên biệt đảm nhiệm việc điều phối và xử lý các chức năng tương ứng.

Một số thành phần chính gồm:

- **Game**
- **GameState**
- **GameObject**
- **Player**
- **Alien**
- **Bullet**
- **Missile**
- **Buff**
- **AlienManager**
- **BuffManager**
- **CollisionManager**
- **SoundManager**
- **ResourceManager**
- **MainMenu**
- **PauseMenu**
- **GameOverMenu**
- **ScoreHistoryMenu**
- **GlobalAudio**

Cách phân chia này giúp giảm việc tập trung toàn bộ logic vào một class duy nhất và tạo điều kiện để các thành phần có thể được phát triển độc lập hơn.

---

# 4. VẬN DỤNG 4 TÍNH CHẤT CỦA OOP

Một trong những mục tiêu quan trọng của dự án là áp dụng các nguyên lý cốt lõi của **Lập trình Hướng đối tượng** vào việc xây dựng game.

## 4.1. Tính Kế thừa (Inheritance)

**Kế thừa** cho phép một class mới sử dụng lại các thuộc tính và phương thức của một class cơ sở.

Trong dự án, **GameObject** được sử dụng làm class nền tảng cho các thực thể trong game.

Các class:

- **Player**
- **Alien**
- **Bullet**
- **Missile**
- **Buff**

đều kế thừa từ **GameObject**.

Mô hình có thể được khái quát như sau:

```text
                         ┌───────────────┐
                         │  GameObject   │
                         └───────┬───────┘
                                 │
       ┌─────────────┬───────────┼───────────┬─────────────┐
       │             │           │           │             │
       ▼             ▼           ▼           ▼             ▼
 ┌──────────┐  ┌──────────┐  ┌─────────┐  ┌─────────┐  ┌──────────┐
 │  Player  │  │  Alien   │  │  Bullet │  │   Buff  │  │  Missile │
 └──────────┘  └──────────┘  └─────────┘  └─────────┘  └──────────┘
                           
```

> Sơ đồ trên nhằm minh họa quan hệ kế thừa giữa các thực thể; cấu trúc thực tế cần được đối chiếu với source code của dự án.

Việc sử dụng **GameObject** làm nền tảng mang lại lợi ích:

- Tái sử dụng phần code chung cho các đối tượng.
- Hạn chế việc viết lại những thành phần giống nhau.
- Tạo một cấu trúc thống nhất cho các thực thể trong game.
- Giúp mở rộng thêm các loại đối tượng mới thuận tiện hơn.

Hệ thống giao diện cũng được chia thành các class riêng biệt như **MainMenu**, **PauseMenu**, **GameOverMenu** và **ScoreHistoryMenu**, qua đó tổ chức các thành phần UI theo từng chức năng cụ thể.

---

## 4.2. Tính Đa hình (Polymorphism)

**Đa hình** cho phép các đối tượng thuộc những class khác nhau nhưng có cùng interface hoặc cùng nguồn gốc kế thừa có thể thực hiện hành vi theo cách riêng của chúng.

Trong dự án, các class kế thừa từ **GameObject** có những hành vi chung như:

- `update()`
- `draw()`

Các phương thức này được **override** để phù hợp với từng loại đối tượng.

Ví dụ:

- **Player** có logic điều khiển và di chuyển của người chơi.
- **Alien** có logic di chuyển của kẻ địch.
- **Bullet** có hành vi bay theo cơ chế của đạn.
- **Missile** có hành vi bay và xử lý riêng so với Bullet.

Nhờ **đa hình**, cùng một nhóm thao tác có thể được áp dụng cho nhiều loại đối tượng, trong khi mỗi đối tượng vẫn duy trì cách xử lý riêng.

Điều này đặc biệt hữu ích trong game vì nhiều thực thể cần được cập nhật và hiển thị liên tục trong vòng lặp game nhưng hành vi của chúng không giống nhau.

---

## 4.3. Tính Đóng gói (Encapsulation)

**Đóng gói** là việc kết hợp dữ liệu và các phương thức xử lý dữ liệu vào trong class, đồng thời hạn chế việc truy cập trực tiếp từ bên ngoài.

Trong dự án, các class quản lý hệ thống như:

- **AlienManager**
- **BuffManager**
- **CollisionManager**
- **SoundManager**
- **ResourceManager**

đảm nhiệm những phần logic xử lý riêng.

Các biến dữ liệu và logic nội bộ được tổ chức bên trong class, trong đó những dữ liệu cần bảo vệ được khai báo ở phạm vi **private**. Bên ngoài chỉ sử dụng các phương thức **public** mà class cung cấp.

Ví dụ về vai trò của các manager:

### **AlienManager**

Quản lý các đối tượng **Alien** và hệ thống sinh quái.

### **BuffManager**

Quản lý các **Buff** được sinh ra trong game, quá trình cập nhật và xử lý các item.

### **CollisionManager**

Đảm nhiệm việc xử lý các tương tác va chạm giữa những đối tượng liên quan trong game.

### **SoundManager**

Quản lý các hoạt động liên quan đến âm thanh.

### **ResourceManager**

Quản lý tài nguyên được sử dụng trong chương trình.

Nhờ đóng gói, class **Game** không cần trực tiếp biết toàn bộ cách các manager thực hiện công việc bên trong. **Game** chủ yếu gọi các phương thức được cung cấp để điều phối hoạt động của hệ thống.

---

## 4.4. Tính Trừu tượng (Abstraction)

**Trừu tượng** cho phép che giấu những chi tiết triển khai không cần thiết và chỉ thể hiện những thành phần quan trọng đối với việc sử dụng đối tượng.

Trong dự án, logic lõi của game được tách biệt khỏi các thành phần hiển thị và quản lý tài nguyên.

Có thể chia hệ thống thành các nhóm chính:

```text
Game / GameState
       |
       +------------------+
       |                  |
       v                  v
      UI             ResourceManager
       |                  |
       v                  v
 MainMenu/...        GlobalAudio
```

Trong đó:

- **Game** và **GameState** tập trung vào logic và trạng thái của trò chơi.
- Các class **UI** phụ trách phần giao diện.
- **ResourceManager** xử lý tài nguyên.
- **GlobalAudio** xử lý phần âm thanh dùng ở phạm vi hệ thống.

Cách tổ chức này giúp phần logic gameplay không phải phụ thuộc trực tiếp vào từng chi tiết triển khai của giao diện hoặc tài nguyên.

---

# 5. CÁC MODULE CHÍNH

## 5.1. Game và GameState

**Game** đóng vai trò điều phối các thành phần chính của trò chơi.

**GameState** được sử dụng để tổ chức trạng thái hoạt động của game, giúp tách biệt các trạng thái khác nhau trong quá trình sử dụng chương trình.

Việc tách **Game** và **GameState** góp phần làm cho phần xử lý gameplay và quản lý trạng thái có cấu trúc rõ ràng hơn.

## 5.2. GameObject

**GameObject** là class nền tảng của hệ thống thực thể.

Các thực thể như **Player**, **Alien**, **Bullet**, **Missile** và **Buff** kế thừa từ class này để sử dụng lại cấu trúc chung.

## 5.3. Player

**Player** đại diện cho nhân vật do người chơi điều khiển.

Player có vai trò chính trong gameplay:

- Điều khiển khẩu pháo laser.
- Thực hiện hoạt động bắn.
- Tương tác với các đối tượng trong game.
- Nhặt và sử dụng **Buff**.

## 5.4. Alien

**Alien** đại diện cho các kẻ xâm lược ngoài hành tinh.

Hệ thống sử dụng **AlienManager** để hỗ trợ quản lý và sinh các Alien trong game.

## 5.5. Bullet và Missile

**Bullet** đại diện cho đạn được sử dụng trong chiến đấu.

**Missile** là một loại thực thể tấn công riêng, có hành vi khác với Bullet và được xử lý thông qua cơ chế đa hình của hệ thống thực thể.

## 5.6. Buff

**Buff** đại diện cho các item có hiệu ứng hỗ trợ người chơi.

Các hiệu ứng Buff được kiểm thử trong quá trình phát triển, bao gồm:

- Hiệu ứng **đạn đôi**.
- Hiệu ứng liên quan đến **Missile**.
- Cơ chế nhặt item.

## 5.7. Các Manager

Hệ thống Manager được sử dụng để tách riêng những nhiệm vụ quản lý:

| Module | Vai trò |
|---|---|
| **AlienManager** | Quản lý và sinh Alien |
| **BuffManager** | Quản lý Buff/item |
| **CollisionManager** | Xử lý va chạm |
| **SoundManager** | Quản lý âm thanh |
| **ResourceManager** | Quản lý tài nguyên |

Việc phân chia này hỗ trợ nguyên tắc tổ chức module và giảm sự phụ thuộc trực tiếp giữa các thành phần.

---

# 6. CẤU TRÚC CÀI ĐẶT

Dự án được phân chia thành các thư mục theo chức năng.

```text
Space-Invaders/
│
├── assets/
│   ├── audio/
│   └── images/
│
├── include/
│   └── *.hpp
│
├── src/
│   └── *.cpp
│
├── build/
│   ├── main.exe
│   └── *.dll
│
├── highscore.txt
└── history.txt
```

## 6.1. Thư mục `assets/`

Thư mục **assets/** dùng để quản lý tài nguyên media của game.

### `assets/audio/`

Chứa các tài nguyên âm thanh như:

- Nhạc nền.
- Tiếng nổ.
- Hiệu ứng súng.
- Các hiệu ứng âm thanh khác được sử dụng trong game.

### `assets/images/`

Chứa các hình ảnh/sprite phục vụ cho game, bao gồm:

- Sprite tàu.
- Sprite Alien.
- Hình ảnh đạn.
- Hình ảnh khiên.
- Các tài nguyên hình ảnh liên quan.

## 6.2. Thư mục `include/`

Thư mục **include/** chứa các file header **`.hpp`**.

Các file này chủ yếu khai báo:

- Class.
- Thuộc tính.
- Phương thức.
- Quan hệ giữa các thành phần.

## 6.3. Thư mục `src/`

Thư mục **src/** chứa các file mã nguồn **`.cpp`**.

Đây là nơi định nghĩa chi tiết logic của các class đã được khai báo trong `include/`.

## 6.4. Thư mục `build/`

Thư mục **build/** chứa các file phục vụ quá trình chạy chương trình, bao gồm:

- `main.exe`
- Các thư viện động **`.dll`** của **SFML 3**.

## 6.5. File lưu trữ dữ liệu

Dự án sử dụng:

- **`highscore.txt`**: lưu thành tích điểm cao.
- **`history.txt`**: lưu lịch sử điểm của người chơi.

---

# 7. GIAO DIỆN NGƯỜI DÙNG

## 7.1. Luồng giao diện

Luồng UI của chương trình:

```text
+------------+
| Main Menu  |
+-----+------+
      |
      v
+------------+
|  Vào Game  |
+-----+------+
      |
      v
+-------------+
| Pause Menu  |
+------+------+ 
       |
       v
+-------------+
|  Game Over  |
+------+------+ 
       |
       v
+--------------------+
| Score History Menu |
+--------------------+
```

Các thành phần UI được chia thành các class:

- **MainMenu**
- **PauseMenu**
- **GameOverMenu**
- **ScoreHistoryMenu**

Cách tổ chức này giúp mỗi menu đảm nhiệm một chức năng giao diện riêng.

---

# 8. KIỂM THỬ

## 8.1. Nội dung kiểm thử

Trong quá trình phát triển, các chức năng sau đã được kiểm thử:

- **Hệ thống va chạm (`CollisionManager`)**
- **Hệ thống sinh quái (`AlienManager`)**
- **Hiệu ứng Buff/nhặt item**
- **Bắn đạn đôi**
- **Missile**
- **Âm thanh động**

## 8.2. Kiểm thử giao diện

### Main Menu

[Chèn ảnh màn hình: Main Menu]

### Gameplay

[Chèn ảnh màn hình: Màn hình gameplay chính]

### Pause Menu

[Chèn ảnh màn hình: Pause Menu]

### Buff / Item

[Chèn ảnh màn hình: Hiệu ứng Buff hoặc quá trình nhặt item]

### Bắn đạn đôi / Missile

[Chèn ảnh màn hình: Bắn đạn đôi hoặc Missile]

### Game Over

[Chèn ảnh màn hình: Game Over Menu]

### Score History

[Chèn ảnh màn hình: Score History Menu]

### Âm thanh

[Chèn ảnh màn hình: Minh họa giao diện/chức năng có âm thanh động]

## 8.3. Kết quả kiểm thử

Các chức năng được liệt kê trong phạm vi kiểm thử đã được nhóm thực hiện kiểm tra trong quá trình phát triển, bao gồm hệ thống va chạm, sinh Alien, Buff/item, đạn đôi, Missile và âm thanh động.

Các hình ảnh minh họa kết quả thực tế có thể được bổ sung vào các vị trí placeholder ở trên.

---

# 9. PHÂN CÔNG CÔNG VIỆC NHÓM

| Thành viên | Công việc | Hoàn thành |
|---|---|---:|
| **Quân** | Buff, Audio, Collision | **34%** |
| **Vinh** | Alien, Bullet, Player, Image | **35%** |
| **Huy** | History, UI, Menu | **31%** |
| **Tổng cộng** |  | **100%** |

Việc phân chia công việc được thực hiện theo từng nhóm chức năng của hệ thống, qua đó mỗi thành viên chịu trách nhiệm đối với những module được giao.

---

# 10. HƯỚNG PHÁT TRIỂN TƯƠNG LAI

Dự án có thể tiếp tục được mở rộng theo các hướng sau:

## 10.1. Mở rộng Game State

Phát triển thêm nhiều **Game State** mới nhằm mở rộng cách tổ chức trạng thái của trò chơi.

Việc bổ sung các state mới giúp hệ thống có thể quản lý nhiều trạng thái hoạt động khác nhau một cách rõ ràng hơn.

## 10.2. Đa dạng hóa kẻ địch

Phát triển thêm nhiều loại **Alien** khác nhau và bổ sung **Boss**.

Mục tiêu là tạo sự đa dạng hơn cho hệ thống kẻ địch và mở rộng khả năng phát triển gameplay.

## 10.3. Mở rộng hệ thống đạn

Bổ sung thêm nhiều loại **Bullet** mới với các đặc điểm khác nhau.

## 10.4. Đa dạng hóa phi thuyền

Thêm nhiều mẫu **Spaceship** cho người chơi để mở rộng lựa chọn và khả năng phát triển hệ thống Player.

---

# 11. KẾT LUẬN

Qua quá trình xây dựng dự án **Space Invaders**, nhóm đã áp dụng các kiến thức của môn **Lập trình Hướng đối tượng** vào một chương trình game viết bằng **C++** và sử dụng **SFML 3**.

Điểm trọng tâm của dự án là việc tổ chức hệ thống theo hướng đối tượng thông qua bốn tính chất:

- **Kế thừa (Inheritance)** với nền tảng **GameObject**.
- **Đa hình (Polymorphism)** thông qua các hành vi được ghi đè như `update()` và `draw()`.
- **Đóng gói (Encapsulation)** thông qua các module quản lý như **AlienManager**, **BuffManager**, **CollisionManager**, **SoundManager** và **ResourceManager**.
- **Trừu tượng (Abstraction)** thông qua việc tách biệt logic game, giao diện và quản lý tài nguyên.

Bên cạnh đó, dự án được tổ chức thành các module và thư mục riêng biệt, bao gồm tài nguyên, header, source code, file thực thi và dữ liệu điểm số. Một số hệ thống quan trọng như va chạm, sinh quái, Buff/item, đạn đôi, Missile và âm thanh động đã được kiểm thử.

Dự án cũng đặt nền tảng để tiếp tục phát triển trong tương lai thông qua việc mở rộng **Game State**, đa dạng hóa **Alien**, bổ sung **Boss**, các loại **Bullet** mới và nhiều mẫu **Spaceship**.

---

# 12. PHỤ LỤC

## 12.1. Cấu trúc class tiêu biểu

Quan hệ kế thừa chính của các thực thể có thể được mô tả khái quát:

```text
                         GameObject
                    _________|_________
                   /    /     |     \   \
                  /    /      |      \   \
              Player Alien  Bullet  Missile Buff
```

Các class giao diện được tổ chức riêng:

```text
UI
├── MainMenu
├── PauseMenu
├── GameOverMenu
└── ScoreHistoryMenu
```

> Các sơ đồ trên mang tính minh họa cho cấu trúc được mô tả trong báo cáo.

## 12.2. Vị trí bổ sung hình ảnh

Người thực hiện có thể bổ sung các ảnh chụp màn hình thực tế vào phần **Kiểm thử** tại các placeholder:

- `[Chèn ảnh màn hình: Main Menu]`
- `[Chèn ảnh màn hình: Màn hình gameplay chính]`
- `[Chèn ảnh màn hình: Pause Menu]`
- `[Chèn ảnh màn hình: Hiệu ứng Buff hoặc quá trình nhặt item]`
- `[Chèn ảnh màn hình: Bắn đạn đôi hoặc Missile]`
- `[Chèn ảnh màn hình: Game Over Menu]`
- `[Chèn ảnh màn hình: Score History Menu]`
- `[Chèn ảnh màn hình: Minh họa giao diện/chức năng có âm thanh động]`

---

# 13. TÀI LIỆU THAM KHẢO

1. **Source code ý tưởng tham khảo:**  
   https://github.com/attreyabhatt/Space-Invaders-Pygame

2. **Cảm hứng Gameplay:**  
   https://www.youtube.com/shorts/u2e5RYYej_4

3. **Github mã nguồn của nhóm:**  
   https://github.com/dnvinh2402/oop

---

# HẾT
