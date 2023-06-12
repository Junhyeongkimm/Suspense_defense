#pragma once
#include <filesystem>
#include <map>
#include <string>

namespace sf {
    class Music;
}

namespace CS230 {


    class MusicManager {
    public:
        sf::Music* Load(const std::string path);
        void Unload();

    private:
        std::map<std::string, sf::Music*> sounds;
    };
}