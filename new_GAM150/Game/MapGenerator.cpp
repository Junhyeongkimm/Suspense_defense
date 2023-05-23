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

void Map::Update(double dt) {
	time += dt; 


	if (time >= duration) {
		if (is_day == true) {
			is_day = false;
			for (int i = 0; i < map_size; i++) {
				for (int j = 0; j < map_size; j++) {
					if (MAP[i][j]->Get_State() == TILES::COLONY_CORE)
						mediator->AddMonster(MAP[i][j]->GetPosition());
				}
			}
		}
		else {
			is_day = true;
			++date;
			Make_Colony(date * 5);
			Make_Resource(date * 10);
			Make_Warp(date * 10);
		}
		time = 0;
	}
	
}

void Map::MapMaking() {
	Initialize();

	for (int i = 0; i < optimize_number; i++)
		Optimizing();

	Make_Base();
	Make_Colony(10);
	Make_Resource(100);
	Make_Warp(100);
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
	delete MAP[map_size / 2][map_size / 2];
	MAP[map_size / 2][map_size / 2] = new Tower(Math::vec2{ map_size / 2 * tile_length, map_size / 2 * tile_length });
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
	remaining_colony += number;
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
void Map::Make_Warp(int number) {
	for (int i = 0; i < number; i++) {
		while (1) {
			int rand_x = random(10, map_size - 10);
			int rand_y = random(10, map_size - 10);

			if (MAP[rand_x][rand_y]->Get_State() == TILES::VOID) {
				delete MAP[rand_x][rand_y];
				MAP[rand_x][rand_y] = new Warp(Math::vec2{ rand_x * tile_length, rand_y * tile_length });
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

	static int offset;
	
	if (is_day == true) {
		if (time <= duration / 4) {
			offset = (int)(4 * time / duration * 3) + 7; // 7 ~ 10
		}
		else if (time > duration / 4 && time <= 3 * duration / 4) { // 10
			offset = 10;
		}
		else {
			offset = 10 - (int)(4 * (time - 3 * duration / 4) / duration * 3); // 10~7
		}
	}
	else {
		if (time <= duration / 4) {
			offset = 7 - (int)(4 * time / duration * 3); // 7 ~ 4
		}
		else if (time > duration / 4 && time <= 3 * duration / 4) { // 4
			offset = 4;
		}
		else {
			offset = (int)(4 * (time - 3 * duration / 4) / duration * 3) + 4; // 4~7
		}
	}

	for (int i = player_x - offset - 1; i <= player_x + offset + 1; i++) {
		for (int j = player_y - offset - 1; j <= player_y + offset + 1; j++) {
			if (i < 0 || i >= map_size || j < 0 || j >= map_size)
				continue;
			MAP[i][j]->Draw(is_day);
		}
	}
	pop_settings();
}

void Map::CheckAttacked(int x, int y, Math::vec2 attack_point) {

	if (attack_point.x > 0 && attack_point.x < map_length && attack_point.y > 0 && attack_point.y < map_length
		&& x > 0 && x < map_size-1 && y > 0 && y < map_size-1) {
		switch (MAP[x][y]->Get_State()) {
		case TILES::COLONY_SIDE:
			if (MAP[x][y]->Attacked(attack_point, 1)) {
				for (int i = -1; i <= 1; i++) {
					for (int j = -1; j <= 1; j++) {
						if (MAP[x + i][y + j]->Get_State() == TILES::COLONY_CORE) {
							MAP[x + i][y + j]->ReduceHP();
							if (MAP[x + i][y + j]->GetHP() <= 0) {
								for (int k = -1; k <= 1; k++) {
									for (int l = -1; l <= 1; l++) {
										delete MAP[x + i + k][y + j + l];
										MAP[x + i + k][y + j + l] = new Void(Math::vec2{ (x + i + k) * tile_length, (y + j + l) * tile_length });
									}
								}
								mediator->AddMonster(MAP[x + i][y + j]->GetPosition());
								--remaining_colony;
							}
						}
					}
				}
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
				mediator->IncreaseMapResource();
			}

			break;
		case TILES::WARP:
			MAP[x][y]->Attacked(attack_point);
			if (MAP[x][y]->GetHP() <= 0) {
				delete MAP[x][y];
				MAP[x][y] = new Void(Math::vec2{ x * tile_length, y * tile_length });
				//mediator->Warp();
				mediator->IncreaseWarpResource();
			}

			break;
		default:

			break;
		}
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