#include "Mediator.h"

Mediator::Mediator() : map(nullptr), player(nullptr), monsters(), bullets() {

}

void Mediator::Attack_player() {
	player->Reduce_hp();
	
}

//void Mediator::Attack_monster() {
//	monster->Reduce_hp();
//}

void Mediator::Check_Monster_Attacked() {
	for (Monster* monster : *monsters) {
		monster->Attacked(player->GetAttackPosition());
	}
}

void Mediator::Check_Map_Attacked() {
	
	for (int i = player->GetTilePosition().x - 3; i <= player->GetTilePosition().x + 3; i++) {
		for (int j = player->GetTilePosition().y - 3; j <= player->GetTilePosition().y + 3; j++) {
			map->CheckAttacked(i, j, player->GetAttackPosition());
			
		}
	}

	
}

void Mediator::CheckPlayerAttacked() {
	for (Monster* monster : *monsters) {
		if (monster->GetDistance(player->GetPosition()) < monster->GetSize() / 2) {
			player->Reduce_hp();
		}
	}
}

void Mediator::SetPlayer(Player* player) {
	this->player = player;
}
void Mediator::SetMonsters(std::vector<Monster*>*monsters) {
	this->monsters = monsters;
}
void Mediator::SetBullets(std::vector<Bullet*>*bullets) {
	this->bullets = bullets;
}
void Mediator::SetMap(Map* map) {
	this->map = map;
}

void Mediator::AddMonster(Math::vec2 position) {
	monsters->push_back(new Monster(position, this));
}
void Mediator::DeleteMonster(Monster* monster) {
	auto it = std::find(monsters->begin(), monsters->end(), monster);

	// If the monster is found, erase it from the vector
	//if (it != monsters->end()) {
	//	monsters->erase(it);
	//	delete monster; // Don't forget to free the memory!
	//}
	monsters->erase(std::remove(monsters->begin(), monsters->end(), monster), monsters->end());
	delete monster;
}

void Mediator::AddBullet(Math::vec2 position, Math::vec2 direction) {
	bullets->push_back(new Bullet(position, direction, this));
}
void Mediator::DeleteBullet(Bullet* bullet) {
	auto it = std::find(bullets->begin(), bullets->end(), bullet);
	bullets->erase(std::remove(bullets->begin(), bullets->end(), bullet), bullets->end());
	delete bullet;
}

//void Mediator::Check_Collision() {
//
//}

//void Mediator::Update() {
//
//}
