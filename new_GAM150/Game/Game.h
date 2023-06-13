#pragma once

// Need to be updated.
#include "../Engine/GameState.h"
#include "../Engine/Sprite.h"
#include "../Engine/Vec2.h"
#include "../Engine/Camera.h"
#include <vector>

#include "Player.h"
#include "Monster.h"
#include "MapGenerator.h"
#include "MBullet.h"
#include "Bullet.h"
#include "Mediator.h"
#include "Boss.h"
#include "SFML/Audio.hpp"


class Game : public CS230::GameState {
public:
    //scale
    void SetWantScale(Math::vec2 new_scale);
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
    CS230::Sprite sprite;
    Player* player;
    std::vector<Monster*>monsters;
    std::vector<Bullet*>bullets;
    std::vector<MBullet*>monster_bullets;
    std::vector<Boss*>bosses;



    Map* map;
    Mediator* mediator;

    sf::Music* music;

    //CS230::GameObjectManager gameobjectmanager;
    Math::vec2 middle_point{ (double)map->Get_Map_Length() / 2 + map->Get_Tile_Length()/2, (double)map->Get_Map_Length() / 2 + map->Get_Tile_Length()/2 };
    double scale_x;
    double scale_y;
    Monster* target;
    enum class bullet {
        None
    };
};