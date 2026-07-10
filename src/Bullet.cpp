#include "Bullet.hpp"

Bullet::Bullet(sf::Texture* texture, sf::Vector2f startPos, sf::Vector2f vel, bool isPlayer)
    : GameObject(texture) {
    position = startPos;
    sprite.setPosition(position);

    velocity = vel;
    isPlayerBullet = isPlayer;
}

Bullet::~Bullet() {
    // Chưa cần dọn gì đặc biệt
}

void Bullet::Update(float deltaTime) {
    // Di chuyển đạn theo vận tốc
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
    sprite.setPosition(position);

    // Nếu đạn bay ra khỏi màn hình (trên hoặc dưới), đánh dấu để xoá
    if (position.y < 0.0f || position.y > 600.0f) {
        Destroy();
    }
}

void Bullet::Render(sf::RenderWindow& window) {
    window.draw(sprite);
}