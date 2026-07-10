#include "Player.hpp"

Player::Player(sf::Texture* texture, sf::Vector2f startPos) : GameObject(texture) {
    position = startPos;
    sprite.setPosition(position);

    speed = 300.0f;
    lives = 3;
    score = 0;
    fireCooldown = 0.3f;
    currentCooldown = 0.0f;
}

Player::~Player() {
    // Chưa cần dọn gì đặc biệt
}

void Player::HandleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        position.x -= speed * 0.016f; // tạm ước lượng, sẽ thay bằng deltaTime thật ở Update
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        position.x += speed * 0.016f;
    }
}

void Player::Update(float deltaTime) {
    // Di chuyển trái/phải
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        position.x -= speed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        position.x += speed * deltaTime;
    }

    // Giới hạn trong màn hình
    if (position.x < 0.0f) position.x = 0.0f;
    if (position.x > 750.0f) position.x = 750.0f;

    sprite.setPosition(position);

    // Đếm ngược thời gian hồi chiêu bắn đạn
    if (currentCooldown > 0.0f) {
        currentCooldown -= deltaTime;
    }
}

void Player::Render(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Player::Shoot(std::vector<Bullet*>& bulletList, sf::Texture* bulletTexture) {
    // TODO: hoàn thiện sau khi có class Bullet
    // Ý tưởng: nếu currentCooldown <= 0, tạo Bullet mới tại vị trí Player,
    // push_back vào bulletList, rồi reset currentCooldown = fireCooldown
    if (currentCooldown <= 0.0f) {
        sf::Vector2f bulletStartPos = position;
        bulletStartPos.y -= 20.0f; // đặt đạn xuất hiện phía trên đầu Player một chút

        sf::Vector2f bulletVelocity(0.0f, -500.0f); // bay thẳng lên, tốc độ 500px/s

        Bullet* newBullet = new Bullet(bulletTexture, bulletStartPos, bulletVelocity, true);
        bulletList.push_back(newBullet);

        currentCooldown = fireCooldown; // reset thời gian hồi chiêu
    }
}

void Player::TakeDamage() {
    lives -= 1;
    if (lives <= 0) {
        Destroy(); // gọi hàm có sẵn từ GameObject, đặt isActive = false
    }
}