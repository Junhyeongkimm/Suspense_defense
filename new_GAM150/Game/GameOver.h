#pragma once
#include "../Engine/GameState.h"
#include "../Engine/Texture.h"
#include "SFML/Audio.hpp"
// Need to be updated
class GameOver : public CS230::GameState {
public:
    GameOver();
    void Load() override;
    void Update([[maybe_unused]] double dt) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override { return "GameOver"; }

private:
    double counter = 0;
    CS230::Texture* texture;
};
