#include "../Engine/Engine.h"
#include "State.h"
#include "HowToPlay.h"
#include "doodle/drawing.hpp"
#include "doodle/input.hpp"

using namespace doodle;
// Need to be updated

HowToPlay::HowToPlay() :howtoplay(howtoplay), music(nullptr)
{ }

void HowToPlay::Load() {
    music = Engine::GetMusicManager().Load("Assets/Music/MainMenu.wav");

    howtoplay = Engine::GetTextureManager().Load("Assets/howtoplay.png");

    music->play();
    music->setLoop(true);
}

void HowToPlay::Draw() {
    Engine::GetWindow().Clear(UINT_MAX);
    howtoplay->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - howtoplay->GetSize()) / 2.0 }));
   
}

void HowToPlay::Update([[maybe_unused]] double dt) {

    
    if (Key == KeyboardButtons::Escape) {
            Engine::GetGameStateManager().ClearNextGameState();
            Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
    }

}

void HowToPlay::Unload() {
    music->stop();
}
