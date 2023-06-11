#pragma once

#include "Player.h"
#include "Monster.h"
#include "MapGenerator.h"
#include "Bullet.h"
#include <vector>
#include "../Engine/Vec2.h"
#include "MBullet.h"
#include "Boss.h"

class Mediator {
private:
	Player* player;
	std::vector<Monster*>* monsters;
	std::vector<Bullet*>* bullets;
	std::vector<MBullet*>* monster_bullets;
	std::vector<Boss*>* bosses;
	Map* map;
public:
	// Constructor
	Mediator();
	// Check attacked
	void Check_Monster_Attacked();
	void Check_Map_Attacked();
	void CheckPlayerAttacked();
	// Set the member variables
	void SetPlayer(Player* player);
	void SetMonsters(std::vector<Monster*>*monsters);
	void SetBullets(std::vector<Bullet*>*bullets);
	void SetMBullets(std::vector<MBullet*>* monster_bullets);
	void SetBosses(std::vector<Boss*>* bosses);
	void SetMap(Map* map);

	// Add and delete monsters and bosses
	void AddMonster(Math::vec2 position);
	void DeleteMonster(Monster* monster);
	void AddBoss1(Math::vec2 position);
	void AddBoss2(Math::vec2 position);
	void AddBoss3(Math::vec2 position);
	void AddBoss4(Math::vec2 position);
	void DeleteBoss(Boss* boss);

	// Add and delete bullets and monster bullets
	void AddBullet(Math::vec2 position, Math::vec2 direction);
	void AddHoming(Math::vec2 position, Math::vec2 direction);
	void DeleteBullet(Bullet* bullet);
	void AddMBullet(Math::vec2 position, Math::vec2 direction, int type);
	void DeleteMBullet(MBullet* monster_bullet);

	// Check base attacked
	void BaseAttacked(Math::ivec2 position);

	// Getter functions
	std::vector<Monster*>* GetMonster() { return monsters; }
	std::vector<Bullet*>* GetBullets() { return bullets; }
	std::vector<MBullet*>* GetMBullets() { return monster_bullets; }
	std::vector<Boss*>* GetBosses() { return bosses; }
	Player* GetPlayer() { return player; }
	Map* GetMap() { return map; }
};
