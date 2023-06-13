#pragma once
#include "../Engine/GameState.h"
#include "../Engine/Texture.h"
#include "SFML/Audio.hpp"
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
    unsigned int menu = 0;
    double counter = 0;
    CS230::Texture* texture;
    CS230::Texture* playbutton;
    CS230::Texture* howtoplaybutton;
    CS230::Texture* creditbutton;
    CS230::Texture* exitbutton;
    CS230::Texture* selectplaybutton;
    CS230::Texture* selecthowtoplaybutton;
    CS230::Texture* selectcreditbutton;
    CS230::Texture* selectexitbutton;
    CS230::Texture* loading;
    sf::Music* music;
};
