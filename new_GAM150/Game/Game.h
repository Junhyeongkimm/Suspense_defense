#pragma once

// Need to be updated.
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
#include "MBullet.h"
#include "Bullet.h"
#include "Mediator.h"

class Game : public CS230::GameState {
public:
    // Constructor
    Game();
    // Load
    void Load() override;
    // Update
    void Update([[maybe_unused]] double dt) override;
    // Unload
    void Unload() override;
    // Draw
    void Draw() override;
    // Get name
    std::string GetName() override { return "Game"; }
private:
    //Background background;
    CS230::Camera camera;
    Player* player;
    std::vector<Monster*>monsters;
    std::vector<Bullet*>bullets;
    std::vector<MBullet*>monster_bullets;
    Map* map;
    Mediator* mediator;
    //CS230::GameObjectManager gameobjectmanager;
    Math::vec2 middle_point{ (double)map->Get_Map_Length() / 2 + map->Get_Tile_Length()/2, (double)map->Get_Map_Length() / 2 + map->Get_Tile_Length()/2 };
    double tower_attack_count = 0;
    double tower_attack_cool = 2.0;
    Monster* target;
};