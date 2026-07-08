// #include "Game.hpp"
// #include <optional>

// // 1. Constructor (Hàm khởi tạo)
// // Chú ý: Ta dùng Initializer List để khởi tạo cửa sổ ngay khi Game được tạo ra
// Game::Game() : window(sf::VideoMode({800, 600}), "My first game") {
//     // Khởi tạo các con trỏ bằng nullptr để an toàn (sẽ cấp phát bằng new sau)
//     player = nullptr;
// }

// // 2. Destructor (Hàm hủy)
// Game::~Game() {
//     // Dọn dẹp bộ nhớ khi tắt game
//     if (player != nullptr) {
//         delete player;
//     }
    
//     for (int i = 0; i < bullets.size(); i++) {
//         delete bullets[i];
//     }
//     bullets.clear();
// }

// // 3. Hàm xử lý sự kiện (Tách từ vòng lặp trong main cũ)
// void Game::ProcessEvents() {
//     std::optional<sf::Event> event;
//     while (event = window.pollEvent()) {
//         if (event->is<sf::Event::Closed>()) {
//             window.close();
//         }
//     }
// }

// // 4. Hàm cập nhật logic game (Di chuyển, va chạm...)
// void Game::Update(float deltaTime) {
//     // Tạm thời chưa có logic gì, sau này hàm update của player, đạn, quái sẽ nằm ở đây
// }

// // 5. Hàm vẽ đồ họa (Tách từ phần clear và display trong main cũ)
// void Game::Render() {
//     window.clear(sf::Color(127, 127, 127));
    
//     // Sau này các lệnh vẽ player->Render(window) sẽ đặt ở đây
    
//     window.display();
// }

// // 6. TRÁI TIM CỦA GAME: Vòng lặp chính
// void Game::Run() {
//     // sf::Clock dùng để tính deltaTime (chưa dùng tới trong bài test này nhưng chuẩn bị sẵn)
//     sf::Clock clock;

//     // Đây chính là vòng lặp game loop quen thuộc của bạn
//     while (window.isOpen()) {
//         float deltaTime = clock.restart().asSeconds();

//         ProcessEvents();
//         Update(deltaTime);
//         Render();
//     }
// }


#include "Game.hpp"
#include <optional> // Bắt buộc phải có cho SFML 3 Event

// Khởi tạo cửa sổ y hệt code cũ của bạn
Game::Game() : window(sf::VideoMode({800, 600}), "My first game") {
    // Hiện tại chưa cấp phát con trỏ nào nên để trống
}

Game::~Game() {
    // Trống (chưa có con trỏ nào để delete)
}

void Game::ProcessEvents() {
    std::optional<sf::Event> event;
    while (event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
    }
}

void Game::Update(float deltaTime) {
    // Tạm thời để trống, sau này tàu và quái sẽ di chuyển ở đây
}

void Game::Render() {
    // Bôi màu nền xám giống hệt file main cũ của bạn
    window.clear(sf::Color(127, 127, 127));
    
    window.display();
}

void Game::Run() {
    sf::Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        
        ProcessEvents();
        Update(deltaTime);
        Render();
    }
}