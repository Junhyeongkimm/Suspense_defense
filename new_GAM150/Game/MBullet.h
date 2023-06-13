#pragma once

#include "../Engine/Vec2.h"
#include "../Engine/Sprite.h"

class Mediator;

enum BulletState { NORMAL, HOMING, STRONG, FAST, BIG, HEAL, RICOCHET };

class MBullet {
protected:
	Math::vec2 position;
	double speed;
	double size;
	int damage;

	Math::vec2 direction;

	Mediator* mediator;
public:

	CS230::Sprite boss1bullet;
	CS230::Sprite boss2bullet;
	CS230::Sprite boss3bullet;
	CS230::Sprite boss4bullet;

	MBullet(Math::vec2 start_position, Math::vec2 direction, Mediator* mediator, double speed = 400, double size = 20, int damage = 1);
	virtual void Update(double dt);
	virtual void Draw();
	virtual void Move(double dt);

	Math::vec2 GetPosition() { return position; }
	double GetSize() { return size; }
	double GetDistance(Math::vec2 target);
	double scale_x;
	double scale_y;
};

class Homing : public MBullet {
public:
	Homing(Math::vec2 start_position, Math::vec2 direction, Mediator* mediator);
	void Move(double dt);
};

class Strong : public MBullet {
public:
	Strong(Math::vec2 start_position, Math::vec2 direction, Mediator* mediator);
};

class Fast : public MBullet {
public:
	Fast(Math::vec2 start_position, Math::vec2 direction, Mediator* mediator);
};

class Big : public MBullet {
public:
	Big(Math::vec2 start_position, Math::vec2 direction, Mediator* mediator);
};

class Heal : public MBullet {
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