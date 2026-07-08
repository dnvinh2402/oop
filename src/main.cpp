#include "Game.hpp"

int main() {
    // Bước 1: Tạo ra một đối tượng game (cỗ máy)
    // Lúc này, Constructor của Game sẽ chạy và tự động mở cửa sổ 800x600
    Game myGame;

    // Bước 2: Kích hoạt vòng lặp vô tận của game
    myGame.Run();

    // Bước 3: Khi người chơi bấm dấu X, vòng lặp Run() kết thúc, chương trình nhảy xuống đây và thoát.
    // Lúc này, Destructor ~Game() sẽ tự động chạy để dọn dẹp RAM.
    return 0;
}