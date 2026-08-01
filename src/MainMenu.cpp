#include "MainMenu.hpp"
#include "GlobalAudio.hpp"
#include <cstdio>
#include <iostream>

MainMenu::MainMenu(sf::Font *f, sf::Texture *bgTexture, int highScore)
    : font(f), titleText(*font, "SPACE DEFENDER", 52), introText(*font, "", 22), playButton(*font, "BAT DAU CHOI", 34), historyButton(*font, "LICH SU DAU", 28)
{

    bgSprite = new sf::Sprite(*bgTexture);
    sf::Vector2u texSize = bgTexture->getSize();
    // Phủ kín khung màn hình 900x900, không bị lỗi góc đen bên dưới
    bgSprite->setScale(sf::Vector2f(900.0f / (float)texSize.x, 900.0f / (float)texSize.y));
    bgSprite->setPosition(sf::Vector2f(0.0f, 0.0f));

    // Tiêu đề game (Đã kéo xuống giữa màn hình)
    titleText.setFillColor(sf::Color::Yellow);
    sf::FloatRect bounds = titleText.getLocalBounds();
    titleText.setOrigin(sf::Vector2f(bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f));
    titleText.setPosition(sf::Vector2f(450.0f, 380.0f)); // Sửa tọa độ Y từ 180 thành 380

    // Giới thiệu (Đã kéo xuống theo tiêu đề)
    introText.setFillColor(sf::Color(210, 210, 210));
    introText.setString("Tua game chien dau khong gian - Tieu diet quai vat bao ve trai dat!");
    bounds = introText.getLocalBounds();
    introText.setOrigin(sf::Vector2f(bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f));
    introText.setPosition(sf::Vector2f(450.0f, 450.0f)); // Sửa tọa độ Y từ 260 thành 450

    // Nút Bắt đầu
    playButton.setFillColor(sf::Color::Green);
    bounds = playButton.getLocalBounds();
    playButton.setOrigin(sf::Vector2f(bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f));
    playButton.setPosition(sf::Vector2f(450.0f, 580.0f));

    // Nút Lịch sử đấu
    historyButton.setFillColor(sf::Color::Cyan);
    bounds = historyButton.getLocalBounds();
    historyButton.setOrigin(sf::Vector2f(bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f));
    historyButton.setPosition(sf::Vector2f(450.0f, 660.0f));

    // --- TẢI HÌNH ẢNH CHO CÁC NÚT ÂM LƯỢNG ---
    isMuted = GlobalAudio::isMuted;
    currentVolume = (int)GlobalAudio::volume;

    unmuteTexture = new sf::Texture();
    muteTexture = new sf::Texture();
    plusTexture = new sf::Texture();
    minusTexture = new sf::Texture();

    if (!unmuteTexture->loadFromFile("assets/images/volume_on.png"))
    {
        std::cout << "Khong the load volume_on.png!\n";
    }
    if (!muteTexture->loadFromFile("assets/images/volume_mute.png"))
    {
        std::cout << "Khong the load volume_mute.png!\n";
    }
    if (!plusTexture->loadFromFile("assets/images/plus.png"))
    {
        std::cout << "Khong the load plus.png!\n";
    }
    if (!minusTexture->loadFromFile("assets/images/minus.png"))
    {
        std::cout << "Khong the load minus.png!\n";
    }

    muteButtonSprite = new sf::Sprite(*unmuteTexture);
    volumeDownSprite = new sf::Sprite(*minusTexture);
    volumeUpSprite = new sf::Sprite(*plusTexture);

    auto scaleSprite = [](sf::Sprite *sprite, sf::Texture *tex, float targetSize)
    {
        sf::Vector2u size = tex->getSize();
        if (size.x > 0 && size.y > 0)
        {
            sprite->setScale(sf::Vector2f(targetSize / size.x, targetSize / size.y));
        }
    };

    scaleSprite(muteButtonSprite, unmuteTexture, 40.0f);
    scaleSprite(volumeDownSprite, minusTexture, 35.0f);
    scaleSprite(volumeUpSprite, plusTexture, 35.0f);

    volumeDownSprite->setPosition(sf::Vector2f(380.0f, 800.0f));
    muteButtonSprite->setPosition(sf::Vector2f(440.0f, 795.0f));
    volumeUpSprite->setPosition(sf::Vector2f(500.0f, 800.0f));
}

