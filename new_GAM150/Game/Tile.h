#pragma once

#include "../Engine/Vec2.h"
#include "doodle/drawing.hpp"
using namespace doodle;

// enum TILES { WALL, VOID, COLONY_CORE, COLONY_SIDE, BASE_WALL, BASE_INSIDE, RESOURCE, TOWER };

class Tile {
protected:
	static inline const double size = 50;
	Math::vec2 position;
	int state = 0;
	int hp = 0;
	HexColor color = 0;
public:
	Tile(Math::vec2 position);
	virtual void Update();
	virtual void Draw(bool is_day) = 0;
	 void Attacked(Math::vec2 attack_point);
	 bool Attacked(Math::vec2 attack_point, int i);
	const Math::vec2& GetPosition() const { return position; }
	double GetDistance(Math::vec2 target) { return sqrt((position.x - target.x) * (position.x - target.x) + (position.y - target.y) * (position.y - target.y)); }
	int Get_State();
	int GetHP() { return hp; }
	void ReduceHP() { --hp; }
};

class Wall : public Tile {
public:
	Wall(Math::vec2 position);
	void Update();
	void Draw(bool is_day);
	virtual void Attacked();
};

class Void : public Tile {
public:
	Void(Math::vec2 position);
	void Update();
	void Draw(bool is_day);
};

class Colony_Core : public Tile {
public:
	Colony_Core(Math::vec2 position);
	void Update();
	void Draw(bool is_day);
	virtual void Attacked();
};

class Colony_Side : public Tile {
public:
	Colony_Side(Math::vec2 position);
	void Update();
	void Draw(bool is_day);
	virtual void Attacked();
};

class Base_Wall : public Tile {
public:
	Base_Wall(Math::vec2 position);
	void Update();
	void Draw(bool is_day);
	virtual void Attacked();
	bool AbleToBeAttacked() { if (invincibility_count > invincibility_time) { invincibility_count = 0; return true; } else { return false; } }
private:
	double invincibility_count = 0;
	const double invincibility_time = 1.0;
};

class Base_Inside : public Tile {
public:
	Base_Inside(Math::vec2 position);
	void Update();
	void Draw(bool is_day);
};

class Resource : public Tile {
public:
	Resource(Math::vec2 position);
	void Update();
	void Draw(bool is_day);
};

class Warp :public Tile {
public:
	Warp(Math::vec2 position);
	void Update();
	void Draw(bool is_day);
};

class Tower : public Tile {
public:
	Tower(Math::vec2 position);
	void Update();
	void Draw(bool is_day);
};
