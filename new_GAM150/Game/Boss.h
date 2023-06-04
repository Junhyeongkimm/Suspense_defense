#pragma once

#include "../Engine/Vec2.h"
// --------------------------------- BOSS  ---------------------------------
class Boss {
protected:
	int hp;
	double speed;
	Math::vec2 position;
	double size;

	double pattern_count = 0;
	int pattern_index = 1;
	double pattern1_time;
	double pattern2_time;
	double pattern3_time;
public:
	Boss(int hp, double speed, Math::vec2 position, double size, double time1, double time2, double time3);
	void Update(double dt);
	virtual void Draw() = 0;

	virtual void Pattern1() = 0;
	virtual void Pattern2() = 0;
	virtual void Pattern3() = 0;
};
// --------------------------------- BOSS 1 ---------------------------------
class Boss1 : public Boss {
private:
	const int hp = 20;
	const double speed = 300;
	const double size = 100;

	double pattern1_time = 2.0;
	double pattern2_time = 2.0;
	double pattern3_time = 2.0;

public:
	Boss1(Math::vec2 position);
	void Draw();
	void Pattern1();
	void Pattern2();
	void Pattern3();
};
// --------------------------------- BOSS 2 ---------------------------------
class Boss2 : public Boss {
private:
	const int hp = 20;
	const double speed = 300;
	const double size = 100;

	double pattern1_time = 2.0;
	double pattern2_time = 2.0;
	double pattern3_time = 2.0;

public:
	Boss2(Math::vec2 position);
	void Draw();
	void Pattern1();
	void Pattern2();
	void Pattern3();

};
// --------------------------------- BOSS 3 ---------------------------------
class Boss3 : public Boss {
private:
	const int hp = 20;
	const double speed = 300;
	const double size = 100;

	double pattern1_time = 2.0;
	double pattern2_time = 2.0;
	double pattern3_time = 2.0;

public:
	Boss3(Math::vec2 position);
	void Draw();
	void Pattern1();
	void Pattern2();
	void Pattern3();

};
// --------------------------------- BOSS 4 ---------------------------------
class Boss4 : public Boss {
private:
	const int hp = 20;
	const double speed = 300;
	const double size = 100;

	double pattern1_time = 2.0;
	double pattern2_time = 2.0;
	double pattern3_time = 2.0;

public:
	Boss4(Math::vec2 position);
	void Draw();
	void Pattern1();
	void Pattern2();
	void Pattern3();

};