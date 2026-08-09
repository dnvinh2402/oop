#include "MainMenu.hpp"
#include "GlobalAudio.hpp"
#include <cstdio>
#include <iostream>

MainMenu::MainMenu(sf::Font *f, sf::Texture *bgTexture, int highScore)
    : font(f)
{
    // 1. HÌNH NỀN
    bgSprite = std::make_unique<sf::Sprite>(*bgTexture);
    sf::Vector2u texSize = bgTexture->getSize();
    bgSprite->setScale(sf::Vector2f(900.0f / (float)texSize.x, 900.0f / (float)texSize.y));
    bgSprite->setPosition(sf::Vector2f(0.0f, 0.0f));

    // 2. TẢI VÀ TỰ ĐỘNG XÓA NỀN TRẮNG + SỌC CARO CHO LOGO
    logoTexture = std::make_unique<sf::Texture>();
    sf::Image logoImage;
    if (logoImage.loadFromFile("assets/images/logo.png"))
    {
        sf::Vector2u size = logoImage.getSize();
        for (unsigned int y = 0; y < size.y; ++y)
        {
            for (unsigned int x = 0; x < size.x; ++x)
            {
                sf::Color col = logoImage.getPixel(sf::Vector2u(x, y));
                if (col.r > 210 && col.g > 210 && col.b > 205)
                {
                    logoImage.setPixel(sf::Vector2u(x, y), sf::Color(255, 255, 255, 0));
                }
            }
        }
        if (!logoTexture->loadFromImage(logoImage))
        {
            std::cout << "Loi load texture tu logoImage\n";
        }
    }
    else
    {
        std::cout << "Loi load logo.png\n";
    }

    playTexture = std::make_unique<sf::Texture>();
    historyTexture = std::make_unique<sf::Texture>();
    unmuteTexture = std::make_unique<sf::Texture>();
    muteTexture = std::make_unique<sf::Texture>();
    plusTexture = std::make_unique<sf::Texture>();
    minusTexture = std::make_unique<sf::Texture>();

    if (!playTexture->loadFromFile("assets/images/play.png"))
        std::cout << "Loi load play.png\n";
    if (!historyTexture->loadFromFile("assets/images/highscores.png"))
        std::cout << "Loi load highscores.png\n";
    if (!unmuteTexture->loadFromFile("assets/images/volume_on.png"))
        std::cout << "Loi load volume_on.png\n";
    if (!muteTexture->loadFromFile("assets/images/volume_mute.png"))
        std::cout << "Loi load volume_mute.png\n";
    if (!plusTexture->loadFromFile("assets/images/plus.png"))
        std::cout << "Loi load plus.png\n";
    if (!minusTexture->loadFromFile("assets/images/minus.png"))
        std::cout << "Loi load minus.png\n";

    logoSprite = std::make_unique<sf::Sprite>(*logoTexture);
    playSprite = std::make_unique<sf::Sprite>(*playTexture);
    historySprite = std::make_unique<sf::Sprite>(*historyTexture);
    muteButtonSprite = std::make_unique<sf::Sprite>(*unmuteTexture);
    volumeDownSprite = std::make_unique<sf::Sprite>(*minusTexture);
    volumeUpSprite = std::make_unique<sf::Sprite>(*plusTexture);

    // 3. HÀM HELPER: CHỈNH KÍCH THƯỚC VÀ CĂN GIỮA TỰ ĐỘNG
    auto setupSprite = [](sf::Sprite *sprite, sf::Texture *tex, float targetSize, sf::Vector2f pos)
    {
        sf::Vector2u size = tex->getSize();
        if (size.x > 0 && size.y > 0)
        {
            sprite->setScale(sf::Vector2f(targetSize / size.x, targetSize / size.y));
        }
        sf::FloatRect b = sprite->getLocalBounds();
        sprite->setOrigin(sf::Vector2f(b.position.x + b.size.x / 2.0f, b.position.y + b.size.y / 2.0f));
        sprite->setPosition(pos);
    };

    // Kích thước logo
    sf::Vector2u logoSize = logoTexture->getSize();
    if (logoSize.x > 0)
    {
        float logoTargetWidth = 400.0f;
        float scale = logoTargetWidth / logoSize.x;
        logoSprite->setScale(sf::Vector2f(scale, scale));
    }
    sf::FloatRect logoBounds = logoSprite->getLocalBounds();
    logoSprite->setOrigin(sf::Vector2f(logoBounds.position.x + logoBounds.size.x / 2.0f, logoBounds.position.y + logoBounds.size.y / 2.0f));
    logoSprite->setPosition(sf::Vector2f(450.0f, 250.0f));

    // Đặt vị trí các nút chính
    setupSprite(playSprite.get(), playTexture.get(), 150.0f, sf::Vector2f(450.0f, 440.0f));
    float scaleX = 200.0f / playTexture->getSize().x;
    float scaleY = 200.0f / playTexture->getSize().y;
    float scale = std::min(scaleX, scaleY);

    playSprite->setScale(sf::Vector2f(scale, scale));
    setupSprite(historySprite.get(), historyTexture.get(), 70.0f, sf::Vector2f(450.0f, 540.0f));

    // Đặt vị trí hàng nút âm thanh (Đã đẩy xuống 15 pixel: Y = 645.0f)
    setupSprite(volumeDownSprite.get(), minusTexture.get(), 45.0f, sf::Vector2f(360.0f, 645.0f));
    setupSprite(muteButtonSprite.get(), unmuteTexture.get(), 45.0f, sf::Vector2f(450.0f, 645.0f));
    setupSprite(volumeUpSprite.get(), plusTexture.get(), 45.0f, sf::Vector2f(540.0f, 645.0f));

    isMuted = GlobalAudio::isMuted;
    currentVolume = (int)GlobalAudio::volume;
    SetVolume(currentVolume, isMuted);
}

 

