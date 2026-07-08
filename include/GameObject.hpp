#pragma once
#include <SFML/Graphics.hpp>

class GameObject {
protected:
    sf::Vector2f position;
    sf::Sprite sprite;
    bool isActive;

public:
    // Bắt buộc truyền sf::Texture* vào để khởi tạo sf::Sprite
    GameObject(sf::Texture* texture) : sprite(*texture) {
        isActive = true;
    }
    
    virtual ~GameObject() {}

    // Hàm thuần ảo
    virtual void Update(float deltaTime) = 0;
    virtual void Render(sf::RenderWindow& window) = 0;

    bool IsActive() { return isActive; }
    void Destroy() { isActive = false; }
    sf::FloatRect GetBounds() { return sprite.getGlobalBounds(); }
};