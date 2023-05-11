#pragma once

#include "../Engine/Vec2.h"

class Mediator;

class Bullet {
private:
	Math::vec2 positoin;
	const double speed = 10;
	const double size = 20;

	Math::vec2 direction;

	Mediator* mediator;

public:
	Bullet(Math::vec2 start_positon, Math::vec2 direction, Mediator* mediator);
	void Update(double dt);
	Math::vec2 GetPosition() { return positoin; }
	bool IsOutOfScreen();


};