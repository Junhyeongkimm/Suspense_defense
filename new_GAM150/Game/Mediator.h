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

	void Check_Monster_Attacked();
	void Check_Map_Attacked();
	void CheckPlayerAttacked();

	void SetPlayer(Player* player);
	void SetMonsters(std::vector<Monster*>*monsters);
	void SetMap(Map* map);
	Math::vec2 GetPlayerPosition() { return player->GetPosition(); }
	int GetMapState(Math::vec2 position) { return map->GetTileState(position); }

	//int GetMapState(Math::ivec2 position) { return map->GetTileState(position); }
	void AddMonster(Math::vec2 position);

	void DeleteMonster(Monster* monster);
	void IncreaseMapResource() { player->IncreaseMapResource(); }
	void IncreaseMonsterResource() {player->IncreaseMonsterResource(); }
	void Warp() { player->GoToBase(); }

private:
	Player* player;
	std::vector<Monster*>*monsters;
	Map* map;
};
