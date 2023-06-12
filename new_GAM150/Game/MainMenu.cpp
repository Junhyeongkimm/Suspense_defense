#include "../Engine/Engine.h"
#include "State.h"
#include "MainMenu.h"
#include "doodle/drawing.hpp"
#include "doodle/input.hpp"

using namespace doodle;
// Need to be updated

MainMenu::MainMenu():texture(texture), playbutton(playbutton), howtoplaybutton(howtoplaybutton), creditbutton(creditbutton)
{ }

void MainMenu::Load() {
    texture = Engine::GetTextureManager().Load("Assets/maintitle.png");
    playbutton = Engine::GetTextureManager().Load("Assets/playbutton.png");
    howtoplaybutton = Engine::GetTextureManager().Load("Assets/howtoplaybutton.png");
    creditbutton = Engine::GetTextureManager().Load("Assets/creditbutton.png");
}

void MainMenu::Draw() {
    Engine::GetWindow().Clear(UINT_MAX);
    texture->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - texture->GetSize()) / 2.0 }));
    playbutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - playbutton->GetSize().x) / 10}, {(Engine::GetWindow().GetSize().y - playbutton->GetSize().y) -380})));
    howtoplaybutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - howtoplaybutton->GetSize().x) / 10 }, { (Engine::GetWindow().GetSize().y - howtoplaybutton->GetSize().y) -500})));
    creditbutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - creditbutton->GetSize().x) / 10 }, { (Engine::GetWindow().GetSize().y - creditbutton->GetSize().y) -620 })));
 
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
