# Space Invaders OOP Project

## Tổng quan

Space Invaders OOP là một đồ án game shooter 2D phát triển bằng C++ và SFML3. Người chơi điều khiển một tàu vũ trụ trên màn hình, tiêu diệt các loại quái vật, thu buff và cố gắng sống sót qua các vòng chơi.

## Tính năng chính

- Di chuyển bằng `WASD` / `arrow keys`.
- Bắn bằng `Space` hoặc chuột trái.
- 3 loại thuyền chính với các chỉ số khác nhau
- 3 loại quái: `Patrol`, `Orbit`, `Boss`.
- Buff gồm `doubleShot`, `Shield`, `Bomb`.
- Menu chính, Pause menu, Game over, Victory và Score history.
- Lưu điểm cao và lịch sử 5 trận gần nhất.
- Quản lý tài nguyên texture/font với `ResourceManager`.
- Âm thanh hiệu ứng và nhạc nền.

## Cấu trúc dự án

```
oop/
├── assets/
│   ├── audio/
│   └── images/
├── build/
├── docs/
│   ├── highscore.txt
│   └── history.txt
├── include/
│   ├── Alien.hpp
│   ├── AlienManager.hpp
│   ├── Buff.hpp
│   ├── BuffManager.hpp
│   ├── Bullet.hpp
│   ├── CollisionManager.hpp
│   ├── Game.hpp
│   ├── GameObject.hpp
│   ├── GameOverMenu.hpp
│   ├── GameState.hpp
│   ├── GlobalAudio.hpp
│   ├── MainMenu.hpp
│   ├── Missile.hpp
│   ├── PauseMenu.hpp
│   ├── Player.hpp
│   ├── ResourceManager.hpp
│   ├── ScoreHistoryMenu.hpp
│   ├── SoundManager.hpp
├   ├── ShipSelectionMenu.hpp
│   └── UI.hpp
├── src/
│   ├── Alien.cpp
│   ├── AlienManager.cpp
│   ├── Buff.cpp
│   ├── BuffManager.cpp
│   ├── Bullet.cpp
│   ├── CollisionManager.cpp
│   ├── Game.cpp
│   ├── GameOverMenu.cpp
│   ├── GlobalAudio.cpp
│   ├── MainMenu.cpp
│   ├── Missile.cpp
│   ├── PauseMenu.cpp
│   ├── Player.cpp
│   ├── ResourceManager.cpp
│   ├── ScoreHistoryMenu.cpp
│   ├── SoundManager.cpp
├   ├── ShipSelectionMenu.cpp
│   ├── UI.cpp
│   └── main.cpp
├── UML/
│   ├── class_diagram.md
│   ├── sequence_diagrams.md
│   ├── summary.md
│   └── uml_diagrams.md
└── README.md
```

- `assets/`: chứa ảnh, âm thanh và font.
- `build/`: output binary.
- `docs/`: chứa điểm cao và lịch sử trận.
- `include/`: khai báo header cho các class.
- `src/`: định nghĩa hành vi và logic game.
- `UML/`: chứa sơ đồ lớp, sơ đồ trình tự và tóm tắt kiến trúc dự án.

## Luồng chương trình chính

1. `main.cpp` tạo `Game myGame;` và gọi `myGame.Run();`.
2. `Game::Game()` khởi tạo cửa sổ, load tài nguyên, tạo đối tượng `Player`, `AlienManager`, `BuffManager`, `UI`, `MainMenu`, `PauseMenu`.
3. `Game::Run()` chạy vòng lặp:
   - `ProcessEvents()` xử lý input và menu.
   - `Update(deltaTime)` cập nhật trạng thái và logic.
   - `Render()` vẽ scene.
4. `Game` quản lý các trạng thái: `MainMenu`, `Playing`, `GameOver`, `Victory`.

## Các thành phần chính

- `Game`: điều phối vòng lặp, trạng thái, menu, render.
- `Player`: di chuyển, bắn, buff, tính điểm.
- `AlienManager`: tạo và quản lý quái theo vòng.
- `Bullet`: quản lý đạn player và quái.
- `BuffManager`: quản lý item buff rơi.
- `CollisionManager`: xử lý va chạm giữa bullet, alien, player và buff.
- `ResourceManager`: load và cung cấp texture/font.
- `SoundManager`: load và phát âm thanh.
- `UI`: hiển thị điểm, lives, buff.
- `MainMenu`, `PauseMenu`, `GameOverMenu`, `ScoreHistoryMenu`: giao diện tương tác.

## Tài liệu UML

Các sơ đồ UML được cập nhật theo source code hiện tại và nằm trong thư mục `UML/`:

- [UML/class_diagram.md](UML/class_diagram.md): sơ đồ lớp chính và quan hệ giữa các class.
- [UML/sequence_diagrams.md](UML/sequence_diagrams.md): sơ đồ trình tự cho game loop và tương tác menu.
- [UML/summary.md](UML/summary.md): tóm tắt nhanh các thành phần chính.
- [UML/uml_diagrams.md](UML/uml_diagrams.md): bản đầy đủ gồm cả class diagram và sequence diagram.

## Chi tiết game flow

- Khi ở `MainMenu`, người chơi có thể bắt đầu game hoặc xem lịch sử điểm.
- khi ở phần `ShipSelectionMenu`, người chơi có thể chọn thuyền tùy sở thích
- Khi đang chơi, người chơi có thể bắn, di chuyển, nhặt buff và pause.
- Khi mất hết mạng, chuyển sang `GameOver` và có thể restart.
- Khi tiêu diệt hết vòng cuối cùng, chuyển sang `Victory`.
- Điểm cao và lịch sử trận được lưu vào `docs/highscore.txt` và `docs/history.txt`.

## Build & Run

Dự án dùng compiler g++ với SFML3. Sử dụng task trong VS Code hoặc lệnh sau:

```bash
g++ -std=c++17 src/*.cpp -I include -o build/main.exe -I C:/msys64/ucrt64/include -L C:/msys64/ucrt64/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```

Khởi chạy game:

```bash
build/main.exe
```

## Controls

- `Left` / `A`: di chuyển trái
- `Right` / `D`: di chuyển phải
- `Up` / `W`: di chuyển lên
- `Down` / `S`: di chuyển xuống
- `Space`: bắn
- `Left click`: bắn hoặc chọn button
- `Enter`: bắt đầu hoặc restart

## TÀI LIỆU THAM KHẢO

1. **Source code ý tưởng tham khảo:**     
https://github.com/attreyabhatt/Space-Invaders-Pygame

2. **Cảm hứng Gameplay:**     
https://www.youtube.com/shorts/u2e5RYYej_4

3. **Github mã nguồn của nhóm:**     
https://github.com/dnvinh2402/oop

## Nếu bạn cần chạy file mà không cần biên dịch(phòng trường hợp không thể), bạn có thể giải nén thư mục release
Khởi chạy game:

```bash
release/SpaceInvaders.exe
```