MainMenu::~MainMenu()
{
    delete bgSprite;
    delete muteButtonSprite;
    delete volumeDownSprite;
    delete volumeUpSprite;
    delete unmuteTexture;
    delete muteTexture;
    delete plusTexture;
    delete minusTexture;
}

void MainMenu::Update(sf::Vector2f mousePos)
{
    if (playButton.getGlobalBounds().contains(mousePos))
    {
        playButton.setScale(sf::Vector2f(1.15f, 1.15f));
        playButton.setFillColor(sf::Color::Yellow);
    }
    else
    {
        playButton.setScale(sf::Vector2f(1.0f, 1.0f));
        playButton.setFillColor(sf::Color::Green);
    }

    if (historyButton.getGlobalBounds().contains(mousePos))
    {
        historyButton.setScale(sf::Vector2f(1.15f, 1.15f));
        historyButton.setFillColor(sf::Color::Yellow);
    }
    else
    {
        historyButton.setScale(sf::Vector2f(1.0f, 1.0f));
        historyButton.setFillColor(sf::Color::Cyan);
    }

    if (muteButtonSprite->getGlobalBounds().contains(mousePos))
    {
        muteButtonSprite->setColor(sf::Color(200, 200, 200));
    }
    else
    {
        muteButtonSprite->setColor(sf::Color::White);
    }

    if (isMuted)
    {
        volumeDownSprite->setColor(sf::Color(100, 100, 100, 150));
        volumeUpSprite->setColor(sf::Color(100, 100, 100, 150));
    }
    else
    {
        if (volumeDownSprite->getGlobalBounds().contains(mousePos))
        {
            volumeDownSprite->setColor(sf::Color(200, 200, 200));
        }
        else
        {
            volumeDownSprite->setColor(sf::Color::White);
        }

        if (volumeUpSprite->getGlobalBounds().contains(mousePos))
        {
            volumeUpSprite->setColor(sf::Color(200, 200, 200));
        }
        else
        {
            volumeUpSprite->setColor(sf::Color::White);
        }
    }
}

int MainMenu::HandleClick(sf::Vector2f mousePos)
{
    if (playButton.getGlobalBounds().contains(mousePos))
    {
        return 1;
    }
    if (historyButton.getGlobalBounds().contains(mousePos))
    {
        return 2;
    }

    if (muteButtonSprite->getGlobalBounds().contains(mousePos))
    {
        isMuted = !isMuted;
        GlobalAudio::isMuted = isMuted;
        if (isMuted)
        {
            muteButtonSprite->setTexture(*muteTexture, true);
        }
        else
        {
            muteButtonSprite->setTexture(*unmuteTexture, true);
        }

        // Reset scale cho chắc chắn vùng click không hụt
        sf::Texture *currentTex = isMuted ? muteTexture : unmuteTexture;
        sf::Vector2u size = currentTex->getSize();
        if (size.x > 0)
            muteButtonSprite->setScale(sf::Vector2f(40.0f / size.x, 40.0f / size.y));

        return 3;
    }

    if (!isMuted)
    {
        if (volumeDownSprite->getGlobalBounds().contains(mousePos))
        {
            if (currentVolume > 0)
                currentVolume -= 10;
            GlobalAudio::volume = currentVolume;
            printf("Volume: %d%%\n", currentVolume);
            return 4;
        }

        if (volumeUpSprite->getGlobalBounds().contains(mousePos))
        {
            if (currentVolume < 100)
                currentVolume += 10;
            GlobalAudio::volume = currentVolume;
            printf("Volume: %d%%\n", currentVolume);
            return 5;
        }
    }

    return 0;
}

void MainMenu::Render(sf::RenderWindow &window)
{
    window.draw(*bgSprite);
    window.draw(titleText);
    window.draw(introText);
    window.draw(playButton);
    window.draw(historyButton);

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
        volumeDownSprite->setColor(sf::Color(100, 100, 100, 150));
        volumeUpSprite->setColor(sf::Color(100, 100, 100, 150));
    }
    else
    {
        muteButtonSprite->setTexture(*unmuteTexture, true);
        volumeDownSprite->setColor(sf::Color::White);
        volumeUpSprite->setColor(sf::Color::White);
    }

    sf::Texture *currentTex = isMuted ? muteTexture : unmuteTexture;
    sf::Vector2u size = currentTex->getSize();
    if (size.x > 0 && size.y > 0)
    {
        muteButtonSprite->setScale(sf::Vector2f(40.0f / size.x, 40.0f / size.y));
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