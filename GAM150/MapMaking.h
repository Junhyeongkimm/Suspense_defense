#ifndef __MAP_MAKING_H__
#define __MAP_MAKING_H__

#include "Player.h"
#include "Vec2.h"

class Map {
private:
	Player& player;
public:
	Map(Player& player);
	static inline const double screen_width = 750 * 8;
	static inline const double screen_height = 750 * 8;

	static inline const int map_x = 100;
	static inline const int map_y = 100;

	static inline const int optimize_number = 6;
	static inline const double initialize_chance = 30.0;

	static inline const double tile_width = screen_width / map_x;
	static inline const double tile_height = screen_height / map_y;

	enum TILES { WALL, BROKEN_WALL, VOID, COLONY_CORE, COLONY_SIDE, RESOURCE, BASE };

	void MapMaking();
	void Initialize();
	void Optimizing();
	void Make_Base();
	bool Check_Surrounding_Cells(const int x, const int y);
	void Make_Colony(int number);
	void Make_Resource(int number);
	void Show_Map();
	void Change(int x, int y, int tile);

	int MAP[map_x][map_y] = { TILES::VOID };
};

#endif