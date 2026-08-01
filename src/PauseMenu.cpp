#include "PauseMenu.hpp"
#include <cstdio>

PauseMenu::PauseMenu(sf::Font* f) 
    : font(f), 
      volume(100.0f), 
      isMuted(false),
      titleText(*font, "PAUSE MENU", 30), 
      resumeButton(*font, "Resume Game", 22), 
      mainMenuButton(*font, "Main Menu", 22), 
      volumeText(*font, "", 18), 
      muteButtonText(*font, "", 16),
      decreaseText(*font, "-", 20),
      increaseText(*font, "+", 20),
      pauseButtonText(*font, "||", 18) 
{
    pauseButtonRect.setSize(sf::Vector2f(50.0f, 35.0f));
    pauseButtonRect.setFillColor(sf::Color(50, 50, 50, 200));
    pauseButtonRect.setOutlineColor(sf::Color::White);
    pauseButtonRect.setOutlineThickness(1.5f);
    pauseButtonRect.setPosition(sf::Vector2f(840.0f, 10.0f));

    pauseButtonText.setFillColor(sf::Color::White);
    pauseButtonText.setPosition(sf::Vector2f(858.0f, 14.0f));

    backgroundOverlay.setSize(sf::Vector2f(900.0f, 900.0f));
    backgroundOverlay.setFillColor(sf::Color(0, 0, 0, 180));

    menuBox.setSize(sf::Vector2f(420.0f, 380.0f));
    menuBox.setFillColor(sf::Color(20, 20, 35, 240));
    menuBox.setOutlineColor(sf::Color::Cyan);
    menuBox.setOutlineThickness(2.0f);
    menuBox.setPosition(sf::Vector2f(240.0f, 260.0f));

    titleText.setFillColor(sf::Color::Yellow);
    titleText.setPosition(sf::Vector2f(355.0f, 285.0f));

    resumeButton.setFillColor(sf::Color::White);
    resumeButton.setPosition(sf::Vector2f(370.0f, 355.0f));

    mainMenuButton.setFillColor(sf::Color::White);
    mainMenuButton.setPosition(sf::Vector2f(385.0f, 405.0f));

    volumeText.setFillColor(sf::Color::Cyan);
    volumeText.setPosition(sf::Vector2f(350.0f, 460.0f));

    decreaseVolButton.setSize(sf::Vector2f(40.0f, 30.0f));
    decreaseVolButton.setFillColor(sf::Color(70, 70, 70));
    decreaseVolButton.setPosition(sf::Vector2f(330.0f, 500.0f));
    decreaseText.setFillColor(sf::Color::White);
    decreaseText.setPosition(sf::Vector2f(344.0f, 501.0f));

    muteButton.setSize(sf::Vector2f(90.0f, 30.0f));
    muteButton.setFillColor(sf::Color(70, 70, 70));
    muteButton.setPosition(sf::Vector2f(385.0f, 500.0f));
    muteButtonText.setString("Mute: OFF");
    muteButtonText.setFillColor(sf::Color::White);
    muteButtonText.setPosition(sf::Vector2f(393.0f, 505.0f));

    increaseVolButton.setSize(sf::Vector2f(40.0f, 30.0f));
    increaseVolButton.setFillColor(sf::Color(70, 70, 70));
    increaseVolButton.setPosition(sf::Vector2f(490.0f, 500.0f));
    increaseText.setFillColor(sf::Color::White);
    increaseText.setPosition(sf::Vector2f(502.0f, 501.0f));
}

PauseMenu::~PauseMenu() {}

bool PauseMenu::IsPauseButtonClicked(sf::Vector2f mousePos) const {
    return pauseButtonRect.getGlobalBounds().contains(mousePos);
}

void PauseMenu::Update(sf::Vector2f mousePos) {
    if (resumeButton.getGlobalBounds().contains(mousePos))
        resumeButton.setFillColor(sf::Color::Yellow);
    else
        resumeButton.setFillColor(sf::Color::White);

    if (mainMenuButton.getGlobalBounds().contains(mousePos))
        mainMenuButton.setFillColor(sf::Color::Yellow);
    else
        mainMenuButton.setFillColor(sf::Color::White);
}

int PauseMenu::HandleClick(sf::Vector2f mousePos) {
    if (IsPauseButtonClicked(mousePos)) {
        return 3; 
    }
    if (resumeButton.getGlobalBounds().contains(mousePos)) {
        return 1; 
    }
    if (mainMenuButton.getGlobalBounds().contains(mousePos)) {
        return 2; 
    }
    
    if (muteButton.getGlobalBounds().contains(mousePos)) {
        isMuted = !isMuted;
        if (isMuted) {
            muteButton.setFillColor(sf::Color::Red);
            muteButtonText.setString("Mute: ON");
        } else {
            muteButton.setFillColor(sf::Color(70, 70, 70));
            muteButtonText.setString("Mute: OFF");
        }
    }
    else if (decreaseVolButton.getGlobalBounds().contains(mousePos) && !isMuted) {
        volume -= 10.0f;
        if (volume < 0.0f) volume = 0.0f;
    }
    else if (increaseVolButton.getGlobalBounds().contains(mousePos) && !isMuted) {
        volume += 10.0f;
        if (volume > 100.0f) volume = 100.0f;
    }

    return 0;
}

void PauseMenu::Render(sf::RenderWindow& window, bool isPaused) {
    window.draw(pauseButtonRect);
    window.draw(pauseButtonText);

    if (isPaused) {
        window.draw(backgroundOverlay);
        window.draw(menuBox);
        window.draw(titleText);
        window.draw(resumeButton);
        window.draw(mainMenuButton);

        char buf[32];
        if (isMuted) {
            std::snprintf(buf, sizeof(buf), "Volume: MUTED");
        } else {
            std::snprintf(buf, sizeof(buf), "Volume: %.0f%%", volume);
        }
        volumeText.setString(buf);
        window.draw(volumeText);

        window.draw(decreaseVolButton);
        window.draw(decreaseText);
        window.draw(muteButton);
        window.draw(muteButtonText);
        window.draw(increaseVolButton);
        window.draw(increaseText);
    }
}

void PauseMenu::SetVolume(float vol, bool mute) {
    volume = vol;
    isMuted = mute;

    if (isMuted) {
        muteButton.setFillColor(sf::Color::Red);
        muteButtonText.setString("Mute: ON");
    } else {
        muteButton.setFillColor(sf::Color(70, 70, 70));
        muteButtonText.setString("Mute: OFF");
    }
}

float PauseMenu::GetVolume() const {
    return volume;
}

bool PauseMenu::IsMuted() const {
    return isMuted;
}