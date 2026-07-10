#include "Alien.hpp"

Alien::Alien(sf::Texture* texture, sf::Vector2f startPos, int points) : GameObject(texture) {
    position = startPos;
    sprite.setPosition(position);
    pointValue = points;
}

Alien::~Alien() {
    // Chưa cần dọn gì đặc biệt
}

void Alien::Update(float deltaTime) {
    // Alien không tự di chuyển một mình mỗi frame.
    // Việc di chuyển (ngang + xuống) do AlienManager điều khiển đồng loạt
    // cho cả đàn, thông qua MoveHorizontal() và MoveDown() gọi từ bên ngoài.
}

void Alien::Render(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Alien::MoveDown(float distance) {
    position.y += distance;
    sprite.setPosition(position);
}

void Alien::MoveHorizontal(float distance) {
    position.x += distance;
    sprite.setPosition(position);
}