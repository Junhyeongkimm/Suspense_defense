#pragma once
#include "../Engine/Vec2.h"
#include "../Engine/Sprite.h"
#include <vector>
#include <unordered_map>

class Mediator;

class Monster {
private:
	CS230::Sprite colonymonstersprite;
	CS230::Sprite flymonstersprite;
	Mediator* mediator;
	Math::vec2 position;
	Math::ivec2 tile_position;
	Math::vec2 direction;
	int hp = 2;
	double size = 40;
	double speed;
	// The monster will not move when it is paralyzed (when it spawned)
	const double paralyze_time = 0.5;
	double paralyze_count = 0;
	bool created_at_day;
	bool created_by_boss;

public:
	//scale
	void ColonySetWantScale(Math::vec2 new_scale);
	void FlySetWantScale(Math::vec2 new_scale);
	// Constructor
	Monster(Math::vec2 position, Mediator* mediator, bool created_by_boss = false);
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
	double scale_x;
	double scale_y;
	bool is_monstermoving = false;
	bool colonymonstertype;
	bool flymonstertype;
	enum class colonymonster_action{
		left,
		right,
		up,
		down
	};

	enum class flymonster_action {
		flymove1,
		flymove2

	};

};