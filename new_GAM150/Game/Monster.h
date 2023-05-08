#pragma once
#include "../Engine/Vec2.h"
//#include "Mediator.h"
class Mediator;

class Monster {
private:
	Math::vec2 position;
	int hp = 1;
	double size = 50;
	double speed = 200;

	Mediator* mediator;
public:
	Monster(Math::vec2 position, Mediator* mediator);
	void Update(double dt, Math::vec2 target);
	void Move(Math::vec2 target, double dt);
	void Draw();
	const Math::vec2& GetPosition() const { return position; }
	double GetDistance(Math::vec2 target);
	double GetSize() { return size; }
	void Attacked(Math::vec2 attack_position);
	void Reduce_hp();
	~Monster();
};