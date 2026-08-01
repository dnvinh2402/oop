#include "SoundManager.hpp"
#include "GlobalAudio.hpp"

#include <iostream>

SoundManager::SoundManager()
{
}

bool SoundManager::LoadSound(const std::string& name,
                             const std::string& filename)
{
    sf::SoundBuffer buffer;

    if (!buffer.loadFromFile(filename))
    {
        std::cout << "Khong load duoc sound: "
                  << filename << std::endl;
        return false;
    }

    buffers[name] = std::move(buffer);

    sounds.emplace(name, sf::Sound(buffers[name]));

    return true;
}

bool SoundManager::LoadMusic(const std::string& filename)
{
    if (!backgroundMusic.openFromFile(filename))
    {
        std::cout << "Khong load duoc music\n";
        return false;
    }

    backgroundMusic.setLooping(true);

    UpdateVolume();

    return true;
}

void SoundManager::Play(const std::string& name)
{
    auto it = sounds.find(name);

    if (it == sounds.end())
        return;

    UpdateVolume();

    it->second.play();
}

void SoundManager::PlayMusic()
{
    UpdateVolume();

    backgroundMusic.play();
}

void SoundManager::StopMusic()
{
    backgroundMusic.stop();
}

void SoundManager::UpdateVolume()
{
    float volume =
        GlobalAudio::isMuted ?
        0.f :
        GlobalAudio::volume;

    backgroundMusic.setVolume(volume);

    for (auto& sound : sounds)
    {
        sound.second.setVolume(volume);
    }
}