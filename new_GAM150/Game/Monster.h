#pragma once
#include "../Engine/Vec2.h"
#include <vector>
#include <unordered_map>

class Mediator;

class Monster {
private:
	Mediator* mediator;
	Math::vec2 position;
	Math::ivec2 tile_position;
	Math::vec2 direction;
	int hp = 1;
	double size = 40;
	double speed = 200;
	// The monster will not move when it is paralyzed (when it spawned)
	const double paralyze_time = 0.5;
	double paralyze_count = 0;
public:
	// Constructor
	Monster(Math::vec2 position, Mediator* mediator);
	// Update by dt and will move the the target
	void Update(double dt);
	// Draw
	void Draw();
	// Getter functions
	Math::vec2& GetPosition()  { return position; }
	double GetDistance(Math::vec2 target);
	double GetSize() { return size; }
	// Check attacked
	void Attacked(Math::vec2 attack_position);
	// Reduec hp
	void Reduce_hp();
	// Destructor
	~Monster();
	// Pathfinding
	std::vector<Math::ivec2> openList;
	std::vector<Math::ivec2> closedList;
	std::unordered_map<Math::ivec2, Math::ivec2> cameFrom;
	//double GetDistance(const Math::vec2& target);
	Math::ivec2 FindPath(const Math::ivec2& target);
	std::vector<Math::ivec2> GetNeighboringTiles(const Math::ivec2& position);
};