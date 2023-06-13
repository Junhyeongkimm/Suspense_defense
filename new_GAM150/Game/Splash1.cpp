#include "../Engine/Engine.h"
#include "State.h"
#include "Splash1.h"

Splash1::Splash1() : texture1(texture1)
{ }

void Splash1::Load() {
        texture1 = Engine::GetTextureManager().Load("Assets/Teamlogo.png");
}

void Splash1::Draw() {
    Engine::GetWindow().Clear(UINT_MAX);

    texture1->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - texture1->GetSize()) / 2.0 }));
}

void Splash1::Update([[maybe_unused]] double dt) {
    if (counter >= 1) {
        Engine::GetGameStateManager().ClearNextGameState();
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Splash2));
    }
    counter += dt;
}

void Splash1::Unload() {

}
