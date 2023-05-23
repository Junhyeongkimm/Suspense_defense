#pragma once

#include "Player.h"
#include "Monster.h"
//#include "Mediator.h"
class Mediator;
#include "TileStates.h"
#include "Tile.h"
#include "../Engine/Camera.h"
#include <vector>

class Map {
private: 
	static inline const double map_length = 10000;
	static inline const int map_size = 200;

	static inline const int optimize_number = 6;
	static inline const double initialize_chance = 30.0;

	static inline const double tile_length = map_length / map_size;

	double time = 0;
	const double duration = 50;
	bool is_day = true;
	int date = 0;

	int remaining_colony = 0;

	Tile* MAP[map_size][map_size];

	Mediator* mediator;
public:
	Map(Mediator* mediator);
	void MapMaking();
	void Initialize();
	void Optimizing();
	void Make_Base();
	void Update(double dt);
	bool Check_Surrounding_Cells(const int x, const int y);
	void Make_Colony(int number);
	void Make_Resource(int number);
	void Make_Warp(int number);
	void Show_Map(Math::ivec2 player_position);
	int Get_Map_Size() { return map_size; }
	double Get_Map_Length() { return map_length; }
	double Get_Tile_Length() { return tile_length; }
	int GetTileState(Math::vec2 position) { return MAP[(int)(position.x/tile_length)][(int)(position.y/tile_length)]->Get_State(); }
	//int GetTileState(Math::ivec2 position) { return MAP[position.x][position.y]->Get_State(); }
	void CheckAttacked(int x, int y, Math::vec2 attack_point);
	int GetTileHP(int x, int y) { }
	double GetTime() { return time; }
	double GetDuration() { return duration; }
	bool IsDay() { return is_day; }
	int GetColony() { return remaining_colony; }
	int GetDate() { return date; }
};
