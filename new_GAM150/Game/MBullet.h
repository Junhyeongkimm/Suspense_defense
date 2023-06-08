#pragma once

#include "../Engine/Vec2.h"

class Mediator;

class MBullet {
protected:
	Math::vec2 position;
	const double speed = 600;
	const double size = 20;
	int damage = 1;

	Math::vec2 direction;

	Mediator* mediator;

public:

	MBullet(Math::vec2 start_position, Math::vec2 direction, Mediator* mediator);
	virtual void Update(double dt);
	virtual void Draw();
	virtual void Move(double dt);

	Math::vec2 GetPosition() { return position; }
	double GetSize() { return size; }
	double GetDistance(Math::vec2 target);
};

class Homing : public MBullet {
private:

public:
	Homing(Math::vec2 start_position, Math::vec2 direction, Mediator* mediator);
	void Move(double dt);
};

class Strong : public MBullet {
private:
	int damage = 2;
public:
	Strong(Math::vec2 start_position, Math::vec2 direction, Mediator* mediator);
};

class Fast : public MBullet {
private:
	double speed = 1200;
public:
	Fast(Math::vec2 start_position, Math::vec2 direction, Mediator* mediator);
};

class Big : public MBullet {
private:
	double size = 40;
public:
	Big(Math::vec2 start_position, Math::vec2 direction, Mediator* mediator);
};

class Heal : public MBullet {
private:

public:
	Heal(Math::vec2 start_position, Math::vec2 direction, Mediator* mediator);
	void Update(double dt);
};

class Ricochet : public MBullet {
private:
	int count = 2;
public:
	Ricochet(Math::vec2 start_position, Math::vec2 direction, Mediator* mediator);
	void Update(double dt);
};