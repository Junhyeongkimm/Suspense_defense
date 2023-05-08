#pragma once

#include "Player.h"
#include "Monster.h"
#include "MapGenerator.h"
#include <vector>
#include "../Engine/Vec2.h"

//class Player;
//class Monster;
//class Map;

class Mediator {
public:
	Mediator();
	void Attack_player();
	//void Attack_monster();
	void Check_Monster_Attacked();
	void Check_Map_Attacked();
	void SetPlayer(Player* player);
	void SetMonsters(std::vector<Monster*>*monsters);
	void SetMap(Map* map);
	Math::vec2 GetPlayerPosition() { return player->GetPosition(); }
	int GetMapState(Math::vec2 position) { return map->GetTileState(position); }
	void AddMonster(Math::vec2 position);
	//void Check_Collision();
	//void Update();
	void DeleteMonster(Monster* monster);

private:
	Player* player;
	std::vector<Monster*>*monsters;
	Map* map;
};
