#include "../Engine/Engine.h"
#include "State.h"
#include "Splash.h"

Splash::Splash() : texture(texture)
{ }

void Splash::Load() {
    texture = Engine::GetTextureManager().Load("Assets/DigiPen.png");
}

void Splash::Draw() {
    Engine::GetWindow().Clear(UINT_MAX);

    texture->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - texture->GetSize()) / 2.0 }));
}

void Splash::Update([[maybe_unused]] double dt) {
    Engine::GetLogger().LogDebug(std::to_string(counter));
    if (counter >= 1) {
        Engine::GetGameStateManager().ClearNextGameState();
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Splash1));
    }
    counter += dt;
}

void Splash::Unload() {

}
