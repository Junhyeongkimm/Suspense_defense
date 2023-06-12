#pragma once
#include "../Engine/Vec2.h"
#include "../Engine/Sprite.h"
#include <vector>
#include <unordered_map>

class Mediator;

class Monster {
private:
	CS230::Sprite sprite;
	Mediator* mediator;
	Math::vec2 position;
	Math::ivec2 tile_position;
	Math::vec2 direction;
	int hp = 1;
	double size = 40;
	double speed;
	// The monster will not move when it is paralyzed (when it spawned)
	const double paralyze_time = 0.5;
	double paralyze_count = 0;
	bool created_at_day;
	double scale_x;
	double scale_y;
public:
	//scale
	void SetWantScale(Math::vec2 new_scale);
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
	// Reduec hp
	void Reduce_hp(int damage);
	int GetHp() { return hp; }
	// Destructor
	~Monster();

	enum class monster_action{
		left,
		rightattack,
		up,
		upattack,
		down,
		downattack

	};

	enum class flymonster_action {
		None,
		flymove

	};
	enum class flymonsterDirection {
		Left,
		Right
	};
};