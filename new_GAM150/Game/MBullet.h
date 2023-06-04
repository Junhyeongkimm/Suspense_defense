#pragma once

#include "../Engine/Vec2.h"

class Mediator;

class MBullet {
protected:
	Math::vec2 position;
	double speed = 600;
	double size = 20;

	Math::vec2 direction;

	Mediator* mediator;

public:

	MBullet(Math::vec2 starat_position, Math::vec2 direction, Mediator* mediator);
	
	void Update(double dt);

	void Draw();

	Math::vec2 GetPosition() { return position; }

	double GetSize() { return size; }

};