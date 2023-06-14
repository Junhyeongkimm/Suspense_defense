#include "../Engine/Engine.h"
#include "State.h"
#include "Splash2.h"

Splash2::Splash2() : texture2(texture2)
{ }

void Splash2::Load() {
    texture2 = Engine::GetTextureManager().Load("Assets/gametitle.png");
}

void Splash2::Draw() {
    Engine::GetWindow().Clear(UINT_MAX);

    texture2->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - texture2->GetSize()) / 2.0 }));
}

void Splash2::Update([[maybe_unused]] double dt) {
    if (counter >= 1) {
        //Engine::GetGameStateManager().ClearNextGameState();
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
    }
    counter += dt;
}

void Splash2::Unload() {

}
