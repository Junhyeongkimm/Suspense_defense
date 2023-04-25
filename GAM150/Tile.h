#ifndef __TILE_H__
#define __TILE_H__

#include "Vec2.h"
#include "doodle/doodle.hpp"
using namespace doodle;

class Tile {
private:
	Vec2 position;
	// Image
	HexColor color;
	double size;
	int state;
	int hp;
public:
	Tile(Vec2 position, double size, HexColor color, int state, int hp);
	void Update();
	void Draw();
	void Change_State(int state);
	int Get_State();
	void Check_Attacked(Vec2 pos);
};

#endif