#include "MapGenerator.h"
#include "doodle/random.hpp"
#include "doodle/angle.hpp"
#include "Mediator.h"
#include "../Engine/Engine.h"
#include "State.h"
using namespace doodle;

// Constructor of this class
Map::Map(Mediator* mediator) : mediator(mediator), target(nullptr) {
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
			// date = 1, boss_clear_count = 0
			Make_Colony(date * 5);
			Make_Resource(date * 20);
			Make_Warp(date * 5);
			/*Make_Colony(date * (boss_clear_count + 1));
			Make_Resource(date * (boss_clear_count + 1));
			Make_Warp(date * (boss_clear_count + 1));*/
		}
		time = 0;
	}

	for (int i = 0; i < map_size; i++) {
		for (int j = 0; j < map_size; j++) {
			if (MAP[i][j]->Get_State() == TILES::BASE_WALL)
				MAP[i][j]->Update(dt);
		}
	}

	// Find the closest monster and set the target
	target = nullptr;
	for (Monster* monster : *mediator->GetMonster()) {
		if (target == nullptr || monster->GetDistance(middle_point) < target->GetDistance(middle_point))
			target = monster;
	}
	// Attack the target monster if it is not nullptr and in range
	tower_attack_count += dt;
	if (target != nullptr) {
		if ((target->GetDistance(middle_point) < mediator->GetMap()->Get_Tile_Length() * 15) && tower_attack_count >= tower_attack_cool) {
			Math::vec2 direction = target->GetPosition() - middle_point;
			direction /= direction.GetLength();
			mediator->AddBullet(middle_point, direction);

			tower_attack_count = 0;
		}
	}
	// If there is no monster, set the target to the nullptr
	if (mediator->GetMonster()->size() == 0)
		target = nullptr;
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
	Make_Resource(100);
	Make_Warp(50);
	Make_Boss_Zone();
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
					MAP[i][j]->Get_State() == TILES::BOSS_ZONE ||
					((mediator->GetPlayer()->GetTilePosition().x == i) && (mediator->GetPlayer()->GetTilePosition().y == j)))
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
				(!((mediator->GetPlayer()->GetTilePosition().x == rand_x) && (mediator->GetPlayer()->GetTilePosition().y == rand_y)))) {
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
				(!((mediator->GetPlayer()->GetTilePosition().x == rand_x) && (mediator->GetPlayer()->GetTilePosition().y == rand_y)))) {
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
// Make boss zone
void Map::Make_Boss_Zone() {
	Math::ivec2 first = { 10, 10 };
	Math::ivec2 second = { map_size - 10, 10 };
	Math::ivec2 third = { 10, map_size - 10 };
	Math::ivec2 fourth = { map_size - 10, map_size - 10 };

	for (int i = -6; i <= 6; i++) {
		for (int j = -6; j <= 6; j++) {
			if (i >= -4 && i <= 4 && j >= -4 && j <= 4) {
				Math::vec2 position = MAP[first.x + i][first.y + j]->GetPosition();
				delete MAP[first.x + i][first.y + j];
				MAP[first.x + i][first.y + j] = new Boss_Zone(position);
			}
			else {
				Math::vec2 position = MAP[first.x + i][first.y + j]->GetPosition();
				delete MAP[first.x + i][first.y + j];
				MAP[first.x + i][first.y + j] = new Wall(position);
			}
		}
	}
	mediator->AddBoss1(Math::vec2{ first.x * tile_length + tile_length / 2, first.y * tile_length + tile_length / 2 });
	for (int i = -6; i <= 6; i++) {
		for (int j = -6; j <= 6; j++) {
			if (i >= -4 && i <= 4 && j >= -4 && j <= 4) {
				Math::vec2 position = MAP[second.x + i][second.y + j]->GetPosition();
				delete MAP[second.x + i][second.y + j];
				MAP[second.x + i][second.y + j] = new Boss_Zone(position);
			}
			else {
				Math::vec2 position = MAP[second.x + i][second.y + j]->GetPosition();
				delete MAP[second.x + i][second.y + j];
				MAP[second.x + i][second.y + j] = new Wall(position);
			}
		}
	}
	mediator->AddBoss1(Math::vec2{ second.x * tile_length + tile_length / 2, second.y * tile_length + tile_length / 2 });
	for (int i = -6; i <= 6; i++) {
		for (int j = -6; j <= 6; j++) {
			if (i >= -4 && i <= 4 && j >= -4 && j <= 4) {
				Math::vec2 position = MAP[third.x + i][third.y + j]->GetPosition();
				delete MAP[third.x + i][third.y + j];
				MAP[third.x + i][third.y + j] = new Boss_Zone(position);
			}
			else {
				Math::vec2 position = MAP[third.x + i][third.y + j]->GetPosition();
				delete MAP[third.x + i][third.y + j];
				MAP[third.x + i][third.y + j] = new Wall(position);
			}
		}
	}
	mediator->AddBoss1(Math::vec2{ third.x * tile_length + tile_length / 2, third.y * tile_length + tile_length / 2 });
	for (int i = -6; i <= 6; i++) {
		for (int j = -6; j <= 6; j++) {
			if (i >= -4 && i <= 4 && j >= -4 && j <= 4) {
				Math::vec2 position = MAP[fourth.x + i][fourth.y + j]->GetPosition();
				delete MAP[fourth.x + i][fourth.y + j];
				MAP[fourth.x + i][fourth.y + j] = new Boss_Zone(position);
			}
			else {
				Math::vec2 position = MAP[fourth.x + i][fourth.y + j]->GetPosition();
				delete MAP[fourth.x + i][fourth.y + j];
				MAP[fourth.x + i][fourth.y + j] = new Wall(position);
			}
		}
	}
	mediator->AddBoss1(Math::vec2{ fourth.x * tile_length + tile_length / 2, fourth.y * tile_length + tile_length / 2 });
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
	for (int i = mediator->GetPlayer()->GetTilePosition().x - offset - 1; i <= mediator->GetPlayer()->GetTilePosition().x + offset + 1; i++) {
		for (int j = mediator->GetPlayer()->GetTilePosition().y - offset - 1; j <= mediator->GetPlayer()->GetTilePosition().y + offset + 1; j++) {
			if (i < 0 || i >= map_size || j < 0 || j >= map_size)
				continue;
			MAP[i][j]->Draw(is_day);
		}
	}
	pop_settings();
}
// Show the direction of base
void Map::Base_Show_Arrow() {
	push_settings();

	arrow_direction = { middle_point.x - mediator->GetPlayer()->GetPosition().x, middle_point.y - mediator->GetPlayer()->GetPosition().y };
	arrow_direction /= arrow_direction.GetLength();

	apply_translate(mediator->GetPlayer()->GetPosition().x, mediator->GetPlayer()->GetPosition().y);
	apply_translate(-150, (double)Engine::GetWindow().GetSize().y / 2 - 50);

	draw_ellipse(0, 0, 60);

	double angle = atan(arrow_direction.y / arrow_direction.x);
	if (arrow_direction.x < 0) {
		angle += PI;
	}
	else if (arrow_direction.x >= 0 && arrow_direction.y < 0) {
		angle += 2 * PI;
	}
	apply_rotate(angle);
	set_outline_width(15);
	draw_line(0, 0, 30, 0);
	
	pop_settings();
}
// Draw arrow to the closest colony
void Map::Colony_Show_Arrow() {
	if (remaining_colony == 0)
		return;

	push_settings();

	Math::vec2 current;
	double distance = std::numeric_limits<double>::max();
	for (int i = 0; i < map_size; i++) {
		for (int j = 0; j < map_size; j++) {
			if (MAP[i][j]->Get_State() == TILES::COLONY_CORE) {
				if (MAP[i][j]->GetDistance(mediator->GetPlayer()->GetPosition()) < distance) {
					current = MAP[i][j]->GetPosition();
					distance = MAP[i][j]->GetDistance(mediator->GetPlayer()->GetPosition());
				}
			}
		}
	}

	arrow_direction = { current.x - mediator->GetPlayer()->GetPosition().x, current.y - mediator->GetPlayer()->GetPosition().y };
	arrow_direction /= arrow_direction.GetLength();

	apply_translate(mediator->GetPlayer()->GetPosition().x, mediator->GetPlayer()->GetPosition().y);
	apply_translate(150, (double)Engine::GetWindow().GetSize().y / 2 - 50);
	draw_ellipse(0, 0, 60);

	set_outline_width(15);
	double angle = atan(arrow_direction.y / arrow_direction.x);
	if (arrow_direction.x < 0) {
		angle += PI;
	}
	else if (arrow_direction.x >= 0 && arrow_direction.y < 0) {
		angle += 2 * PI;
	}
	apply_rotate(angle);
	draw_line(0, 0, 30, 0);

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
				mediator->GetPlayer()->IncreaseMapResource();
			}
			break;

		case TILES::WARP:
			MAP[x][y]->Attacked(attack_point);
			if (MAP[x][y]->GetHP() <= 0) {
				delete MAP[x][y];
				MAP[x][y] = new Void(Math::vec2{ x * tile_length, y * tile_length });
				mediator->GetPlayer()->IncreaseWarpResource();
			}
			break;

		case TILES::TREASURE:
			//MAP[x][y]->Attacked(attack_point);
			//if (MAP[x][y]->GetHP() <= 0) {
			//	delete MAP[x][y];
			//	MAP[x][y] = new Void(Math::vec2{ x * tile_length, y * tile_length });

			//	switch (unlock_count) {
			//	case 0:
			//		mediator->GetMap()->UnlockBaseArraw();
			//		break;
			//	case 1:
			//		//mediator->UnlockRangedAttack();
			//		break;
			//	case 2:
			//		mediator->GetPlayer()->UnlockDodge();
			//		break;
			//	case 3:
			//		mediator->GetMap()->UnlockColonyArraw();
			//		break;
			//	}
			//	++unlock_count;
			//}
			//break;

		default:

			break;
		}
	}
	
}

