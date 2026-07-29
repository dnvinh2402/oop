#include "Player.hpp"
#include <cmath>

Player::Player(sf::Texture *texture, sf::Vector2f startPos) : GameObject(texture)
{
    position = startPos;
    sprite.setPosition(position);

    speed = 300.0f;
    lives = 3;
    score = 0;
    fireCooldown = 0.3f;
    currentCooldown = 0.0f;
    rapidFire = false;
    shield = false;

    rapidFireTimer = 0.0f;
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
    // // Giới hạn trong màn hình
    // if (position.x < 0.0f)
    //     position.x = 0.0f;
    // if (position.x > 750.0f)
    //     position.x = 750.0f;

    if (position.x < 0.f)
    {
        position.x = 0.f;
    }
    else if (position.x > 800.f)
    {
        position.x = 800.f;
    }

    // Giới hạn trục Y (Giữ phi thuyền ở nửa dưới màn hình để không bay xuyên bầy quái)
    float maxY = 600.f; // Đáy màn hình
    float minY = 350.f; // Giới hạn bay cao nhất (bạn có thể tinh chỉnh số 350 này)

    if (position.y < minY)
    {
        position.y = minY;
    }
    else if (position.y > maxY)
    {
        position.y = maxY;
    }
    sprite.setPosition(position);

    // Đếm ngược thời gian hồi chiêu bắn đạn
    if (currentCooldown > 0.0f)
    {
        currentCooldown -= deltaTime;
    }
    // =========================
    // Rapid Fire
    // =========================
    if (rapidFire)
    {
        rapidFireTimer -= deltaTime;

        if (rapidFireTimer <= 0.0f)
        {
            rapidFire = false;
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
    if (bombReady)
    {
        bombTimer -= deltaTime;
    }
}

void Player::Render(sf::RenderWindow &window)
{
    window.draw(sprite);
}

void Player::Shoot(std::vector<Bullet *> &bulletList, sf::Texture *bulletTexture)
{
    // TODO: hoàn thiện sau khi có class Bullet
    // Ý tưởng: nếu currentCooldown <= 0, tạo Bullet mới tại vị trí Player,
    // push_back vào bulletList, rồi reset currentCooldown = fireCooldown
    if (currentCooldown <= 0.0f)
    {
        sf::Vector2f bulletStartPos = position;
        bulletStartPos.y -= 20.0f; // đặt đạn xuất hiện phía trên đầu Player một chút

        sf::Vector2f bulletVelocity(0.0f, -500.0f); // bay thẳng lên, tốc độ 500px/s

        if (rapidFire)
        {
            sf::Vector2f leftPos = bulletStartPos;
            sf::Vector2f rightPos = bulletStartPos;

            leftPos.x -= 10.f;
            rightPos.x += 10.f;

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
void Player::ActivateRapidFire()
{
    rapidFire = true;
    rapidFireTimer = 10.0f;

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