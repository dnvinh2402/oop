#include "ResourceManager.hpp"
#include <iostream>

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
    for (auto &pair : textures)
    {
        delete pair.second;
    }
    textures.clear();

    for (auto &pair : fonts)
    {
        delete pair.second;
    }
    fonts.clear();
}

void ResourceManager::LoadTexture(std::string name, std::string filename)
{
    sf::Texture *texture = new sf::Texture();

    if (!texture->loadFromFile(filename))
    {
        std::cerr << "Loi: khong the load texture: " << filename << std::endl;
        delete texture;
        return;
    }

    auto it = textures.find(name);
    if (it != textures.end())
    {
        delete it->second;
    }

    textures[name] = texture;
}

sf::Texture *ResourceManager::GetTexture(std::string name)
{
    auto it = textures.find(name);

    if (it != textures.end() && it->second != nullptr)
    {
        return it->second;
    }

    std::cerr << "Canh bao: khong tim thay texture hop le: "
              << name << std::endl;

    return nullptr;
}

void ResourceManager::LoadFont(std::string name, std::string filename)
{
    sf::Font *font = new sf::Font();

    if (!font->openFromFile(filename))
    {
        std::cerr << "Loi: khong the load font: " << filename << std::endl;
        delete font;
        return;
    }

    auto it = fonts.find(name);
    if (it != fonts.end())
    {
        delete it->second;
    }

    fonts[name] = font;
}

sf::Font *ResourceManager::GetFont(std::string name)
{
    auto it = fonts.find(name);
    if (it != fonts.end())
    {
        return it->second;
    }

    std::cerr << "Canh bao: khong tim thay font ten: " << name << std::endl;
    return nullptr;
}