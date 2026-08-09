#include "ResourceManager.hpp"
#include <iostream>
#include <memory>

ResourceManager::ResourceManager()
{
    // Chưa cần làm gì lúc khởi tạo
}

ResourceManager::~ResourceManager() = default;

void ResourceManager::LoadTexture(std::string name, std::string filename)
{
    auto texture = std::make_unique<sf::Texture>();

    if (!texture->loadFromFile(filename))
    {
        std::cerr << "Loi: khong the load texture: " << filename << std::endl;
        return;
    }

    textures[name] = std::move(texture);
}

sf::Texture *ResourceManager::GetTexture(std::string name)
{
    auto it = textures.find(name);

    if (it != textures.end() && it->second != nullptr)
    {
        return it->second.get();
    }

    std::cerr << "Canh bao: khong tim thay texture hop le: "
              << name << std::endl;

    return nullptr;
}

void ResourceManager::LoadFont(std::string name, std::string filename)
{
    auto font = std::make_unique<sf::Font>();

    if (!font->openFromFile(filename))
    {
        std::cerr << "Loi: khong the load font: " << filename << std::endl;
        return;
    }

    fonts[name] = std::move(font);
}

sf::Font *ResourceManager::GetFont(std::string name)
{
    auto it = fonts.find(name);
    if (it != fonts.end())
    {
        return it->second.get();
    }

    std::cerr << "Canh bao: khong tim thay font ten: " << name << std::endl;
    return nullptr;
}