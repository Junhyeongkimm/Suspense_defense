#include "../Engine/Engine.h"
#include "State.h"
#include "GameOver.h"
#include "doodle/drawing.hpp"
#include "doodle/input.hpp"

using namespace doodle;
// Need to be updated

GameOver::GameOver() :texture(texture)
{ }

void GameOver::Load() {

    texture = Engine::GetTextureManager().Load("Assets/Gameover.png");



}

void GameOver::Draw() {
    Engine::GetWindow().Clear(UINT_MAX);
    texture->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - texture->GetSize()) / 2.0 }));
 

}

void GameOver::Update([[maybe_unused]] double dt) {


    if (Key == KeyboardButtons::Escape) {
            Engine::GetGameStateManager().ClearNextGameState();
            Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
   
    }

}

void GameOver::Unload() {
    
}
