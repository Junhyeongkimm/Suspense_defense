#include "MapGenerator.h"
#include "doodle/random.hpp"
#include "doodle/angle.hpp"
#include "Mediator.h"
#include "../Engine/Engine.h"
using namespace doodle;
#include <iostream>

Map::Map(Mediator* mediator) : mediator(mediator) {
	for (int i = 0; i < map_size; i++) {
		for (int j = 0; j < map_size; j++) {
			delete MAP[i][j];
			MAP[i][j] = new Void( Math::vec2{ i*tile_length, j*tile_length } );
		}
	}
}
void Map::MapMaking() {
	Initialize();

	for (int i = 0; i < optimize_number; i++)
		Optimizing();

	Make_Base();
	Make_Colony(150);
	Make_Resource(300);
}
void Map::Initialize() {
	for (int i = 0; i < map_size; i++) {
		for (int j = 0; j < map_size; j++) {
			if (i == 0 || i == map_size - 1 || j == 0 || j == map_size - 1) {
				delete MAP[i][j];
				MAP[i][j] = new Wall(Math::vec2{ i * tile_length, j * tile_length });
			}
			else {
				delete MAP[i][j];
				MAP[i][j] = new Void(Math::vec2{ i * tile_length, j * tile_length });
			}
		}
	}

	for (int i = 1; i < map_size - 1; i++) {
		for (int j = 1; j < map_size - 1; j++) {
			if (random(100) < initialize_chance) {
				delete MAP[i][j];
				MAP[i][j] = new Wall(Math::vec2{ i * tile_length, j * tile_length });
			}
		}
	}
}
void Map::Optimizing() {
	for (int i = 1; i < map_size - 1; i++) {
		for (int j = 1; j < map_size - 1; j++) {
			if (Check_Surrounding_Cells(i, j)) {
				delete MAP[i][j];
				MAP[i][j] = new Wall(Math::vec2{ i * tile_length, j * tile_length });
			}
				
		}
	}
}
void Map::Make_Base() {
	for (int i = map_size / 2 - 6; i <= map_size / 2 + 6; i++) {
		for (int j = map_size / 2 - 6; j <= map_size / 2 + 6; j++) {
			delete MAP[i][j];
			MAP[i][j] = new Void(Math::vec2{ i * tile_length, j * tile_length });
		}
	}
	for (int i = map_size / 2 - 4; i <= map_size / 2 + 4; i++) {
		for (int j = map_size / 2 - 4; j <= map_size / 2 + 4; j++) {
			delete MAP[i][j];
			MAP[i][j] = new Base_Wall(Math::vec2{ i * tile_length, j * tile_length });
		}
	}
	for (int i = map_size / 2 - 3; i <= map_size / 2 + 3; i++) {
		for (int j = map_size / 2 - 3; j <= map_size / 2 + 3; j++) {
			delete MAP[i][j];
			MAP[i][j] = new Base_Inside(Math::vec2{ i * tile_length, j * tile_length });
		}
	}
}
bool Map::Check_Surrounding_Cells(const int x, const int y) {
	int count = 0;
	for (int i = x - 1; i <= x + 1; i++) {
		for (int j = y - 1; j <= y + 1; j++) {
			if (MAP[i][j]->Get_State() == TILES::WALL)
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
		int rand_x = random(10, map_size - 10);
		int rand_y = random(10, map_size - 10);
		bool not_make = false;

		for (int i = rand_x - 4; i <= rand_x + 4; i++) {
			for (int j = rand_y - 4; j <= rand_y + 4; j++) {
				if (MAP[i][j]->Get_State() == TILES::COLONY_CORE || MAP[i][j]->Get_State() == TILES::BASE_INSIDE)
					not_make = true;
			}
		}
		if (not_make == false) {
			for (int i = rand_x - 2; i <= rand_x + 2; i++) {
				for (int j = rand_y - 2; j <= rand_y + 2; j++) {
					delete MAP[i][j];
					MAP[i][j] = new Void(Math::vec2{ i * tile_length, j * tile_length });
				}
			}
			for (int i = rand_x - 1; i <= rand_x + 1; i++) {
				for (int j = rand_y - 1; j <= rand_y + 1; j++) {
					delete MAP[i][j];
					MAP[i][j] = new Colony_Side(Math::vec2{ i * tile_length, j * tile_length });
				}
			}
			delete MAP[rand_x][rand_y];
			MAP[rand_x][rand_y] = new Colony_Core(Math::vec2{ rand_x * tile_length, rand_y * tile_length });
			i++;
		}
	}
}
void Map::Make_Resource(int number) {
	for (int i = 0; i < number; i++) {
		while (1) {
			int rand_x = random(10, map_size - 10);
			int rand_y = random(10, map_size - 10);

			if (MAP[rand_x][rand_y]->Get_State() == TILES::VOID) {
				delete MAP[rand_x][rand_y];
				MAP[rand_x][rand_y] = new Resource(Math::vec2{ rand_x * tile_length, rand_y * tile_length });
				break;
			}
			else
				continue;
		}
	}
}
void Map::Show_Map(Math::ivec2 player_position) {
	/*int player_x = (int)(map_length / 2 + player_position.x) / (int)tile_length;
	int player_y = (int)(map_length / 2 + player_position.y) / (int)tile_length;*/

	int player_x = player_position.x;
	int player_y = player_position.y;
	

	push_settings();
	//apply_translate(-camera.GetPosition().x, -camera.GetPosition().y);
	//apply_translate(-player_position.x, -player_position.y);
	
	//no_outline();
	for (int i = player_x - 10; i < player_x + 10; i++) {
		for (int j = player_y - 10; j < player_y + 10; j++) {
			if (i < 0 || i >= map_size || j < 0 || j >= map_size)
				continue;
			MAP[i][j]->Draw();
		}
	}
	pop_settings();
}

void Map::CheckAttacked(int x, int y, Math::vec2 attack_point) {

	switch (MAP[x][y]->Get_State()) {
	case TILES::COLONY_SIDE:
		MAP[x][y]->Attacked(attack_point);
		if (MAP[x][y]->GetHP() <= 0) {
			for (int i = -1; i <= 1; i++) {
				for (int j = -1; j <= 1; j++) {
					if (MAP[x+i][y+j]->Get_State() == TILES::COLONY_CORE) {
						for (int k = -1; k <= 1; k++) {
							for (int l = -1; l <= 1; l++) {
								delete MAP[x + i + k][y + j + l];
								MAP[x + i + k][y + j + l] = new Void(Math::vec2{ (x + i + k) * tile_length, (y + j + l) * tile_length });
							}
						}
					}
				}
			}
			//mediator->AddMonster(MAP[x][y]->GetPosition());
			mediator->AddMonster(MAP[x][y]->GetPosition());
		}
		
		break;
	case TILES::WALL:
		MAP[x][y]->Attacked(attack_point);
		if (MAP[x][y]->GetHP() <= 0) {
			delete MAP[x][y];
			MAP[x][y] = new Void(Math::vec2{ x * tile_length, y * tile_length });
		}

		break;
	case TILES::RESOURCE:
		MAP[x][y]->Attacked(attack_point);
		if (MAP[x][y]->GetHP() <= 0) {
			delete MAP[x][y];
			MAP[x][y] = new Void(Math::vec2{ x * tile_length, y * tile_length });
		}

		break;
	default:

		break;
	}

	/*if (MAP[x][y]->Get_State() == TILES::WALL || MAP[x][y]->Get_State() == TILES::COLONY_CORE || MAP[x][y]->Get_State() == TILES::RESOURCE) {
		MAP[x][y]->Attacked(attack_point);
		if (MAP[x][y]->GetHP() <= 0) {
			delete MAP[x][y];
			MAP[x][y] = new Void(Math::vec2{ x * tile_length, y * tile_length });
			std::cout << "Changed" << std::endl;
		}
	}*/
	
}