void MainMenu::Update(sf::Vector2f mousePos)
{
    auto hoverEffect = [&](sf::Sprite *spr)
    {
        if (spr->getGlobalBounds().contains(mousePos))
        {
            spr->setColor(sf::Color(255, 255, 255, 120));
        }
        else
        {
            spr->setColor(sf::Color(255, 255, 255, 255));
        }
    };

    hoverEffect(playSprite.get());
    hoverEffect(historySprite.get());
    hoverEffect(muteButtonSprite.get());

    if (isMuted)
    {
        volumeDownSprite->setColor(sf::Color(255, 255, 255, 40));
        volumeUpSprite->setColor(sf::Color(255, 255, 255, 40));
    }
    else
    {
        hoverEffect(volumeDownSprite.get());
        hoverEffect(volumeUpSprite.get());
    }
}

int MainMenu::HandleClick(sf::Vector2f mousePos)
{
    if (playSprite->getGlobalBounds().contains(mousePos))
        return 1;
    if (historySprite->getGlobalBounds().contains(mousePos))
        return 2;

    if (muteButtonSprite->getGlobalBounds().contains(mousePos))
    {
        isMuted = !isMuted;
        GlobalAudio::isMuted = isMuted;
        SetVolume(currentVolume, isMuted);
        return 3;
    }

    if (!isMuted)
    {
        if (volumeDownSprite->getGlobalBounds().contains(mousePos))
        {
            if (currentVolume > 0)
                currentVolume -= 10;
            GlobalAudio::volume = currentVolume;
            return 4;
        }

        if (volumeUpSprite->getGlobalBounds().contains(mousePos))
        {
            if (currentVolume < 100)
                currentVolume += 10;
            GlobalAudio::volume = currentVolume;
            return 5;
        }
    }
    return 0;
}

void MainMenu::Render(sf::RenderWindow &window)
{
    window.draw(*bgSprite);
    window.draw(*logoSprite);
    window.draw(*playSprite);
    window.draw(*historySprite);
    window.draw(*muteButtonSprite);
    window.draw(*volumeDownSprite);
    window.draw(*volumeUpSprite);
}

void MainMenu::SetVolume(int vol, bool mute)
{
    currentVolume = vol;
    isMuted = mute;
    GlobalAudio::volume = currentVolume;
    GlobalAudio::isMuted = isMuted;

    if (isMuted)
    {
        muteButtonSprite->setTexture(*muteTexture, true);
    }
    else
    {
        muteButtonSprite->setTexture(*unmuteTexture, true);
    }
}

int MainMenu::GetVolume() const
{
    return currentVolume;
}

bool MainMenu::IsMuted() const
{
    return isMuted;
}