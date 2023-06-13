#include "../Engine/Engine.h"
#include "State.h"
#include "MainMenu.h"
#include "doodle/drawing.hpp"
#include "doodle/input.hpp"

using namespace doodle;
// Need to be updated

MainMenu::MainMenu():texture(texture), playbutton(playbutton), howtoplaybutton(howtoplaybutton), creditbutton(creditbutton), music(nullptr)
{ }

void MainMenu::Load() {
    music = Engine::GetMusicManager().Load("Assets/Music/MainMenu.wav");
    texture = Engine::GetTextureManager().Load("Assets/maintitle.png");
    playbutton = Engine::GetTextureManager().Load("Assets/playbutton.png");
    howtoplaybutton = Engine::GetTextureManager().Load("Assets/howtoplaybutton.png");
    creditbutton = Engine::GetTextureManager().Load("Assets/creditbutton.png");
    exitbutton = Engine::GetTextureManager().Load("Assets/exit.png");

    selectplaybutton = Engine::GetTextureManager().Load("Assets/selectplaybutton.png");
    selecthowtoplaybutton = Engine::GetTextureManager().Load("Assets/selecthowtoplaybutton.png");
    selectcreditbutton = Engine::GetTextureManager().Load("Assets/selectcreditbutton.png");
    selectexitbutton = Engine::GetTextureManager().Load("Assets/selectexit.png");

    music->play();
    music->setLoop(true);
}

void MainMenu::Draw() {
    Engine::GetWindow().Clear(UINT_MAX);
    texture->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - texture->GetSize()) / 2.0 }));
    if (menu == 0)
    {
        selectplaybutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - selectplaybutton->GetSize().x) / 10 }, { (Engine::GetWindow().GetSize().y - selectplaybutton->GetSize().y) - 340 })));
        howtoplaybutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - howtoplaybutton->GetSize().x) / 10 }, { (Engine::GetWindow().GetSize().y - howtoplaybutton->GetSize().y) - 480 })));
        creditbutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - creditbutton->GetSize().x) / 10 }, { (Engine::GetWindow().GetSize().y - creditbutton->GetSize().y) - 620 })));
        exitbutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - selectcreditbutton->GetSize().x) -100 }, { (Engine::GetWindow().GetSize().y - selectcreditbutton->GetSize().y) - 600 })));
    }
    if (menu == 1)
    {
        playbutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - playbutton->GetSize().x) / 10 }, { (Engine::GetWindow().GetSize().y - playbutton->GetSize().y) - 340 })));
        selecthowtoplaybutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - selecthowtoplaybutton->GetSize().x) / 10 }, { (Engine::GetWindow().GetSize().y - selecthowtoplaybutton->GetSize().y) - 480 })));
        creditbutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - creditbutton->GetSize().x) / 10 }, { (Engine::GetWindow().GetSize().y - creditbutton->GetSize().y) - 620 })));
        exitbutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - selectcreditbutton->GetSize().x) -100 }, { (Engine::GetWindow().GetSize().y - selectcreditbutton->GetSize().y) - 600 })));
    }
    if (menu == 2)
    {
        playbutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - playbutton->GetSize().x) / 10 }, { (Engine::GetWindow().GetSize().y - playbutton->GetSize().y) - 340 })));
        howtoplaybutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - howtoplaybutton->GetSize().x) / 10 }, { (Engine::GetWindow().GetSize().y - howtoplaybutton->GetSize().y) - 480 })));
        selectcreditbutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - selectcreditbutton->GetSize().x) / 10 }, { (Engine::GetWindow().GetSize().y - selectcreditbutton->GetSize().y) - 620 })));
        exitbutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - selectcreditbutton->GetSize().x) -100 }, { (Engine::GetWindow().GetSize().y - selectcreditbutton->GetSize().y) - 600 })));

    }
    if (menu == 3)
    {
        playbutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - playbutton->GetSize().x) / 10 }, { (Engine::GetWindow().GetSize().y - playbutton->GetSize().y) - 340 })));
        howtoplaybutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - howtoplaybutton->GetSize().x) / 10 }, { (Engine::GetWindow().GetSize().y - howtoplaybutton->GetSize().y) - 480 })));
        creditbutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - selectcreditbutton->GetSize().x) / 10 }, { (Engine::GetWindow().GetSize().y - selectcreditbutton->GetSize().y) - 620 })));
        selectexitbutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - selectcreditbutton->GetSize().x)-100 }, { (Engine::GetWindow().GetSize().y - selectcreditbutton->GetSize().y) - 600 })));
    }

   
    
  
}

void MainMenu::Update([[maybe_unused]] double dt) {
    
    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::W)) {
        menu = (menu + 3) % 4;
    }
    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::S)) {
        menu = (menu + 1) % 4;
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
            case 3:
                Engine::GetGameStateManager().ClearNextGameState();
                break;
            }
            menu = 0;
        }
    }


}

void MainMenu::Unload() {
    music->stop();
}
