#pragma once

#include "../Engine/GameState.h"
//#include "../Engine/Texture.h"
//#include "../Engine/Sprite.h"
#include "../Engine/Vec2.h"
#include "../Engine/Camera.h"
//#include "../Game/Background.h"
//#include "../Engine/GameObjectManager.h"
#include <vector>

#include "Player.h"
#include "Monster.h"
#include "MapGenerator.h"
#include "Mediator.h"


class Game : public CS230::GameState {
public:
    Game();
    void Load() override;
    void Update([[maybe_unused]] double dt) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override { return "Game"; }

private:
    //Background background;
    CS230::Camera camera;
    Player* player;
    std::vector<Monster*>monsters;
    Map* map;
    Mediator* mediator;
    //CS230::GameObjectManager gameobjectmanager;
};