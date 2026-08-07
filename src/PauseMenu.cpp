#include "PauseMenu.hpp"
#include "GlobalAudio.hpp"
#include <cstdio>
#include <iostream>

PauseMenu::PauseMenu(sf::Font *f)
    : font(f),
      volume(100.0f),
      isMuted(false),
      volumeText(*font, "", 20) 
{
    // 1. LÀM MỜ GAME
    backgroundOverlay.setSize(sf::Vector2f(900.0f, 900.0f));
    backgroundOverlay.setFillColor(sf::Color(0, 0, 0, 160));

    // 2. KHỞI TẠO TẤT CẢ TEXTURE
    menuBgTexture = new sf::Texture();
    pauseTexture = new sf::Texture();
    resumeTexture = new sf::Texture();
    homeTexture = new sf::Texture();
    unmuteTexture = new sf::Texture();
    muteTexture = new sf::Texture();
    minusTexture = new sf::Texture();
    plusTexture = new sf::Texture();

    if (!menuBgTexture->loadFromFile("assets/images/menu_frame.png")) std::cout << "Loi load menu_frame.png\n";
    if (!pauseTexture->loadFromFile("assets/images/pausemenu.png")) std::cout << "Loi load pausemenu.png\n";
    if (!resumeTexture->loadFromFile("assets/images/resume.png")) std::cout << "Loi load resume.png\n";
    if (!homeTexture->loadFromFile("assets/images/home.png")) std::cout << "Loi load home.png\n";
    if (!unmuteTexture->loadFromFile("assets/images/volume_on.png")) std::cout << "Loi load volume_on.png\n";
    if (!muteTexture->loadFromFile("assets/images/volume_mute.png")) std::cout << "Loi load volume_mute.png\n";
    if (!minusTexture->loadFromFile("assets/images/minus.png")) std::cout << "Loi load minus.png\n";
    if (!plusTexture->loadFromFile("assets/images/plus.png")) std::cout << "Loi load plus.png\n";

    menuBgSprite = new sf::Sprite(*menuBgTexture);
    pauseSprite = new sf::Sprite(*pauseTexture);
    resumeSprite = new sf::Sprite(*resumeTexture);
    homeSprite = new sf::Sprite(*homeTexture);
    muteSprite = new sf::Sprite(*unmuteTexture);
    minusSprite = new sf::Sprite(*minusTexture);
    plusSprite = new sf::Sprite(*plusTexture);

    // 3. THIẾT LẬP KHUNG NỀN (Ngang 600, Cao 750)
    sf::Vector2u bgSize = menuBgTexture->getSize();
    if (bgSize.x > 0 && bgSize.y > 0) {
        menuBgSprite->setScale(sf::Vector2f(600.0f / bgSize.x, 750.0f / bgSize.y));
    }
    sf::FloatRect bgBounds = menuBgSprite->getLocalBounds();
    menuBgSprite->setOrigin(sf::Vector2f(bgBounds.position.x + bgBounds.size.x / 2.0f, bgBounds.position.y + bgBounds.size.y / 2.0f));
    menuBgSprite->setPosition(sf::Vector2f(450.0f, 450.0f)); 

    // Hàm Helper
    auto setupSprite = [](sf::Sprite* sprite, sf::Texture* tex, float targetSize, sf::Vector2f pos) {
        sf::Vector2u size = tex->getSize();
        if (size.x > 0 && size.y > 0) {
            sprite->setScale(sf::Vector2f(targetSize / size.x, targetSize / size.y));
        }
        sf::FloatRect bounds = sprite->getLocalBounds();
        sprite->setOrigin(sf::Vector2f(bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f));
        sprite->setPosition(pos);
    };

    // Nút Pause ở góc phải
    setupSprite(pauseSprite, pauseTexture, 40.0f, sf::Vector2f(850.0f, 40.0f));
    
    // 4. SẮP XẾP BỐ CỤC (ĐÃ KÉO XUỐNG 10 PIXEL CHO TẤT CẢ)
    
    // Nút Resume (Kéo xuống Y = 330)
    setupSprite(resumeSprite, resumeTexture, 70.0f, sf::Vector2f(450.0f, 330.0f));
    
    // Nút Home (Kéo xuống Y = 420)
    setupSprite(homeSprite, homeTexture, 70.0f, sf::Vector2f(450.0f, 420.0f));

    // Chữ % Âm lượng
    volumeText.setFillColor(sf::Color(80, 80, 80)); 

    // Cụm nút Âm lượng (Kéo xuống Y = 570)
    setupSprite(minusSprite, minusTexture, 45.0f, sf::Vector2f(360.0f, 570.0f));
    setupSprite(muteSprite, unmuteTexture, 45.0f, sf::Vector2f(450.0f, 570.0f));
    setupSprite(plusSprite, plusTexture, 45.0f, sf::Vector2f(540.0f, 570.0f));
}

