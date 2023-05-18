#pragma once

#include "Player.h"
#include "Monster.h"
#include "MapGenerator.h"
#include "Bullet.h"
#include <vector>
#include "../Engine/Vec2.h"

//class Player;
//class Monster;
//class Map;

class Mediator {
private:
	Player* player;
	std::vector<Monster*>* monsters;
	std::vector<Bullet*>* bullets;
	Map* map;

public:
	Mediator();
	void Attack_player();

	void Check_Monster_Attacked();
	void Check_Map_Attacked();
	void CheckPlayerAttacked();
	

	void SetPlayer(Player* player);
	void SetMonsters(std::vector<Monster*>*monsters);
	void SetBullets(std::vector<Bullet*>*bullets);
	void SetMap(Map* map);
	Math::vec2 GetPlayerPosition() { return player->GetPosition(); }
	int GetMapState(Math::vec2 position) { return map->GetTileState(position); }

	void AddMonster(Math::vec2 position);
	void DeleteMonster(Monster* monster);

	void AddBullet(Math::vec2 position, Math::vec2 direction);
	void DeleteBullet(Bullet* bullet);

	void IncreaseMapResource() { player->IncreaseMapResource(); }
	void IncreaseMonsterResource() {player->IncreaseMonsterResource(); }
	void Warp() { player->GoToBase(); }

	bool Is_Day() { return map->IsDay(); }

	double GetMapLength() { return map->Get_Map_Length(); }
};
