#pragma once

#include "Player.h"
#include "Monster.h"
class Mediator;
#include "TileStates.h"
#include "Tile.h"
#include "../Engine/Camera.h"
#include <vector>

class Map {
private: 
	// Entire map length and size
	static inline const double map_length = 10000;
	static inline const int map_size = 200;
	// Optimize for optimize_number times
	static inline const int optimize_number = 6;
	// When initializing, make WALL tile by initialize_chance.
	static inline const double initialize_chance = 30.0;
	// Tile length
	static inline const double tile_length = map_length / map_size;
	// For the day and night system.
	double time = 0;
	const double duration = 50;
	bool is_day = true;
	int date = 0;
	// Remainging colony
	int remaining_colony = 0;
	// Map!
	Tile* MAP[map_size][map_size];
	// Mediator
	Mediator* mediator;
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
	// Show the map based on the player's position.
	void Show_Map(Math::ivec2 player_position);
	// Return the map size
	int Get_Map_Size() { return map_size; }
	// Return the map length
	double Get_Map_Length() { return map_length; }
	// Return the tile length
	double Get_Tile_Length() { return tile_length; }
	// Return the tile state based on the "position"
	int GetTileState(Math::vec2 position) { return MAP[(int)(position.x/tile_length)][(int)(position.y/tile_length)]->Get_State(); }
	// Check attacked based on x, y, attack_point
	void CheckAttacked(int x, int y, Math::vec2 attack_point);
	// Get time
	double GetTime() { return time; }
	// Get duration
	double GetDuration() { return duration; }
	// Get is_day
	bool IsDay() { return is_day; }
	// Get the remaining colony
	int GetColony() { return remaining_colony; }
	// Get the date
	int GetDate() { return date; }
};
