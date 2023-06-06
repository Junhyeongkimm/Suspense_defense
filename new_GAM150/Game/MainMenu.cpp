#include "../Engine/Engine.h"
#include "State.h"
#include "MainMenu.h"
#include "doodle/drawing.hpp"
#include "doodle/input.hpp"

using namespace doodle;
// Need to be updated

MainMenu::MainMenu():texture(texture)
{ }

void MainMenu::Load() {
    texture = Engine::GetTextureManager().Load("Assets/maintitle.png");
}

void MainMenu::Draw() {
    Engine::GetWindow().Clear(UINT_MAX);
    texture->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - texture->GetSize()) / 2.0 }));
 
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
