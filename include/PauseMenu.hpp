#pragma once
#include <SFML/Graphics.hpp>

class PauseMenu {
private:
    sf::Font* font;

    // Các biến hình khối (giao diện gốc của bạn)
    sf::RectangleShape pauseButtonRect;
    sf::RectangleShape backgroundOverlay;
    sf::RectangleShape menuBox;
    sf::RectangleShape decreaseVolButton;
    sf::RectangleShape muteButton;
    sf::RectangleShape increaseVolButton;

    // Các biến văn bản (giao diện gốc của bạn)
    sf::Text pauseButtonText;
    sf::Text titleText;
    sf::Text resumeButton;
    sf::Text mainMenuButton;
    sf::Text volumeText;
    sf::Text muteButtonText;
    sf::Text decreaseText;
    sf::Text increaseText;

    float volume;
    bool isMuted;

public:
    PauseMenu(sf::Font* f);
    ~PauseMenu(); // Đã xóa = default để khớp với file .cpp của bạn

    bool IsPauseButtonClicked(sf::Vector2f mousePos) const;
    void Update(sf::Vector2f mousePos);
    int HandleClick(sf::Vector2f mousePos);
    void Render(sf::RenderWindow& window, bool isPausedState);

    // Chỉ để lại khai báo, bỏ phần ngoặc nhọn {} đi
    bool IsMuted() const;
    float GetVolume() const;
    void SetVolume(float vol, bool muted);
};