#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class ResourceManager {
private:
    // Dùng std::map để lưu con trỏ ảnh/font kèm theo tên gọi (ví dụ: "player_tex")
    std::map<std::string, sf::Texture*> textures;
    std::map<std::string, sf::Font*> fonts;

public:
    ResourceManager();
    ~ResourceManager(); // Chú ý: Hàm này sẽ phải chứa vòng lặp delete toàn bộ con trỏ trong map

    void LoadTexture(std::string name, std::string filename);
    sf::Texture* GetTexture(std::string name);

    void LoadFont(std::string name, std::string filename);
    sf::Font* GetFont(std::string name);
};