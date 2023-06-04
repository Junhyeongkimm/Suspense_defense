#include "Mediator.h"

// Constructor
Mediator::Mediator() : map(nullptr), player(nullptr), monsters(), bullets(), monster_bullets() {

}
// Check if the monsters are attacked
void Mediator::Check_Monster_Attacked() {
	for (Monster* monster : *monsters) {
		//monster->Attacked(player->GetAttackPosition());
		monster->Attacked(player->GetPosition() + player->GetSize() * player->GetAttackDirection());
	}
}
// Check if the map is attacked
void Mediator::Check_Map_Attacked() {
	// Two for loop are to restrain restrain the scope
	for (int i = player->GetTilePosition().x - 3; i <= player->GetTilePosition().x + 3; i++) {
		for (int j = player->GetTilePosition().y - 3; j <= player->GetTilePosition().y + 3; j++) {
			//map->CheckAttacked(i, j, player->GetAttackPosition());
			map->CheckAttacked(i, j, player->GetPosition() + player->GetSize() * player->GetAttackDirection());
		}
	}
}
// Check if the player is attacekd
void Mediator::CheckPlayerAttacked() {
	for (Monster* monster : *monsters) {
		if (monster->GetDistance(player->GetPosition()) < monster->GetSize() / 2) {
			player->Reduce_hp();
		}
	}
}
// Set functions
void Mediator::SetPlayer(Player* player) {
	this->player = player;
}
void Mediator::SetMonsters(std::vector<Monster*>*monsters) {
	this->monsters = monsters;
}
void Mediator::SetBullets(std::vector<Bullet*>*bullets) {
	this->bullets = bullets;
}
void Mediator::SetMBullets(std::vector<MBullet*>* monster_bullets) {
	this->monster_bullets = monster_bullets;
}
void Mediator::SetMap(Map* map) {
	this->map = map;
}
// Add and delete monster
void Mediator::AddMonster(Math::vec2 position) {
	monsters->push_back(new Monster(position, this));
}
void Mediator::DeleteMonster(Monster* monster) {
	auto it = std::find(monsters->begin(), monsters->end(), monster);
	monsters->erase(std::remove(monsters->begin(), monsters->end(), monster), monsters->end());
	delete monster;
	this->IncreaseMonsterResource();
}
// Add and delete bullet
void Mediator::AddBullet(Math::vec2 position, Math::vec2 direction) {
	bullets->push_back(new Bullet(position, direction, this));
}
void Mediator::DeleteBullet(Bullet* bullet) {
	auto it = std::find(bullets->begin(), bullets->end(), bullet);
	bullets->erase(std::remove(bullets->begin(), bullets->end(), bullet), bullets->end());
	delete bullet;
}
// Add and delete monster bullet
void Mediator::AddMBullet(Math::vec2 position, Math::vec2 direction) {
	monster_bullets->push_back(new MBullet(position, direction, this));
}
void Mediator::DeleteMBullet(MBullet* bullet) {
	auto it = std::find(monster_bullets->begin(), monster_bullets->end(), bullet);
	monster_bullets->erase(std::remove(monster_bullets->begin(), monster_bullets->end(), bullet), monster_bullets->end());
	delete bullet;
}
void Mediator::BaseAttacked(Math::ivec2 position) {
	map->Attacked(position);
}