#pragma once

#include "../Engine/Vec2.h"

class Mediator;

class Bullet {
private:
	Math::vec2 position;
	const double speed = 550;
	const double size = 20;

	Math::vec2 direction;

	Mediator* mediator;

public:
	// Constructor
	Bullet(Math::vec2 start_positon, Math::vec2 direction, Mediator* mediator);
	// Update by "dt"
	void Update(double dt);
	// Draw
	void Draw();
	// Get position
	Math::vec2 GetPosition() { return position; }

};