PauseMenu::~PauseMenu() {
    delete menuBgSprite; delete menuBgTexture;
    delete pauseSprite;  delete pauseTexture;
    delete resumeSprite; delete resumeTexture;
    delete homeSprite;   delete homeTexture;
    delete muteSprite;   delete muteTexture; delete unmuteTexture;
    delete minusSprite;  delete minusTexture;
    delete plusSprite;   delete plusTexture;
}

bool PauseMenu::IsPauseButtonClicked(sf::Vector2f mousePos) const {
    return pauseSprite->getGlobalBounds().contains(mousePos);
}

void PauseMenu::Update(sf::Vector2f mousePos) {
    auto hoverEffect = [&](sf::Sprite* spr) {
        if (spr->getGlobalBounds().contains(mousePos)) {
            spr->setColor(sf::Color(255, 255, 255, 120)); 
        } else {
            spr->setColor(sf::Color(255, 255, 255, 255)); 
        }
    };

    hoverEffect(pauseSprite); 
    hoverEffect(resumeSprite);
    hoverEffect(homeSprite);
    
    if (!isMuted) {
        hoverEffect(minusSprite);
        hoverEffect(plusSprite);
    } else {
        minusSprite->setColor(sf::Color(255, 255, 255, 40)); 
        plusSprite->setColor(sf::Color(255, 255, 255, 40));  
    }
    hoverEffect(muteSprite);
}

int PauseMenu::HandleClick(sf::Vector2f mousePos) {
    if (IsPauseButtonClicked(mousePos)) return 3;
    if (resumeSprite->getGlobalBounds().contains(mousePos)) return 1;
    if (homeSprite->getGlobalBounds().contains(mousePos)) return 2;

    if (muteSprite->getGlobalBounds().contains(mousePos)) {
        isMuted = !isMuted;
        GlobalAudio::isMuted = isMuted;
        GlobalAudio::volume = volume;
        SetVolume(volume, isMuted);
    }
    else if (!isMuted) {
        if (minusSprite->getGlobalBounds().contains(mousePos)) {
            volume -= 10.0f;
            if (volume < 0.0f) volume = 0.0f;
            GlobalAudio::volume = volume;
        }
        else if (plusSprite->getGlobalBounds().contains(mousePos)) {
            volume += 10.0f;
            if (volume > 100.0f) volume = 100.0f;
            GlobalAudio::volume = volume;
        }
    }
    return 0;
}

void PauseMenu::Render(sf::RenderWindow &window, bool isPaused) {
    window.draw(*pauseSprite); 

    if (isPaused) {
        window.draw(backgroundOverlay);
        window.draw(*menuBgSprite);
        
        window.draw(*resumeSprite);
        window.draw(*homeSprite);

        char buf[32];
        if (isMuted) {
            std::snprintf(buf, sizeof(buf), "MUTED");
        } else {
            std::snprintf(buf, sizeof(buf), "%.0f%%", volume);
        }
        volumeText.setString(buf);
        
        // Chữ Volume được đặt chen giữa nút Home và dàn nút Âm lượng (Kéo xuống Y = 500)
        sf::FloatRect tBounds = volumeText.getLocalBounds();
        volumeText.setOrigin(sf::Vector2f(tBounds.position.x + tBounds.size.x / 2.0f, tBounds.position.y + tBounds.size.y / 2.0f));
        volumeText.setPosition(sf::Vector2f(450.0f, 500.0f)); 
        
        window.draw(volumeText);
        window.draw(*minusSprite);
        window.draw(*muteSprite);
        window.draw(*plusSprite);
    }
}

void PauseMenu::SetVolume(float vol, bool mute) {
    volume = vol;
    isMuted = mute;

    if (isMuted) {
        muteSprite->setTexture(*muteTexture, true);
    } else {
        muteSprite->setTexture(*unmuteTexture, true);
    }
}

float PauseMenu::GetVolume() const {
    return volume;
}

bool PauseMenu::IsMuted() const {
    return isMuted;
}