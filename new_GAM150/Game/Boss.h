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
	Math::ivec2 tile_position;
	double size;

	double pattern_count = 0;
	int pattern_index = 1;
	int index_save = 1;
	double pattern1_cool;
	double pattern2_cool;
	double pattern3_cool;
	double pattern_donothing = 1.0;
	int pattern1_loop;
	int pattern2_loop;
	int pattern3_loop;
	int loop_count = 0;

	double heal_count = 0;
	double heal_time = 0.5;

	Mediator* mediator;
public:
	Boss(int hp, double speed, Math::vec2 position, double size, double time1, double time2, double time3, int loop1, int loop2, int loop3, Mediator* mediator);
	void Update(double dt);
	virtual void Draw() = 0;
	void ReduceHP(int damage) { hp -= damage; }
	double GetDistance(Math::vec2 target) { return (position - target).GetLength(); }
	double GetSize() { return size; }
	Math::vec2 GetPosition() { return position; }
	int GetHp() { return hp; }

	virtual void Pattern1() = 0;
	virtual void Pattern2() = 0;
	virtual void Pattern3() = 0;
	bool is_boss_die = false;
	bool is_boss_attack = false;
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