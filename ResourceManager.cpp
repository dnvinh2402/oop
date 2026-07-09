#include "ResourceManager.hpp"
#include <iostream>

ResourceManager::ResourceManager() {
    // Chưa cần làm gì lúc khởi tạo
}

ResourceManager::~ResourceManager() {
    // Duyệt qua toàn bộ map, giải phóng từng con trỏ texture
    for (auto& pair : textures) {
        delete pair.second;
    }
    textures.clear();

    // Tương tự cho font
    for (auto& pair : fonts) {
        delete pair.second;
    }
    fonts.clear();
}

void ResourceManager::LoadTexture(std::string name, std::string filename) {
    sf::Texture* texture = new sf::Texture();

    if (!texture->loadFromFile(filename)) {
        std::cerr << "Loi: khong the load texture: " << filename << std::endl;
        delete texture;
        return;
    }

    textures[name] = texture;
}

sf::Texture* ResourceManager::GetTexture(std::string name) {
    auto it = textures.find(name);
    if (it != textures.end()) {
        return it->second;
    }

    std::cerr << "Canh bao: khong tim thay texture ten: " << name << std::endl;
    return nullptr;
}

void ResourceManager::LoadFont(std::string name, std::string filename) {
    sf::Font* font = new sf::Font();

    if (!font->openFromFile(filename)) {
        std::cerr << "Loi: khong the load font: " << filename << std::endl;
        delete font;
        return;
    }

    fonts[name] = font;
}

sf::Font* ResourceManager::GetFont(std::string name) {
    auto it = fonts.find(name);
    if (it != fonts.end()) {
        return it->second;
    }

    std::cerr << "Canh bao: khong tim thay font ten: " << name << std::endl;
    return nullptr;
}