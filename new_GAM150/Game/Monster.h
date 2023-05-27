#pragma once
#include "../Engine/Vec2.h"

class Mediator;

class Monster {
private:
	Mediator* mediator;
	Math::vec2 position;
	int hp = 1;
	double size = 40;
	double speed = 200;
	// The monster will not move when it is paralyzed (when it spawned)
	const double paralyze_time = 1.0;
	double paralyze_count = 0;
public:
	// Constructor
	Monster(Math::vec2 position, Mediator* mediator);
	// Update by dt and will move the the target
	void Update(double dt, Math::vec2 target);
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
	enum class monster_action{
		left,
		leftattack,
		right,
		rightattack,
		up,
		upattack,
		down,
		downattack

	};
};