#include "AStar.h"
#include "TileStates.h"
#include "Mediator.h"

Math::ivec2 FindPath(const Math::ivec2& tile_position, const Math::ivec2& target, Mediator* mediator) {
	if (mediator->GetTileStateInt(target) == TILES::WALL ||
		mediator->GetTileStateInt(target) == TILES::COLONY_SIDE ||
		mediator->GetTileStateInt(target) == TILES::RESOURCE ||
		mediator->GetTileStateInt(target) == TILES::WARP)
		return tile_position;
	if (mediator->GetTileStateInt(target) == TILES::BASE_INSIDE ||
		mediator->GetTileStateInt(target) == TILES::BASE_WALL ||
		mediator->GetTileStateInt(target) == TILES::TOWER)
		return tile_position;

	std::vector<Math::ivec2> openList;
	std::vector<Math::ivec2> closedList;
	std::unordered_map<Math::ivec2, Math::ivec2> cameFrom;

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
				mediator->GetTileStateInt(neighbor) == TILES::BASE_WALL ||
				mediator->GetTileStateInt(neighbor) == TILES::TREASURE) {
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

std::vector<Math::ivec2> GetNeighboringTiles(const Math::ivec2& position) {
	std::vector<Math::ivec2> neighbors;
	neighbors.push_back({ position.x + 1, position.y });
	neighbors.push_back({ position.x - 1, position.y });
	neighbors.push_back({ position.x, position.y + 1 });
	neighbors.push_back({ position.x, position.y - 1 });
	return neighbors;
}