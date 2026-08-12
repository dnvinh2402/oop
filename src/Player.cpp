#include "Player.hpp"
#include <cmath>
Player::Player(sf::Texture *texture, sf::Vector2f startPos,
               int healthLevel,
               int fireRateLevel,
               int speedLevel) : GameObject(texture),
                                 healthLevel(healthLevel),
                                 fireRateLevel(fireRateLevel),
                                 speedLevel(speedLevel)
{
    position = startPos;
    sprite.setPosition(position);

    speed = 320.0f;
    if (speedLevel >= 12)
    {
        speed = 360.f;
    }
    else if (speedLevel <= 8)
    {
        speed = 280.f;
    }
    lives = 3;
    score = 0;
    fireCooldown = 0.5f;
    if (fireRateLevel >= 12)
    {
        fireCooldown = 0.3f;
    }
    else if (fireRateLevel <= 8)
    {
        fireCooldown = 0.7f;
    }
    currentCooldown = 0.0f;
    doubleShot = false;
    shield = false;

    doubleShotTimer = 0.0f;
    shieldTimer = 0.0f;
    shieldHitsRemaining = 2;

    invincible = false;
    invincibleTimer = 0.0f;
    blinkTimer = 0.0f;
    blinkVisible = true;

    bombReady = false;
    bombTimer = 0.f;
    bombCount = 0;
}

Player::~Player()
{
}

void Player::HandleInput(float deltaTime)
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
}

void Player::Update(float deltaTime)
{
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
            if (fireRateLevel >= 12)
            {
                fireCooldown = 0.3f;
            }
            else if (fireRateLevel <= 8)
            {
                fireCooldown = 0.7f;
            }
            else
            {
                fireCooldown = 0.5f;
            }
        }
    }

    // Cập nhật khiên bảo vệ theo thời gian
    if (shield)
    {
        shieldTimer -= deltaTime;

        if (shieldTimer <= 0.0f)
        {
            shield = false;
        }
    }

    if (invincible)
    {
        invincibleTimer -= deltaTime;
        blinkTimer -= deltaTime;

        if (blinkTimer <= 0.0f)
        {
            blinkTimer = 0.1f;
            blinkVisible = !blinkVisible;
        }

        if (invincibleTimer <= 0.0f)
        {
            invincible = false;
            blinkVisible = true;
        }
    }

    if (bombReady && bombTimer > 0.f)
    {
        bombTimer -= deltaTime;
    }
}

void Player::Render(sf::RenderWindow &window)
{
    if (invincible)
    {
        if (blinkVisible)
        {
            window.draw(sprite);
        }
    }
    else
    {
        window.draw(sprite);
    }
}

bool Player::Shoot(std::vector<Bullet *> &bulletList, sf::Texture *bulletTexture)
{
    if (currentCooldown > 0.0f)
        return false;
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
    return true;
}

void Player::TakeDamage()
{
    if (invincible)
    {
        return;
    }

    if (shield)
    {
        TakeShieldHit();
        return;
    }

    lives--;

    if (lives <= 0)
    {
        Destroy();
        return;
    }

    StartInvincibility(3.0f);
}

bool Player::IsInvincible() const
{
    return invincible;
}

void Player::StartInvincibility(float duration)
{
    invincible = true;
    invincibleTimer = duration;
    blinkTimer = 0.1f;
    blinkVisible = false;
}

// Xử lý khi bị đạn địch trúng lúc đang bật khiên (chịu tối đa 2 viên)
void Player::TakeShieldHit()
{
    if (shield)
    {
        shieldHitsRemaining--;
        if (shieldHitsRemaining <= 0)
        {
            shield = false;
        }
    }
}

void Player::ActivateDoubleShot()
{
    doubleShot = true;
    doubleShotTimer = 10.0f;
    fireCooldown = 0.3f;
}

void Player::ActivateShield()
{
    shield = true;
    shieldTimer = 10.0f;
    shieldHitsRemaining = 2;
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
