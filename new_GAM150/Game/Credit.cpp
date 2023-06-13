#include "../Engine/Engine.h"
#include "State.h"
#include "Credit.h"
#include "doodle/drawing.hpp"
#include "doodle/input.hpp"

using namespace doodle;
// Need to be updated

#include "../Engine/Engine.h"
#include "State.h"
#include "Credit.h"
#include "doodle/drawing.hpp"
#include "doodle/input.hpp"

using namespace doodle;

Credit::Credit() : Credit1(nullptr), Credit2(nullptr), Credit3(nullptr), Credit4(nullptr), Credit5(nullptr), Credit6(nullptr), Credit7(nullptr), music(nullptr), creditTimer(0.0), creditDelay(1.0)
{ }

void Credit::Load() {
    music = Engine::GetMusicManager().Load("Assets/Music/MainMenu.wav");
    next = Engine::GetTextureManager().Load("Assets/next.png");
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
    if (credit == 0)
    {
        Credit1->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - Credit1->GetSize()) / 2.0 }));
    }
    if (credit == 1)
    {
        Credit2->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - Credit2->GetSize()) / 2.0 }));
    }
    if (credit == 2)
    {
        Credit3->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - Credit3->GetSize()) / 2.0 }));
    }
    if (credit == 3)
    {
        Credit4->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - Credit4->GetSize()) / 2.0 }));
    }
    if (credit == 4)
    {
        Credit5->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - Credit5->GetSize()) / 2.0 }));
    }
    if (credit == 5)
    {
        Credit6->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - Credit6->GetSize()) / 2.0 }));
    }
    if (credit == 6)
    {
        Credit7->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - Credit7->GetSize()) / 2.0 }));
    }
}

void Credit::Update(double dt) {
    // 타이머 업데이트
    creditTimer += dt;

    if (creditTimer >= creditDelay) {
        creditTimer = 0.0;  // 타이머 초기화

        // 크레딧 변경
        credit++;
        if (credit >= 7) {
            Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
            credit = 0;
        }
    }

    // 사용자 입력 처리
    if (Key == KeyboardButtons::Q) {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
    }
}

void Credit::Unload() {
    music->stop();
}