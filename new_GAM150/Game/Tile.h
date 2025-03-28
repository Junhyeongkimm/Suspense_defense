#pragma once

#include "../Engine/Sprite.h"
#include "../Engine/Vec2.h"
#include "doodle/drawing.hpp"

using namespace doodle;
// enum values below is the tiles
// enum TILES { WALL, VOID, COLONY_CORE, COLONY_SIDE, BASE_WALL, BASE_INSIDE, RESOURCE, WARP, TOWER, TREASURE };
class Tile {
protected:
    static inline const double size = 50;
    Math::vec2 position;
    int state = 0;
    int hp;
    HexColor color = 0;
    int max_hp;

public:
    // Constructor
    Tile(Math::vec2 position, int max_hp = 0);
    // Update
    virtual void Update(double dt);
    // Draw
    virtual void Draw(bool is_day) = 0;
    // Check attacked
    void Attacked(Math::vec2 attack_point);
    // Check attacked and true or false
    bool Attacked(Math::vec2 attack_point, int i);
    // Getter functions
    Math::vec2& GetPosition() { return position; }
    double GetDistance(Math::vec2 target) { return sqrt((position.x - target.x) * (position.x - target.x) + (position.y - target.y) * (position.y - target.y)); }
    int Get_State();
    int GetHP() { return hp; }
    int GetMaxHp() { return max_hp; }
    CS230::Sprite sprite;
    // Reduce hp of the tile
    virtual void ReduceHP() { --hp; }
    void Repair() { hp = max_hp; }
    void Upgrade() { max_hp += 5; hp = max_hp; }
    double scale_x;
    double scale_y;
};

// Wall tile
class Wall : public Tile {
public:

    Wall(Math::vec2 position);
    void Update(double dt);
    void Draw(bool is_day);
    void Attacked();
    enum class rock_animations {
        basic,
        broken
    };
private:
    bool rockbroken = false;

};
// Void tile
class Void : public Tile {
public:

    Void(Math::vec2 position);
    void Update(double dt);
    void Draw(bool is_day);
    enum class void_animations {
        basic
    };
};
// Colony_Core tile
class Colony_Core : public Tile {
public:
    Colony_Core(Math::vec2 position);
    void Update(double dt);
    void Draw(bool is_day);
    enum class colonycore_animations {
        basic,
        attacked1,
        attacked2
    };
private:
    bool colonyattacked= false;
    bool colonybroken = false;
};
// Colony_Side tile
class Colony_Side : public Tile {
public:
    Colony_Side(Math::vec2 position);
    void Update(double dt);
    void Draw(bool is_day);
    enum class colony_side
    {
        basic
    };
};
// Base_Wall tile
class Base_Wall : public Tile {
public:
    Base_Wall(Math::vec2 position);
    void Update(double dt);
    void Draw(bool is_day);
    void Attacked();
    bool AbleToBeAttacked();
    enum class basewall_animations {
        basic
    };
    virtual void ReduceHP() { if (AbleToBeAttacked()) { --hp; } }

private:
    double invincibility_count = 0;
    const double invincibility_time = 1.0;
};
// Base_Inside tile
class Base_Inside : public Tile {
public:
    Base_Inside(Math::vec2 position);
    void Update(double dt);
    void Draw(bool is_day);
    enum class baseinside_animations {
        basic
    };
};
// Resource tile
class Resource : public Tile {
public:

    Resource(Math::vec2 position);
    void Update(double dt);
    void Draw(bool is_day);
    void Attacked();
    enum class resource_animations {
        basic,
        attacked,
        broken
    };
private:
	bool resourceattacked = false;
	bool resourcebroken = false;
};

// Warp tile
class Warp :public Tile {
public:
    Warp(Math::vec2 position);
    void Update(double dt);
    void Draw(bool is_day);
    enum class warp_resource_animations {
        basic,
        broken
    };
private:
	bool warpbroken = false;
};

// Tower tile
class Tower : public Tile {
public:
    Tower(Math::vec2 position);
    void Update(double dt);
    void Draw(bool is_day);
    enum class Tower_animations {
        None,
        broken
    };
};

// Treasure tile
class Treasure : public Tile {
public:
    Treasure(Math::vec2 position);
    void Update(double dt);
    void Draw(bool is_day);
    enum class treasure_animations {
        None,
        broken
    };
    bool treasurebroken = false;
};

class Boss_Zone : public Tile {
public:
    Boss_Zone(Math::vec2 position);
    void Update(double dt);
    void Draw(bool is_day);
    enum class boss_zone_animations {
        Basic
    };
};