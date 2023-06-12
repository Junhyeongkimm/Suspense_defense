#pragma once
#include "../Engine/GameState.h"
#include "../Engine/Texture.h"
// Need to be updated
class MainMenu : public CS230::GameState {
public:
    MainMenu();
    void Load() override;
    void Update([[maybe_unused]] double dt) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override { return "MainMenu"; }

private:
    double counter = 0;
    CS230::Texture* texture;
    CS230::Texture* playbutton;
    CS230::Texture* howtoplaybutton;
    CS230::Texture* creditbutton;
};
