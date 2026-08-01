#pragma once

#include <SFML/Audio.hpp>
#include <map>
#include <string>

class SoundManager
{
private:
    std::map<std::string, sf::SoundBuffer> buffers;
    std::map<std::string, sf::Sound> sounds;

    sf::Music backgroundMusic;

public:
    SoundManager();

    bool LoadSound(const std::string& name,
                   const std::string& filename);

    bool LoadMusic(const std::string& filename);

    void Play(const std::string& name);

    void PlayMusic();

    void StopMusic();

    void UpdateVolume();
};