#pragma once

#include "Player.h"
#include "Monster.h"
#include "TileStates.h"
#include "Tile.h"
#include "../Engine/Camera.h"
#include <vector>
class Mediator;
class Monster;

class Map {
private: 
	// Entire map length and size
	static inline const double map_length = 10000;
	static inline const int map_size = 200;
	// Optimize for optimize_number times
	static inline const int optimize_number = 5;
	// When initializing, make WALL tile by initialize_chance.
	static inline const double initialize_chance = 30.0;
	// Tile length
	static inline const double tile_length = map_length / map_size;
	// For the day and night system.
	double time = 0;
	const double duration = 60;
	bool is_day = true;
	int date = 0;
	int offset = 0;
	// Remainging colony
	int remaining_colony = 0;
	// Map!
	Tile* MAP[map_size][map_size];
	// Mediator
	Mediator* mediator;
	// Middle point
	Math::vec2 middle_point{ map_length / 2 + tile_length / 2, map_length / 2 + tile_length / 2 };
	Math::vec2 arrow_direction{ 0, 0 };
	// Monster, tower
	Monster* target;
	double tower_attack_count = 0;
	double tower_attack_cool = 1.0;
public:
	// Constructor
	Map(Mediator* mediator);
	// Make the map. It will be called when you start the game
	void MapMaking();
	// Initialize the map
	void Initialize();
	// Optimize the map (Check the surrounding tiles and change tiles into another tiles
	void Optimizing();
	// Make base camp at the middle point.
	void Make_Base();
	// Update the map
	void Update(double dt);
	// Check the surrounding cells. If MAP[x][y] is VOID and there are enough tiles of wall, change the tile to the WALL
	bool Check_Surrounding_Cells(const int x, const int y);
	// Make "number" numbers of colony
	void Make_Colony(int number);
	// Make "number" numbers of resource
	void Make_Resource(int number);
	// Make "number" numbers of warp
	void Make_Warp(int number);
	// Make unlock things
	void Make_Treasure();
	// Make boss zone
	void Make_Boss_Zone();
	// Show the map based on the player's position.
	void Show_Map();
	// Draw arrow to the base
	void Base_Show_Arrow();
	// Draw arrow to the closest colony
	void Colony_Show_Arrow();
	// Attacked
	void Attacked(Math::ivec2 position);
	// Getter functions
	int Get_Map_Size() { return map_size; }
	double Get_Map_Length() { return map_length; }
	double Get_Tile_Length() { return tile_length; }
	int GetTileState(Math::vec2 position) { return MAP[(int)(position.x/tile_length)][(int)(position.y/tile_length)]->Get_State(); }
	int GetTileStateInt(Math::ivec2 position) { return MAP[position.x][position.y]->Get_State(); }
	void CheckAttacked(int x, int y, Math::vec2 attack_point);
	double GetTime() { return time; }
	double GetDuration() { return duration; }
	bool IsDay() { return is_day; }
	int GetColony() { return remaining_colony; }
	int GetDate() { return date; }
	int GetOffset() { return offset; }
	// Unlock things
	int unlock_count = 0;
	// Upgrade things
	int boss_clear_count = 0;
	void IncreaseBossCount();
	int base_upgrade_count = 0;
	int base_upgrade_max = 0;
	int GetUpgradeCount(){ return base_upgrade_count; }
	int GetUpgradeMax() { return base_upgrade_max; }
	int GetRepairCost();
	int GetUpgradeCost();
	void RepairBase();
	void UpgradeBase();
};
