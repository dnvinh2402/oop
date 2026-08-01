#include "MainMenu.hpp"
#include <cstdio>
#include <cmath> // Dùng cho hàm toán học nếu cần, hoặc dùng hiệu ứng lướt mượt

MainMenu::MainMenu(sf::Font* f, sf::Texture* bgTexture, int highScore) 
    : font(f), titleText(*font), introText(*font), playButton(*font), highScoreText(*font) {
    
    bgSprite = new sf::Sprite(*bgTexture);
    
    sf::Vector2u texSize = bgTexture->getSize();
    bgSprite->setScale(sf::Vector2f(900.0f / texSize.x, 900.0f / texSize.y));

    // Thiết lập chữ tiêu đề
    titleText.setCharacterSize(52);
    titleText.setFillColor(sf::Color::Yellow);
    titleText.setString("SPACE DEFENDER");
    sf::FloatRect bounds = titleText.getLocalBounds();
    titleText.setOrigin(sf::Vector2f(bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f));
    titleText.setPosition(sf::Vector2f(450.0f, 200.0f));

    // Giới thiệu game
    introText.setCharacterSize(22);
    introText.setFillColor(sf::Color(210, 210, 210));
    introText.setString("Tua game chien dau khong gian - Tieu diet quai vat bao ve trai dat!");
    bounds = introText.getLocalBounds();
    introText.setOrigin(sf::Vector2f(bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f));
    introText.setPosition(sf::Vector2f(450.0f, 300.0f));

    // Nút Bắt đầu chơi (Cố định size gốc, dùng scale để phóng to thu nhỏ chuẩn tâm)
    playButton.setCharacterSize(34);
    playButton.setFillColor(sf::Color::Green);
    playButton.setString("BAT DAU CHOI");
    bounds = playButton.getLocalBounds();
    playButton.setOrigin(sf::Vector2f(bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f));
    playButton.setPosition(sf::Vector2f(450.0f, 440.0f));

    // Hiển thị điểm cao nhất
    highScoreText.setCharacterSize(28);
    highScoreText.setFillColor(sf::Color::Cyan);
    char buf[50];
    snprintf(buf, sizeof(buf), "DIEM CAO NHAT: %d", highScore);
    highScoreText.setString(buf);
    bounds = highScoreText.getLocalBounds();
    highScoreText.setOrigin(sf::Vector2f(bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f));
    highScoreText.setPosition(sf::Vector2f(450.0f, 530.0f));
}

MainMenu::~MainMenu() {
    delete bgSprite;
}

// Hiệu ứng di chuột: Dùng setScale thay vì thay đổi characterSize để giữ nguyên tâm căn giữa tuyệt đối
void MainMenu::Update(sf::Vector2f mousePos) {
    if (playButton.getGlobalBounds().contains(mousePos)) {
        playButton.setScale(sf::Vector2f(1.2f, 1.2f)); // Phóng to đều 20% từ tâm ra
        playButton.setFillColor(sf::Color::Yellow);
    } else {
        playButton.setScale(sf::Vector2f(1.0f, 1.0f)); // Trở về kích thước chuẩn
        playButton.setFillColor(sf::Color::Green);
    }

    if (highScoreText.getGlobalBounds().contains(mousePos)) {
        highScoreText.setScale(sf::Vector2f(1.15f, 1.15f)); // Phóng to nhẹ từ tâm
    } else {
        highScoreText.setScale(sf::Vector2f(1.0f, 1.0f));
    }
}

int MainMenu::HandleClick(sf::Vector2f mousePos) {
    if (playButton.getGlobalBounds().contains(mousePos)) {
        return 1; 
    }
    if (highScoreText.getGlobalBounds().contains(mousePos)) {
        return 2; 
    }
    return 0;
}

void MainMenu::Render(sf::RenderWindow& window) {
    window.draw(*bgSprite);
    window.draw(titleText);
    window.draw(introText);
    window.draw(playButton);
    window.draw(highScoreText);
}