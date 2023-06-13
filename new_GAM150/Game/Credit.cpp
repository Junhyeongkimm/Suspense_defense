#include "../Engine/Engine.h"
#include "State.h"
#include "Credit.h"
#include "doodle/drawing.hpp"
#include "doodle/input.hpp"

using namespace doodle;
// Need to be updated

Credit::Credit() :Credit1(nullptr), Credit2(nullptr), Credit3(nullptr), Credit4(nullptr), Credit5(nullptr), Credit6(nullptr), Credit7(nullptr), music(nullptr)
{ }

void Credit::Load() {
    music = Engine::GetMusicManager().Load("Assets/Music/MainMenu.wav");
    Credit1 = Engine::GetTextureManager().Load("Assets/Credit/Credit1.png");
    Credit2 = Engine::GetTextureManager().Load("Assets/Credit/Credit2.png");
    Credit3 = Engine::GetTextureManager().Load("Assets/Credit/Credit3.png");
    Credit4 = Engine::GetTextureManager().Load("Assets/Credit/Credit4.png");
    Credit5 = Engine::GetTextureManager().Load("Assets/Credit/Credit5.png");
    Credit6 = Engine::GetTextureManager().Load("Assets/Credit/Credit6.png");
    Credit7 = Engine::GetTextureManager().Load("Assets/Credit/Credit7.png");
    music->play();
    music->setLoop(true);
}

void Credit::Draw() {
    Engine::GetWindow().Clear(UINT_MAX);
    switch (credit) {
    case 1:
        Credit1->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - Credit1->GetSize()) / 2.0 }));
        break;
    case 2:
        Credit2->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - Credit2->GetSize()) / 2.0 }));
        break;
    case 3:
        Credit3->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - Credit3->GetSize()) / 2.0 }));
        break;
    case 4:
        Credit4->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - Credit4->GetSize()) / 2.0 }));
        break;
    case 5:
        Credit5->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - Credit5->GetSize()) / 2.0 }));
        break;
    case 6:
        Credit6->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - Credit6->GetSize()) / 2.0 }));
        break;
    case 7:
        Credit7->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - Credit7->GetSize()) / 2.0 }));
        break;
    }
}

void Credit::Update([[maybe_unused]] double dt) {
    
    if (counter >= 0)
    {
        credit++;
    }else if (counter >= 2)
    {
        credit++;
    }
    else if (counter >= 4)
    {
        credit++;
    }
    else if (counter >= 6)
    {
        credit++;
    }
    else if (counter >= 8)
    {
        credit++;
    }
    else if (counter >= 10)
    {
        credit++;
    }
    else if (counter >= 12)
    {
        credit++;
    }
    counter += dt;

    if (Key == KeyboardButtons::Q){ 
            Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
    }

}

void Credit::Unload() {
    music->stop();
}
