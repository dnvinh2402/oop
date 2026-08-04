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
    shieldHitsRemaining = 2; // Khởi tạo mặc định chịu được 2 lần trúng đạn

    bombReady = false;
    bombTimer = 0.f;
    bombCount = 0;
}

Player::~Player()
{
    // Chưa cần dọn gì đặc biệt
}

void Player::HandleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        position.x -= speed * 0.016f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        position.x += speed * 0.016f;
    }
}

void Player::Update(float deltaTime)
{
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

    if (position.x < 0.f)
    {
        position.x = 0.f;
    }
    else if (position.x > 900.f - bounds.size.x) 
    {
        position.x = 900.f - bounds.size.x;
    }

    float maxY = 900.f - bounds.size.y; 
    float minY = 450.f; 

    if (position.y < minY)
    {
        position.y = minY;
    }
    else if (position.y > maxY)
    {
        position.y = maxY;
    }
    
    sprite.setPosition(position);

    if (currentCooldown > 0.0f)
    {
        currentCooldown -= deltaTime;
    }

    if (doubleShot)
    {
        doubleShotTimer -= deltaTime;

        if (doubleShotTimer <= 0.0f)
        {
            doubleShot = false;
            fireCooldown = 0.3f;
        }
    }

    // Cập nhật khiên bảo vệ theo thời gian (10 giây)
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
        sf::Sprite shieldSpriteInstance(*shieldTexture);

        sf::FloatRect playerBounds = sprite.getGlobalBounds();
        sf::FloatRect shieldBounds = shieldSpriteInstance.getGlobalBounds();

        shieldSpriteInstance.setOrigin({
            shieldBounds.size.x / 2.f,
            shieldBounds.size.y / 2.f
        });

        shieldSpriteInstance.setPosition({
            position.x + playerBounds.size.x / 2.f,
            position.y + playerBounds.size.y / 2.f
        });

        float scale = 2.f;

        shieldSpriteInstance.setScale({
            scale,
            scale
        });

        window.draw(shieldSpriteInstance);
    }
}

void Player::Shoot(std::vector<Bullet *> &bulletList, sf::Texture *bulletTexture)
{
    if (currentCooldown <= 0.0f)
    {
        sf::FloatRect playerBounds = sprite.getGlobalBounds();
        sf::Vector2u bulletSize = bulletTexture->getSize();

        sf::Vector2f bulletStartPos;

        bulletStartPos.x = position.x + playerBounds.size.x / 2.f - bulletSize.x / 2.f;
        bulletStartPos.y = position.y - bulletSize.y;

        sf::Vector2f bulletVelocity(0.0f, -500.0f);

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

        currentCooldown = fireCooldown;
    }
}

void Player::TakeDamage()
{
    // Nếu đang có khiên, gọi hàm TakeShieldHit thay vì trừ trực tiếp mạng
    if (shield)
    {
        TakeShieldHit();
        return;
    }

    lives--;

    if (lives <= 0)
    {
        Destroy();
    }
}

// Xử lý khi bị đạn địch trúng lúc đang bật khiên (tối đa 2 viên)
void Player::TakeShieldHit()
{
    if (shield)
    {
        shieldHitsRemaining--;
        if (shieldHitsRemaining <= 0)
        {
            shield = false; // Mất khiên sau khi trúng đủ 2 viên đạn
        }
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
    shieldTimer = 10.0f;         // Tồn tại tối đa 10 giây nếu không bị bắn
    shieldHitsRemaining = 2;   // Cho phép chịu tối đa 2 viên đạn địch
}

bool Player::HasShield() const
{
    return shield;
}

void Player::ActivateBomb()
{
    bombCount++;

    if (!bombReady)
    {
        bombReady = true;
        bombTimer = 1.f;
    }
}

bool Player::IsBombReady() const
{
    return bombReady && bombTimer <= 0.f;
}

void Player::ResetBomb()
{
    bombCount--;

    if (bombCount > 0)
    {
        bombTimer = 1.f;
    }
    else
    {
        bombReady = false;
        bombTimer = 0.f;
    }
}

void Player::SetShieldTexture(sf::Texture* texture)
{
    shieldTexture = texture;
}