// Upgrade things
int Map::GetRepairCost() {
	int void_count = 0;
	int cost = 0;
	// Check base wall
	for (int i = map_size / 2 - 4; i <= map_size / 2 + 4; i++) {
		for (int j = map_size / 2 - 4; j <= map_size / 2 + 4; j++) {
			// Skip base inside
			if (i > map_size / 2 - 4 && i < map_size / 2 + 4 && j>map_size / 2 - 4 && j < map_size / 2 + 4) {
				continue;
			}
			if (MAP[i][j]->Get_State() == TILES::VOID) {
				++void_count;
			}
			else {
				cost += (MAP[i][j]->GetMaxHp() - MAP[i][j]->GetHP());
			}

		}
	}
	cost += void_count * 5;

	return cost;
}
void Map::RepairBase() {
	// Return if the hp is full
	if (GetRepairCost() == 0) {
		return;
	}
	// Check the player have enough resources
	if (mediator->GetPlayer()->GetMonsterResource() >= GetRepairCost()) {
		// Use the resource from the player
		mediator->GetPlayer()->UseMonsterResource(GetRepairCost());
		// Check the base wall
		for (int i = map_size / 2 - 4; i <= map_size / 2 + 4; i++) {
			for (int j = map_size / 2 - 4; j <= map_size / 2 + 4; j++) {
				// Skip base inside
				if (i > map_size / 2 - 4 && i < map_size / 2 + 4 && j > map_size / 2 - 4 && j < map_size / 2 + 4) {
					continue;
				}
				// If the base wall has changed into void, change back to base wall
				if (MAP[i][j]->Get_State() == TILES::VOID) {
					Math::vec2 position = MAP[i][j]->GetPosition();
					delete MAP[i][j];
					MAP[i][j] = new Base_Wall(position);
				}
				// Repair the base wall
				else {
					MAP[i][j]->Repair();
				}
			}
		}
	}
	// If the player has not enough cost
	else {

	}
}
int Map::GetUpgradeCost() {
	switch (base_upgrade_count) {
	case 0:
		return 10;
		break;
	case 1:
		return 20;
		break;
	case 2:
		return 30;
		break;
	default:
		return 0;
	}
	return 0;
}
void Map::UpgradeBase() {
	if (mediator->GetPlayer()->GetMapResource() >= GetUpgradeCost()) {
		// Something
		switch (base_upgrade_count) {
		case 0:
			mediator->GetPlayer()->UnlockShotgun();
			break;
		case 1:
			mediator->GetPlayer()->UnlockHoming();
			break;
		case 2:
			mediator->GetPlayer()->UnlockGatling();
			break;
		}
		// Upgrade wall max hp
		for (int i = map_size / 2 - 4; i <= map_size / 2 + 4; i++) {
			for (int j = map_size / 2 - 4; j <= map_size / 2 + 4; j++) {
				// Skip base inside
				if (i > map_size / 2 - 4 && i < map_size / 2 + 4 && j > map_size / 2 - 4 && j < map_size / 2 + 4) {
					continue;
				}
				// If the base wall has changed into void, change back to base wall
				if (MAP[i][j]->Get_State() == TILES::VOID) {
					Math::vec2 position = MAP[i][j]->GetPosition();
					delete MAP[i][j];
					MAP[i][j] = new Base_Wall(position);
				}
				// Upgrade the walls's hp
				MAP[i][j]->Upgrade();
			}
		}
		// Increase upgrade maximum of player
		mediator->GetPlayer()->UseMonsterResource(GetUpgradeCost());
		mediator->GetPlayer()->IncreaseUpgradeMax();
		// Upgrade tower
		tower_attack_cool -= 0.1;
		// Update
		++base_upgrade_count;
	}
	else {

	}

}
void Map::IncreaseBossCount() { 
	++boss_clear_count; 
	++base_upgrade_max;
	// Game clear
	if (boss_clear_count == 4) {
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
	}
}