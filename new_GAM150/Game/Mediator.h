#pragma once

#include "Player.h"
#include "Monster.h"
#include "MapGenerator.h"
#include "Bullet.h"
#include <vector>
#include "../Engine/Vec2.h"

class Mediator {
private:
	Player* player;
	std::vector<Monster*>* monsters;
	std::vector<Bullet*>* bullets;
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
	void SetMap(Map* map);
	// Add monster at the position, push back to the monsters
	void AddMonster(Math::vec2 position);
	// Delete the monster from the vector monsters
	void DeleteMonster(Monster* monster);
	// Add bullet at the position, directed to the direction, push back to the bullets
	void AddBullet(Math::vec2 position, Math::vec2 direction);
	// Delete the bullet from the vector bullets
	void DeleteBullet(Bullet* bullet);
	// Increase the resources
	void IncreaseMapResource() { player->IncreaseMapResource(); }
	void IncreaseMonsterResource() {player->IncreaseMonsterResource(); }
	void IncreaseWarpResource() { player->IncreaseWarpResource(); }
	void BaseAttacked(Math::ivec2 position);
	// Warp to the base
	void Warp() { player->GoToBase(); }
	// Check if it is day
	bool Is_Day() { return map->IsDay(); }
	// Getter functions
	double GetMapLength() { return map->Get_Map_Length(); }
	double GetTileLength() { return map->Get_Tile_Length(); }
	int GetMapSize() { return map->Get_Map_Size(); }
	Math::vec2 GetPlayerPosition() { return player->GetPosition(); }
	Math::ivec2 GetPlayerTilePosition() { return player->GetTilePosition(); }
	int GetDamage() { return player->GetDamage(); }
	int GetTileState(Math::vec2 position) {return map->GetTileState(position); }
	int GetTileStateInt(Math::ivec2 position) { return map->GetTileStateInt(position); }
	// Unlock things
	void UnlockDodge() { player->UnlockDodge(); }
	void UnlockRangedAttack() { player->UnlockRangedAttack(); }
	void UnlockBaseArraw() { map->UnlockBaseArraw(); }
	void UnlockColonyArraw() { map->UnlockColonyArraw(); }
};
