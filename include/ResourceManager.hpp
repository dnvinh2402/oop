#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <memory>

class ResourceManager {
private:
    // Dùng std::map để lưu con trỏ ảnh/font kèm theo tên gọi (ví dụ: "player_tex")
    std::map<std::string, std::unique_ptr<sf::Texture>> textures;
    std::map<std::string, std::unique_ptr<sf::Font>> fonts;

public:
    ResourceManager();
    ~ResourceManager(); // Chú ý: Hàm này sẽ phải chứa vòng lặp delete toàn bộ con trỏ trong map

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    void LoadTexture(std::string name, std::string filename);
    sf::Texture* GetTexture(std::string name);

    void LoadFont(std::string name, std::string filename);
    sf::Font* GetFont(std::string name);
};