
#pragma once
#include "../Engine/GameState.h"
#include "../Engine/Texture.h"
// Splash
class Splash1 : public CS230::GameState {
public:
    Splash1();
    void Load() override;
    void Update([[maybe_unused]] double dt) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override { return "Splash1"; }

public:
    double counter = 0;
    CS230::Texture* texture1;
};
