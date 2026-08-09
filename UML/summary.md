# UML Summary

## Tổng quan thành phần

- `Game`: điều phối vòng lặp, trạng thái, input, update, render.
- `Player`: điều khiển người chơi, movement, shoot, buff.
- `AlienManager`: tạo và quản lý các Alien theo round.
- `CollisionManager`: xử lý va chạm giữa bullet, alien, player và buff.
- `ResourceManager`: load và cung cấp texture/font.
- `SoundManager`: load và phát audio.
- `UI`: hiển thị score, lives, buff timer, game over/victory.
- `MainMenu`, `PauseMenu`, `GameOverMenu`, `ScoreHistoryMenu`: quản lý giao diện tương tác.

## Đặc điểm dễ đọc

- Mỗi file trong `UML/` chứa nội dung nhỏ, tập trung:
  - `class_diagram.md`: sơ đồ lớp và quan hệ.
  - `sequence_diagrams.md`: sơ đồ trình tự game loop và menu.
  - `summary.md`: tóm tắt các thành phần chính.

## File gốc

- `UML/uml_diagrams.md`: chứa cả class diagram và sequence diagram đầy đủ.

Những file này giúp bạn tham khảo nhanh mà không cần mở toàn bộ tài liệu UML lớn.