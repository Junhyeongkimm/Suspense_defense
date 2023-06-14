#pragma once

#include "Player.h"
#include "Monster.h"
#include "TileStates.h"
#include "Tile.h"
#include "../Engine/Camera.h"
#include <vector>
#include "SFML/Audio.hpp"

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
	double time = 0.0;
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
	// Texture 
	CS230::Texture* bassarrowbackground;
	CS230::Texture* colonyarrowbackground;
	CS230::Texture* day;
	CS230::Texture* night;
	CS230::Texture* ui_resource;
	CS230::Texture* ui_potalresource;
	CS230::Texture* ui_monsterresource;
	CS230::Texture* ui_colony;
	CS230::Texture* ui_monster;

	sf::Music* dayMusic;
	sf::Music* nightMusic;

	// Constructor
	Map(Mediator* mediator);
	// Map making functions
	void MapMaking();
	void Initialize();
	void Optimizing();
	bool Check_Surrounding_Cells(const int x, const int y);
	// Update
	void Update(double dt);
	// Make special spaces
	void Make_Base();
	void Make_Colony(int number);
	void Make_Resource(int number);
	void Make_Warp(int number);
	void Make_Treasure();
	void Make_Boss_Zone();
	// Show things
	void Show_Map();
	void Base_Show_Arrow();
	void Colony_Show_Arrow();
	// Check attacked
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
	int GetBossClearCount() { return boss_clear_count; }
	void IncreaseBossCount();
	int base_upgrade_count = 0;
	int base_upgrade_max = 0;
	int GetUpgradeCount(){ return base_upgrade_count; }
	int GetUpgradeMax() { return base_upgrade_max; }
	int GetRepairCost();
	int GetUpgradeCost();
	void RepairBase();
	void UpgradeBase();
	~Map();
};
