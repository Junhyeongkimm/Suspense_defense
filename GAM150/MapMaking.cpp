#include "MapMaking.h"
#include <doodle/doodle.hpp>
using namespace doodle;
#include <iostream>

Map::Map(Player& player) :player(player) {

}
void Map::MapMaking() {
	Initialize();

	for (int i = 0; i < optimize_number; i++)
		Optimizing();

	Make_Base();
	Make_Colony(50);
	Make_Resource(100);
}
void Map::Initialize() {
	for (int i = 0; i < map_x; i++) {
		for (int j = 0; j < map_y; j++) {
			if (i == 0 || i == map_x - 1 || j == 0 || j == map_y - 1)
				MAP[i][j] = WALL;
			else
				MAP[i][j] = VOID;
		}
	}

	for (int i = 1; i < map_x - 1; i++) {
		for (int j = 1; j < map_y - 1; j++) {
			if (random(100) < initialize_chance) {
				MAP[i][j] = WALL;
			}
		}
	}
}
void Map::Optimizing() {
	for (int i = 1; i < map_x - 1; i++) {
		for (int j = 1; j < map_y - 1; j++) {
			if (Check_Surrounding_Cells(i, j))
				MAP[i][j] = WALL;
		}
	}
}
void Map::Make_Base() {
	/*
	for (int i = 43; i < 57; i++) {
		for (int j = 43; j < 57; j++) {
			MAP[i][j] = VOID;
		}
	}

	*/
	for (int i = 46; i <= 54; i++) {
		for (int j = 46; j <= 54; j++) {
			//MAP[i][j] = WALL;
			MAP[i][j] = VOID;
		}
	}
	for (int i = 47; i <= 53; i++) {
		for (int j = 47; j <= 53; j++) {
			//MAP[i][j] = WALL;
			MAP[i][j] = BASE;
		}
	}
	/*
	for (int i = 48; i <= 52; i++) {
		for (int j = 48; j <= 52; j++) {
			MAP[i][j] = VOID;
		}
	}
	*/
}
bool Map::Check_Surrounding_Cells(const int x, const int y) {
	int count = 0;
	for (int i = x - 1; i <= x + 1; i++) {
		for (int j = y - 1; j <= y + 1; j++) {
			if (MAP[i][j] == WALL)
				count++;
		}
	}
	if (count >= 5)
		return true;
	else
		return false;
}
void Map::Make_Colony(int number) {
	int i = 0;
	while (i < number) {
		int rand_x = random(10, 90);
		int rand_y = random(10, 90);
		bool not_make = false;

		for (int i = rand_x - 4; i <= rand_x + 4; i++) {
			for (int j = rand_y - 4; j <= rand_y + 4; j++) {
				if (MAP[i][j] == COLONY_CORE || MAP[i][j] == BASE)
					not_make = true;
			}
		}
		if (not_make == false) {
			for (int i = rand_x - 2; i <= rand_x + 2; i++) {
				for (int j = rand_y - 2; j <= rand_y + 2; j++) {
					MAP[i][j] = VOID;
				}
			}
			for (int i = rand_x - 1; i <= rand_x + 1; i++) {
				for (int j = rand_y - 1; j <= rand_y + 1; j++) {
					MAP[i][j] = COLONY_SIDE;
				}
			}
			MAP[rand_x][rand_y] = COLONY_CORE;
			i++;
		}
	}
}
void Map::Make_Resource(int number) {
	for (int i = 0; i < number; i++) {
		while (1) {
			int rand_x = random(10, 90);
			int rand_y = random(10, 90);

			if (MAP[rand_x][rand_y] == VOID) {
				MAP[rand_x][rand_y] = RESOURCE;
				break;
			}
			else
				continue;
		}
	}
}
void Map::Show_Map() {
	int player_x = (int)(screen_width / 2 + player.Get_Position().x) / (int)tile_width;
	int player_y = (int)(screen_height / 2 + player.Get_Position().y) / (int)tile_height;

	push_settings();
	apply_translate(-screen_width / 2, -screen_height / 2);
	for (int i = 0; i < map_x; i++) {
		for (int j = 0; j < map_y; j++) {
			if (player_x >= i - 10 && player_x <= i + 10 && player_y >= j - 10 && player_y <= j + 10) {
				switch (MAP[i][j]) {
				case WALL:
					set_fill_color(HexColor{ 0x000000ff });
					break;
				case BROKEN_WALL:
					set_fill_color(HexColor{ 0x888888ff });
					break;
				case VOID:
					set_fill_color(HexColor{ 0xffffffff });
					break;
				case COLONY_CORE:
					set_fill_color(HexColor{ 0x660000ff });
					break;
				case COLONY_SIDE:
					set_fill_color(HexColor{ 0x440000ff });
					break;
				case RESOURCE:
					set_fill_color(HexColor{ 0xffd966ff });
					break;
				case BASE:
					set_fill_color(HexColor{ 0x274e13ff });
					break;
				}
				draw_rectangle(tile_width * i, tile_height * j, tile_width, tile_height);
				
			}
		}
	}
	pop_settings();
}
void Map::Change(int x, int y, int tile) {
	MAP[x][y] = tile;
}