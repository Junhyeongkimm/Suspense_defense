#pragma once
#include <filesystem>
#include <map>
#include <string>
#include "SFML/Audio.hpp"

namespace sf {
    class SoundBuffer;
    class Sound;
}

namespace CS230 {


    class SoundManager {
    public:
        void Load(const std::string path);
        void Unload();

    private:
        std::map<std::string, sf::SoundBuffer*> sounds;
        sf::Sound sound1;
        sf::Sound sound2;
    };
}