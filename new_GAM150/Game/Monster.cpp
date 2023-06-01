#include "Monster.h"
#include "Mediator.h"
#include <vector>
#include <algorithm>
// Constructor
Monster::Monster(Math::vec2 position, Mediator* mediator) : position(position), mediator(mediator) {
	tile_position.x = (int)((position.x) / mediator->GetTileLength());
	tile_position.y = (int)((position.y) / mediator->GetTileLength());

	if (mediator->Is_Day()) {
		created_at_day = true;
		speed = 300;
	}
	else {
		created_at_day = false;
		speed = 100;
	}
		
}
// Update
void Monster::Update(double dt) {
	// Paralyze. Monster will do nothing while the paralyze_count is smaller than the paralyze_time
	paralyze_count += dt;
	if (paralyze_count < paralyze_time)
		return;
	// During the daytime, it will move to the player.
	if (created_at_day && (mediator->GetTileStateInt(mediator->GetPlayerTilePosition()) != BASE_INSIDE)) {
		Math::ivec2 target_tile = FindPath(mediator->GetPlayerTilePosition());
		Math::vec2 target = { ((double)target_tile.x + 1 / 2.0) * mediator->GetTileLength(), ((double)target_tile.y + 1 / 2.0) * mediator->GetTileLength() };
		direction = target - position;
		direction /= direction.GetLength();
		position += direction * speed * dt;
	}
	// During the night time, it will move to the base
	else {
		Math::vec2 middle_point{ mediator->GetMapLength() / 2 + mediator->GetTileLength()/2, mediator->GetMapLength() / 2 + mediator->GetTileLength()/2 };

		direction.x = (middle_point.x - position.x) / GetDistance(middle_point);
		direction.y = (middle_point.y - position.y) / GetDistance(middle_point);

		double half_size = size / 2.0;

		Math::vec2 next_position_x = { position.x + speed * dt * direction.x, position.y };
		Math::vec2 next_position_y = { position.x, position.y + speed * dt * direction.y };

		bool can_move_x = (
			mediator->GetTileState({ next_position_x.x - half_size, next_position_x.y }) != TILES::BASE_WALL &&
			mediator->GetTileState({ next_position_x.x + half_size, next_position_x.y }) != TILES::BASE_WALL);

		bool can_move_y = (
			mediator->GetTileState({ next_position_y.x, next_position_y.y - half_size }) != TILES::BASE_WALL &&
			mediator->GetTileState({ next_position_y.x, next_position_y.y + half_size }) != TILES::BASE_WALL);

		if (can_move_x) {
			position.x = next_position_x.x;
		}

		if (can_move_y) {
			position.y = next_position_y.y;
		}
	}
	// Tile position update
	tile_position.x = (int)((position.x) / mediator->GetTileLength());
	tile_position.y = (int)((position.y) / mediator->GetTileLength());
}
// Draw
void Monster::Draw() {
	push_settings();
	set_fill_color(HexColor(0x888888ff));
	draw_ellipse(position.x, position.y, size);
	pop_settings();
}
// Getter distance from the monster to the target
double Monster::GetDistance(Math::vec2 target) {
	return sqrt((position.x - target.x) * (position.x - target.x) + (position.y - target.y) * (position.y - target.y));
}
// Reduce hp
void Monster::Reduce_hp() {
	hp -= mediator->GetDamage();
}
// Check attaced, check died
void Monster::Attacked(Math::vec2 attack_position) {
	if (GetDistance(attack_position) < size / 2) {
		Reduce_hp();
		if (hp <= 0) {
			mediator->DeleteMonster(this);
		}
	}
}
// Destructor
Monster::~Monster() {

}
// Pathfinding
Math::ivec2 Monster::FindPath(const Math::ivec2& target) {
	if (mediator->GetTileStateInt(target) == TILES::WALL ||
		mediator->GetTileStateInt(target) == TILES::COLONY_SIDE ||
		mediator->GetTileStateInt(target) == TILES::RESOURCE ||
		mediator->GetTileStateInt(target) == TILES::WARP)
		return tile_position;
	if (mediator->GetTileStateInt(target) == TILES::BASE_INSIDE ||
		mediator->GetTileStateInt(target) == TILES::BASE_WALL)
		return tile_position;

	// A* algorithm
	// Clear vectors
	openList.clear();
	closedList.clear();
	cameFrom.clear();
	// Push back the start position
	openList.push_back(tile_position);

	Math::ivec2 current;
	while (!openList.empty()) {
		// Select the lowest cost location on the openList and erase it from the openList
		current = openList.front();
		openList.erase(openList.begin());
		// If the monster arrived to the target, break
		if (current == target) {
			break;
		}
		// Check the neighbor tile from the current tile
		std::vector<Math::ivec2> neighbors = GetNeighboringTiles(current);
		Math::ivec2 optimalNeighbor = current; // Initialize the optimal neighbor
		double optimalCost = std::numeric_limits<double>::max(); // Set the optimal cost to the maximum value
		for (const Math::ivec2& neighbor : neighbors) {
			// Skip if the tile as already explored
			if (std::find_if(closedList.begin(), closedList.end(),
				[&](const Math::ivec2& element) { return element == neighbor; }) != closedList.end()) {
				continue;
			}
			// Skip if the tile is WALL
			if (mediator->GetTileStateInt(neighbor) == TILES::WALL || 
				mediator->GetTileStateInt(neighbor) == TILES::COLONY_SIDE ||
				mediator->GetTileStateInt(neighbor) == TILES::RESOURCE || 
				mediator->GetTileStateInt(neighbor) == TILES::WARP ||
				mediator->GetTileStateInt(neighbor) == TILES::BASE_INSIDE || 
				mediator->GetTileStateInt(neighbor) == TILES::BASE_WALL) {
				continue;
			}
			cameFrom[neighbor] = current;
			openList.push_back(neighbor);
			// Calculate Manhattan Distance Cost
			int actualCost = (int)cameFrom.size();
			int ManhattanDistanceCost = (abs(target.x - neighbor.x) + abs(target.y - neighbor.y));
			int neighborCost = actualCost + ManhattanDistanceCost;

			if (neighborCost < optimalCost) {
				optimalCost = neighborCost;
				optimalNeighbor = neighbor;
			}
		}

		// Push back current tile to the closed list
		closedList.push_back(current);

		// Choose optimal neighbor
		if (optimalNeighbor != current) {
			current = optimalNeighbor;
		}
	}
	// Backtracking the route
	Math::ivec2 nextPosition = current;
	while (cameFrom.count(current) > 0) {
		nextPosition = current;
		current = cameFrom[current];
		if (current == tile_position) {
			break;
		}
	}
	// Set next position to the direction
	//nextPosition -= tile_position;
	return nextPosition;
}

std::vector<Math::ivec2> Monster::GetNeighboringTiles(const Math::ivec2& position) {
	std::vector<Math::ivec2> neighbors;
	neighbors.push_back({ position.x + 1, position.y });
	neighbors.push_back({ position.x - 1, position.y });
	neighbors.push_back({ position.x, position.y + 1 });
	neighbors.push_back({ position.x, position.y - 1 });
	return neighbors;
}