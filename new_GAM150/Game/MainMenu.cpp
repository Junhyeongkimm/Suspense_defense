#include "../Engine/Engine.h"
#include "State.h"
#include "MainMenu.h"
#include "doodle/drawing.hpp"
#include "doodle/input.hpp"

using namespace doodle;
// Need to be updated

MainMenu::MainMenu()
{ }

void MainMenu::Load() {

}

void MainMenu::Draw() {
    Engine::GetWindow().Clear(UINT_MAX);

    draw_ellipse(Engine::GetWindow().GetSize().x / 2, Engine::GetWindow().GetSize().y / 2, 100);
    
}

void MainMenu::Update([[maybe_unused]] double dt) {

    if (Key == KeyboardButtons::Enter) {
        if (counter == 0)
        {
            Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Game));
        }
    }
    if (Key == KeyboardButtons::Escape) {
        if (counter == 0)
        {
            Engine::GetGameStateManager().ClearNextGameState();
        }
    }

}

void MainMenu::Unload() {

}
