#include "../Engine/Engine.h"
#include "State.h"
#include "Credit.h"
#include "doodle/drawing.hpp"
#include "doodle/input.hpp"

using namespace doodle;
// Need to be updated

Credit::Credit() :texture(texture), playbutton(playbutton), howtoplaybutton(howtoplaybutton), creditbutton(creditbutton), music(nullptr)
{ }

void Credit::Load() {
    music = Engine::GetMusicManager().Load("Assets/Music/MainMenu.wav");
    texture = Engine::GetTextureManager().Load("Assets/maintitle.png");
    playbutton = Engine::GetTextureManager().Load("Assets/playbutton.png");
    howtoplaybutton = Engine::GetTextureManager().Load("Assets/howtoplaybutton.png");
    creditbutton = Engine::GetTextureManager().Load("Assets/creditbutton.png");
    music->play();
    music->setLoop(true);
}

void Credit::Draw() {
    Engine::GetWindow().Clear(UINT_MAX);
    texture->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - texture->GetSize()) / 2.0 }));
    playbutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - playbutton->GetSize().x) / 10 }, { (Engine::GetWindow().GetSize().y - playbutton->GetSize().y) - 380 })));
    howtoplaybutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - howtoplaybutton->GetSize().x) / 10 }, { (Engine::GetWindow().GetSize().y - howtoplaybutton->GetSize().y) - 500 })));
    creditbutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - creditbutton->GetSize().x) / 10 }, { (Engine::GetWindow().GetSize().y - creditbutton->GetSize().y) - 620 })));

}

void Credit::Update([[maybe_unused]] double dt) {

    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::W)) {
        menu = (menu + 2) % 3;
    }
    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::S)) {
        menu = (menu + 1) % 3;
    }


    if (Key == KeyboardButtons::Enter) {
        if (counter == 0) {
            switch (menu) {
            case 0:
                Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Game));
                break;
            case 1:
                Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::HowToPlay));
                break;
            case 2:
                Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Credit));
                break;
            }
            menu = 0;
        }
    }
    if (Key == KeyboardButtons::Escape) {
        if (counter == 0) {
            Engine::GetGameStateManager().ClearNextGameState();
        }
    }

}

void Credit::Unload() {
    music->stop();
}
