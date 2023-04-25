#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "Vec2.h"

class Player;

class Monster {
private:
	Vec2 Position;
	int hp = 1;
	double size = 50;
	double speed = 200;
public:
	Monster(Vec2 Position);
	void Update(Player player);
	void Draw();
	Vec2 Get_Position();
	double Get_Distance(double x, double y);
	double Get_Size();
	~Monster();
};

#endif