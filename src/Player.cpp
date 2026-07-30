#include "Player.hpp"
#include <cmath>

Player::Player(sf::Texture *texture, sf::Vector2f startPos) : GameObject(texture)
{
    position = startPos;
    sprite.setPosition(position);
    shieldTexture = nullptr;

    speed = 300.0f;
    lives = 3;
    score = 0;
    fireCooldown = 0.3f;
    currentCooldown = 0.0f;
    doubleShot = false;
    shield = false;

    doubleShotTimer = 0.0f;
    shieldTimer = 0.0f;

    bombReady = false;
    bombTimer = 0.f;
}

Player::~Player()
{
    // Chưa cần dọn gì đặc biệt
}

void Player::HandleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        position.x -= speed * 0.016f; // tạm ước lượng, sẽ thay bằng deltaTime thật ở Update
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        position.x += speed * 0.016f;
    }
}

void Player::Update(float deltaTime)
{
    // Di chuyển trái/phải
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        position.x -= speed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        position.x += speed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        position.y -= speed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        position.y += speed * deltaTime;
    }
    
    sf::FloatRect bounds = sprite.getGlobalBounds();

    // Giới hạn trục X (Sử dụng bounds.size.x thay vì bounds.width)
    if (position.x < 0.f)
    {
        position.x = 0.f;
    }
    else if (position.x > 900.f - bounds.size.x) 
    {
        position.x = 900.f - bounds.size.x;
    }

    // Giới hạn trục Y (Đổi 600 thành 900)
    float maxY = 900.f - bounds.size.y; 
    
    // Vì màn hình rộng hơn, bạn có thể đẩy giới hạn bay cao nhất (minY) xuống một chút (ví dụ 450) 
    // để phi thuyền không bay lên quá sát bầy quái vật.
    float minY = 450.f; 

    if (position.y < minY)
    {
        position.y = minY;
    }
    else if (position.y > maxY)
    {
        position.y = maxY;
    }
    // 4. Áp dụng tọa độ mới
    sprite.setPosition(position);

    // Đếm ngược thời gian hồi chiêu bắn đạn
    if (currentCooldown > 0.0f)
    {
        currentCooldown -= deltaTime;
    }
    // =========================
    // Rapid Fire
    // =========================
    if (doubleShot)
    {
        doubleShotTimer -= deltaTime;

        if (doubleShotTimer <= 0.0f)
        {
            doubleShot = false;
            fireCooldown = 0.3f;
        }
    }

    // =========================
    // Shield
    // =========================
    if (shield)
    {
        shieldTimer -= deltaTime;

        if (shieldTimer <= 0.0f)
        {
            shield = false;
        }
    }
    if (bombReady && bombTimer > 0.f)
    {
        bombTimer -= deltaTime;
    }
}

void Player::Render(sf::RenderWindow& window)
{
    window.draw(sprite);

    if (shield && shieldTexture != nullptr)
    {
        sf::Sprite shield(*shieldTexture);

        sf::FloatRect playerBounds = sprite.getGlobalBounds();
        sf::FloatRect shieldBounds = shield.getGlobalBounds();

        shield.setOrigin({
            shieldBounds.size.x / 2.f,
            shieldBounds.size.y / 2.f
        });

        shield.setPosition({
            position.x + playerBounds.size.x / 2.f,
            position.y + playerBounds.size.y / 2.f
        });

        float scale = 2.f;

        shield.setScale({
            scale,
            scale
        });

        window.draw(shield);
    }
}
void Player::Shoot(std::vector<Bullet *> &bulletList, sf::Texture *bulletTexture)
{
    // TODO: hoàn thiện sau khi có class Bullet
    // Ý tưởng: nếu currentCooldown <= 0, tạo Bullet mới tại vị trí Player,
    // push_back vào bulletList, rồi reset currentCooldown = fireCooldown
    if (currentCooldown <= 0.0f)
    {
        sf::FloatRect playerBounds = sprite.getGlobalBounds();
        sf::Vector2u bulletSize = bulletTexture->getSize();

        sf::Vector2f bulletStartPos;

        bulletStartPos.x = position.x + playerBounds.size.x / 2.f - bulletSize.x / 2.f;

        bulletStartPos.y = position.y - bulletSize.y;

        sf::Vector2f bulletVelocity(0.0f, -500.0f); // bay thẳng lên, tốc độ 500px/s

        if (doubleShot)
        {
            sf::Vector2f leftPos = bulletStartPos;
            sf::Vector2f rightPos = bulletStartPos;

            leftPos.x -= 12.f;
            rightPos.x += 12.f;

            bulletList.push_back(
                new Bullet(bulletTexture, leftPos, bulletVelocity, true));

            bulletList.push_back(
                new Bullet(bulletTexture, rightPos, bulletVelocity, true));
        }
        else
        {
            bulletList.push_back(
                new Bullet(bulletTexture, bulletStartPos, bulletVelocity, true));
        }

        currentCooldown = fireCooldown; // reset thời gian hồi chiêu
    }
}

void Player::TakeDamage()
{
    if (shield)
        return;

    lives--;

    if (lives <= 0)
    {
        Destroy();
    }
}
void Player::ActivateDoubleShot()
{
    doubleShot = true;
    doubleShotTimer = 10.0f;

    fireCooldown = 0.15f;
}

void Player::ActivateShield()
{
    shield = true;
    shieldTimer = 10.0f;
}

bool Player::HasShield() const
{
    return shield;
}
void Player::ActivateBomb()
{
    bombReady = true;
    bombTimer = 1.f;
}
bool Player::IsBombReady() const
{
    return bombReady && bombTimer <= 0.f;
}
void Player::ResetBomb()
{
    bombReady = false;
}
void Player::SetShieldTexture(sf::Texture* texture)
{
    shieldTexture = texture;
}