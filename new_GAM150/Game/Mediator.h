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
	void SetMap(Map* map);
	void SetBullet(std::vector<Bullet*>* bullets);
	Math::vec2 GetPlayerPosition() { return player->GetPosition(); }
	int GetMapState(Math::vec2 position) { return map->GetTileState(position); }

	void AddMonster(Math::vec2 position);
	void AddBullet(Math::vec2 position, Math::vec2 direction);

	void DeleteMonster(Monster* monster);
	void IncreaseMapResource() { player->IncreaseMapResource(); }
	void IncreaseMonsterResource() {player->IncreaseMonsterResource(); }
	void Warp() { player->GoToBase(); }

};
