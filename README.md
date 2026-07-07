# Space Invaders Project Structure

```text
space invaders/
├── src/                # Chứa toàn bộ file .cpp
├── include/            # Chứa toàn bộ file .hpp / .h
├── assets/             # Chứa hình ảnh, âm thanh, font chữ
├── docs/               # Chứa báo cáo PDF, hình ảnh UML
├── build/              # Thư mục chứa file thực thi .exe
├── CMakeLists.txt      # File cấu hình CMake (nếu sử dụng)
└── README.md           # Hướng dẫn cách build và chạy code
```
---
# Các Module Chính Của Game

## 1. Quản lý cửa sổ & Vòng lặp game (Game Loop)

Chịu trách nhiệm:

- Khởi tạo và quản lý cửa sổ game.
- Xử lý vòng lặp chính của trò chơi.
- Cập nhật trạng thái game theo từng frame.
- Xử lý sự kiện từ bàn phím, chuột (nếu có).
- Render toàn bộ đối tượng lên màn hình.

---

## 2. Quản lý trạng thái Game (Game State Management)

Quản lý việc chuyển đổi giữa các trạng thái khác nhau của game:

- Menu chính (Main Menu).
- Tạm dừng game (Pause).
- Tiếp tục trò chơi (Resume).
- Thoát game (Exit).
- Tăng/giảm âm lượng (Volume Up / Volume Down) nếu có hệ thống âm thanh.
- Hiển thị thông tin:
  - Điểm số (**Score**).
  - Số mạng còn lại (**Lives**).

---

# 3. Module Thực thể (Entities)

Quản lý các đối tượng xuất hiện trong game.

## Player (Tàu vũ trụ người chơi)

Chức năng:

- Điều khiển tàu của người chơi.
- Di chuyển trái/phải.
- Bắn đạn.
- Quản lý trạng thái sống/chết.

---

## Alien Swarm (Đoàn tàu địch)

Chức năng:

- Quản lý nhóm kẻ địch.
- Di chuyển theo đội hình.
- Đổi hướng khi chạm biên màn hình.
- Tăng tốc độ di chuyển sau mỗi lần đổi hướng.
- Sinh ra đạn từ kẻ địch.

---

## Bullet (Đạn)

Bao gồm:

- Đạn của người chơi.
- Đạn của kẻ địch.

Chức năng:

- Quản lý vị trí và hướng bay.
- Kiểm tra va chạm với các thực thể khác.
- Xóa đạn khi:
  - Ra khỏi màn hình.
  - Va chạm thành công.

> Việc quản lý danh sách đạn bay trên màn hình yêu cầu sử dụng cấu trúc dữ liệu phù hợp để tối ưu bộ nhớ và vòng lặp kiểm tra va chạm.
# Space Invaders - OOP Project Structure

```text
oop/
│
├── include/
│   ├── Game.hpp
│   ├── GameObject.hpp
│   ├── Player.hpp
│   ├── Alien.hpp
│   ├── Bullet.hpp
│   ├── AlienManager.hpp
│   ├── CollisionManager.hpp
│   ├── ResourceManager.hpp
│   ├── AudioManager.hpp
│   ├── UI.hpp
│   └── GameState.hpp
│
├── src/
│   ├── main.cpp
│   ├── Game.cpp
│   ├── GameObject.cpp
│   ├── Player.cpp
│   ├── Alien.cpp
│   ├── Bullet.cpp
│   ├── AlienManager.cpp
│   ├── CollisionManager.cpp
│   ├── ResourceManager.cpp
│   ├── AudioManager.cpp
│   └── UI.cpp
```

---

# Mô tả các file trong dự án

## Thư mục `include/`

Chứa toàn bộ file header (`.hpp`) khai báo class, thuộc tính và phương thức.

| File | Chức năng |
|---|---|
| `Game.hpp` | Quản lý toàn bộ vòng đời game, cửa sổ, vòng lặp chính và trạng thái game. |
| `GameObject.hpp` | Lớp cơ sở (base class) cho các đối tượng trong game. |
| `Player.hpp` | Khai báo lớp tàu người chơi, xử lý di chuyển và bắn đạn. |
| `Alien.hpp` | Khai báo lớp kẻ địch, quản lý vị trí và trạng thái Alien. |
| `Bullet.hpp` | Khai báo lớp đạn, quản lý hướng bay và va chạm. |
| `AlienManager.hpp` | Quản lý nhóm Alien, đội hình và tốc độ di chuyển. |
| `CollisionManager.hpp` | Xử lý kiểm tra va chạm giữa các đối tượng. |
| `ResourceManager.hpp` | Quản lý tài nguyên như texture, font, hình ảnh. |
| `AudioManager.hpp` | Quản lý âm thanh, hiệu ứng và nhạc nền. |
| `UI.hpp` | Quản lý giao diện người dùng như Score, Lives, Menu. |
| `GameState.hpp` | Quản lý các trạng thái của game (Menu, Playing, Pause, Game Over). |

---

# Thư mục `src/`

Chứa toàn bộ file triển khai (`.cpp`) của các class.

| File | Chức năng |
|---|---|
| `main.cpp` | Điểm bắt đầu chương trình, khởi tạo game. |
| `Game.cpp` | Cài đặt vòng lặp game, xử lý sự kiện, cập nhật và render. |
| `GameObject.cpp` | Cài đặt các thuộc tính chung của mọi đối tượng game. |
| `Player.cpp` | Xử lý logic điều khiển tàu người chơi. |
| `Alien.cpp` | Xử lý hành vi và chuyển động của Alien. |
| `Bullet.cpp` | Xử lý chuyển động, trạng thái và vòng đời của đạn. |
| `AlienManager.cpp` | Điều khiển toàn bộ đội hình Alien. |
| `CollisionManager.cpp` | Thực hiện kiểm tra và xử lý va chạm. |
| `ResourceManager.cpp` | Nạp và quản lý tài nguyên game. |
| `AudioManager.cpp` | Xử lý âm thanh trong game. |
| `UI.cpp` | Hiển thị giao diện, điểm số và trạng thái người chơi. |

---

# Kiến trúc OOP tổng quan

```text
                    Game
                     |
        ----------------------------
        |            |             |
   GameState        UI       ResourceManager
                     |
              GameObject (Base Class)
                     |
        ----------------------------
        |            |             |
     Player       Alien        Bullet
                     |
              AlienManager

CollisionManager
        |
  Kiểm tra tương tác
  giữa Player, Alien, Bullet
```

---

# Luồng hoạt động chính

1. `main.cpp` khởi tạo đối tượng `Game`.
2. `Game` tạo cửa sổ và bắt đầu vòng lặp game.
3. Trong mỗi frame:
   - Nhận input từ người chơi.
   - Cập nhật Player.
   - Cập nhật Alien.
   - Cập nhật Bullet.
   - Kiểm tra va chạm.
   - Cập nhật UI.
   - Render toàn bộ đối tượng.
4. Khi kết thúc:
   - Giải phóng tài nguyên.
   - Đóng cửa sổ game.