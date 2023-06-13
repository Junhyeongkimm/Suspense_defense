#pragma once
#include "../Engine/GameState.h"
#include "../Engine/Texture.h"
#include "SFML/Audio.hpp"
// Need to be updated
class Credit : public CS230::GameState {
public:
    Credit();
    void Load() override;
    void Update([[maybe_unused]] double dt) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override { return "Credit"; }

private:
    double counter = 0;
    int credit = 0;
    CS230::Texture* Credit1;
    CS230::Texture* Credit2;
    CS230::Texture* Credit3;
    CS230::Texture* Credit4;
    CS230::Texture* Credit5;
    CS230::Texture* Credit6;
    CS230::Texture* Credit7;
    sf::Music* music;
};
