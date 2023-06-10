#pragma once

#include "../Engine/Vec2.h"
class Mediator;
// --------------------------------- BOSS  ---------------------------------
class Boss {
protected:
	int hp;
	int max_hp;
	double speed;
	Math::vec2 position;
	double size;

	double pattern_count = 0;
	int pattern_index = 1;
	double pattern1_time;
	double pattern2_time;
	double pattern3_time;

	double heal_count = 0;
	double heal_time = 1.0;

	Mediator* mediator;
public:
	Boss(int hp, double speed, Math::vec2 position, double size, double time1, double time2, double time3, Mediator* mediator);
	void Update(double dt);
	virtual void Draw() = 0;

	virtual void Pattern1() = 0;
	virtual void Pattern2() = 0;
	virtual void Pattern3() = 0;
};
// --------------------------------- BOSS 1 ---------------------------------
class Boss1 : public Boss {
public:
	Boss1(Math::vec2 position, Mediator* mediator);
	void Draw();
	void Pattern1();
	void Pattern2();
	void Pattern3();
};
// --------------------------------- BOSS 2 ---------------------------------
class Boss2 : public Boss {
public:
	Boss2(Math::vec2 position, Mediator* mediator);
	void Draw();
	void Pattern1();
	void Pattern2();
	void Pattern3();

};
// --------------------------------- BOSS 3 ---------------------------------
class Boss3 : public Boss {
public:
	Boss3(Math::vec2 position, Mediator* mediator);
	void Draw();
	void Pattern1();
	void Pattern2();
	void Pattern3();

};
// --------------------------------- BOSS 4 ---------------------------------
class Boss4 : public Boss {
public:
	Boss4(Math::vec2 position, Mediator* mediator);
	void Draw();
	void Pattern1();
	void Pattern2();
	void Pattern3();

};