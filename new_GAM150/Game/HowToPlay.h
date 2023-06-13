#pragma once
#include "../Engine/GameState.h"
#include "../Engine/Texture.h"
#include "SFML/Audio.hpp"
// Need to be updated
class HowToPlay : public CS230::GameState {
public:
    HowToPlay();
    void Load() override;
    void Update([[maybe_unused]] double dt) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override { return "HowToPlay"; }

private:
    double counter = 0;
    CS230::Texture* howtoplay;
    sf::Music* music;
};
