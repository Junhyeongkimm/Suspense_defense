#include "MapGenerator.h"
#include "doodle/random.hpp"
#include "doodle/angle.hpp"
#include "Mediator.h"
#include "../Engine/Engine.h"
using namespace doodle;

// Constructor of this class
Map::Map(Mediator* mediator) : mediator(mediator) {
	for (int i = 0; i < map_size; i++) {
		for (int j = 0; j < map_size; j++) {
			// Change all things to the Void
			delete MAP[i][j];
			MAP[i][j] = new Void( Math::vec2{ i*tile_length, j*tile_length } );
		}
	}
}
// Update function
void Map::Update(double dt) {
	// Time system
	time += dt; 
	if (time >= duration) {
		// Day -> Night timing
		if (is_day == true) {
			is_day = false;
			// Make monsters
			for (int i = 0; i < map_size; i++) {
				for (int j = 0; j < map_size; j++) {
					if (MAP[i][j]->Get_State() == TILES::COLONY_CORE)
						mediator->AddMonster(MAP[i][j]->GetPosition());
				}
			}
		}
		// Night -> Day timing
		else {
			// Date + 1 and make colony, resource, warp based on the date
			is_day = true;
			++date;
			Make_Colony(date * 5);
			Make_Resource(date * 10);
			Make_Warp(date * 10);
		}
		time = 0;
	}

	for (int i = 0; i < map_size; i++) {
		for (int j = 0; j < map_size; j++) {
			if (MAP[i][j]->Get_State() == TILES::BASE_WALL)
				MAP[i][j]->Update(dt);
		}
	}
}
// Map making system
void Map::MapMaking() {
	// Initializing
	Initialize();
	// Optimizing
	for (int i = 0; i < optimize_number; i++)
		Optimizing();
	// Make things
	Make_Base();
	Make_Treasure();
	Make_Colony(10);
	Make_Resource(50);
	Make_Warp(20);
}
// Initialize
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
// Optimize
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
// Make base
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
// Checking system
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
// Make colony
void Map::Make_Colony(int number) {
	int i = 0;
	while (i < number) {
		int rand_x = random(10, map_size - 10);
		int rand_y = random(10, map_size - 10);
		bool not_make = false;

		for (int i = rand_x - 4; i <= rand_x + 4; i++) {
			for (int j = rand_y - 4; j <= rand_y + 4; j++) {
				if (MAP[i][j]->Get_State() == TILES::COLONY_CORE || 
					MAP[i][j]->Get_State() == TILES::BASE_INSIDE ||
					MAP[i][j]->Get_State() == TILES::TREASURE ||
					((mediator->GetPlayerTilePosition().x == i) && (mediator->GetPlayerTilePosition().y == j)))
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
// Make resource
void Map::Make_Resource(int number) {
	for (int i = 0; i < number; i++) {
		while (1) {
			int rand_x = random(10, map_size - 10);
			int rand_y = random(10, map_size - 10);

			if (MAP[rand_x][rand_y]->Get_State() == TILES::VOID &&
				(!((mediator->GetPlayerTilePosition().x == rand_x) && (mediator->GetPlayerTilePosition().y == rand_y)))) {
				delete MAP[rand_x][rand_y];
				MAP[rand_x][rand_y] = new Resource(Math::vec2{ rand_x * tile_length, rand_y * tile_length });
				break;
			}
			else
				continue;
		}
	}
}
// Make warp
void Map::Make_Warp(int number) {
	for (int i = 0; i < number; i++) {
		while (1) {
			int rand_x = random(10, map_size - 10);
			int rand_y = random(10, map_size - 10);

			if (MAP[rand_x][rand_y]->Get_State() == TILES::VOID &&
				(!((mediator->GetPlayerTilePosition().x == rand_x) && (mediator->GetPlayerTilePosition().y == rand_y)))) {
				delete MAP[rand_x][rand_y];
				MAP[rand_x][rand_y] = new Warp(Math::vec2{ rand_x * tile_length, rand_y * tile_length });
				break;
			}
			else
				continue;
		}
	}
}
// Make unlock things camp
void Map::Make_Treasure() {
	Math::ivec2 middle{ map_size / 2, map_size / 2 };

	delete MAP[middle.x + 30][middle.y];
	delete MAP[middle.x - 30][middle.y];
	delete MAP[middle.x][middle.y + 30];
	delete MAP[middle.x][middle.y - 30];

	MAP[middle.x + 30][middle.y] = new Treasure(Math::vec2{ (middle.x + 30) * tile_length, middle.y * tile_length } );
	MAP[middle.x - 30][middle.y] = new Treasure(Math::vec2{ (middle.x - 30) * tile_length, middle.y * tile_length } );
	MAP[middle.x][middle.y + 30] = new Treasure(Math::vec2{ middle.x * tile_length, (middle.y + 30) * tile_length } );
	MAP[middle.x][middle.y - 30] = new Treasure(Math::vec2{ middle.x * tile_length, (middle.y - 30) * tile_length } );
}
// Show map
void Map::Show_Map() {
	push_settings();
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
	// Show map based on the player's position and the offset(=sight of the player)
	for (int i = mediator->GetPlayerTilePosition().x - offset - 1; i <= mediator->GetPlayerTilePosition().x + offset + 1; i++) {
		for (int j = mediator->GetPlayerTilePosition().y - offset - 1; j <= mediator->GetPlayerTilePosition().y + offset + 1; j++) {
			if (i < 0 || i >= map_size || j < 0 || j >= map_size)
				continue;
			MAP[i][j]->Draw(is_day);
		}
	}
	pop_settings();
}
// Show the direction of base
void Map::Base_Show_Arrow() {
	if (base_compass_unlocked == false)
		return;
	push_settings();

	arrow_direction = { middle_point.x - mediator->GetPlayerPosition().x, middle_point.y - mediator->GetPlayerPosition().y };
	arrow_direction /= arrow_direction.GetLength();
	arrow_direction *= 30;
	
	apply_translate(mediator->GetPlayerPosition().x, mediator->GetPlayerPosition().y);
	apply_translate(-150, (double)Engine::GetWindow().GetSize().y / 2 - 50);
	draw_ellipse(0, 0, 60);
	set_outline_width(15);

	draw_line(0, 0, arrow_direction.x, arrow_direction.y);
	
	pop_settings();
}
// Draw arrow to the closest colony
void Map::Colony_Show_Arrow() {
	if (colony_copass_unlocked == false || remaining_colony == 0)
		return;

	push_settings();

	Math::vec2 current;
	double distance = std::numeric_limits<double>::max();

	for (int i = 0; i < map_size; i++) {
		for (int j = 0; j < map_size; j++) {
			if (MAP[i][j]->Get_State() == TILES::COLONY_CORE) {
				if (MAP[i][j]->GetDistance(mediator->GetPlayerPosition()) < distance) {
					current = MAP[i][j]->GetPosition();
					distance = MAP[i][j]->GetDistance(mediator->GetPlayerPosition());
				}
			}
		}
	}

	arrow_direction = { current.x - mediator->GetPlayerPosition().x, current.y - mediator->GetPlayerPosition().y };
	arrow_direction /= arrow_direction.GetLength();
	arrow_direction *= 30;

	apply_translate(mediator->GetPlayerPosition().x, mediator->GetPlayerPosition().y);
	apply_translate(150, (double)Engine::GetWindow().GetSize().y / 2 - 50);
	draw_ellipse(0, 0, 60);
	set_outline_width(15);

	draw_line(0, 0, arrow_direction.x, arrow_direction.y);

	pop_settings();
}
// Attacked
void Map::Attacked(Math::ivec2 position) {
	MAP[position.x][position.y]->ReduceHP();
	if (MAP[position.x][position.y]->GetHP() <= 0) {
		delete MAP[position.x][position.y];
		MAP[position.x][position.y] = new Void({ position.x * tile_length, position.y * tile_length });
	}
}
// Check if the specified tile has attacked
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
								mediator->AddMonster(MAP[x + i][y + j]->GetPosition() + Math::vec2{ tile_length / 2, tile_length / 2 });
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
				mediator->IncreaseWarpResource();
			}
			break;

		case TILES::TREASURE:
			MAP[x][y]->Attacked(attack_point);
			if (MAP[x][y]->GetHP() <= 0) {
				delete MAP[x][y];
				MAP[x][y] = new Void(Math::vec2{ x * tile_length, y * tile_length });

				switch (unlock_count) {
				case 0:
					mediator->UnlockBaseArraw();
					break;
				case 1:
					mediator->UnlockRangedAttack();
					break;
				case 2:
					mediator->UnlockDodge();
					break;
				case 3:
					mediator->UnlockColonyArraw();
					break;
				}
				++unlock_count;
			}
			break;

		default:

			break;
		}
	}
	
}