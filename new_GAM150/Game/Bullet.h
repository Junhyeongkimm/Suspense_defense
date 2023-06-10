#pragma once

#include "../Engine/Vec2.h"
#include "../Engine/Sprite.h"

class Mediator;
class Monster;

class Bullet {
protected:
	Math::vec2 position;
	const double speed = 600;
	const double size = 20;
	double scale_x;
	double scale_y;

	Math::vec2 direction;
	CS230::Sprite sprite;
	Mediator* mediator;

public:
	//scale
	void SetWantScale(Math::vec2 new_scale);
	// Constructor
	Bullet(Math::vec2 start_positon, Math::vec2 direction, Mediator* mediator);
	// Update by "dt"
	void Update(double dt);
	// Move
	virtual void Move(double dt);
	// Draw
	void Draw();
	// Get position
	Math::vec2 GetPosition() { return position; }
	double GetSize() { return size; }
	double GetDistance(Math::vec2 target) { return (position - target).GetLength(); }
	enum class bullet {
		None
	};
};

class HomingShot :public Bullet {
private:
	Monster* target;
public:
	HomingShot(Math::vec2 start_positon, Math::vec2 direction, Mediator* mediator);
	void Move(double dt);
};