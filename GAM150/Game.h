#ifndef __GAME_H__
#define __GAME_H__

#include "MapMaking.h"
#include "Player.h"
#include "Vec2.h"
#include "Monster.h"
#include <vector>


class Game {
private:
	Player player;
	Map map;
public:
	Game();
	void Load();
	void Update();
	void Draw();
};

#endif