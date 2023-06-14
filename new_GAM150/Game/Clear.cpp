#include "../Engine/Engine.h"
#include "State.h"
#include "Clear.h"
#include "doodle/drawing.hpp"
#include "doodle/input.hpp"

using namespace doodle;
// Need to be updated

Clear::Clear() :clear(clear), music(nullptr)
{ }

void Clear::Load() {
    music = Engine::GetMusicManager().Load("Assets/Music/MainMenu.wav");

    clear = Engine::GetTextureManager().Load("Assets/howtoplay.png");

    music->play();
    music->setLoop(true);
}

void Clear::Draw() {
    Engine::GetWindow().Clear(UINT_MAX);
    clear->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - clear->GetSize()) / 2.0 }));
}

void Clear::Update([[maybe_unused]] double dt) {
    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Escape)) {
        //Engine::GetGameStateManager().ClearNextGameState();
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
    }
}

void Clear::Unload() {
    music->stop();
}
