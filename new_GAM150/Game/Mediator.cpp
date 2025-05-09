#include "Mediator.h"
#include "doodle/random.hpp"

// Constructor
Mediator::Mediator() : map(nullptr), player(nullptr), monsters(), bosses(), bullets(), monster_bullets() {

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
		if (monster->GetDistance(player->GetPosition()) < (monster->GetSize() + player->GetSize()) / 2) {
			player->Reduce_hp(1);
		}
	}
	for (Boss* boss : *bosses) {
		if (boss->GetDistance(player->GetPosition()) < (boss->GetSize() + player->GetSize()) / 2) {
			player->Reduce_hp(1);
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
void Mediator::SetBosses(std::vector<Boss*>* bosses) {
	this->bosses = bosses;
}
void Mediator::SetMap(Map* map) {
	this->map = map;
}
// Add and delete monster
void Mediator::AddMonster(Math::vec2 position, bool created_by_boss) {
	monsters->push_back(new Monster(position, this, created_by_boss));
}
void Mediator::DeleteMonster(Monster* monster) {
	monsters->erase(remove(monsters->begin(), monsters->end(), monster), monsters->end());
	delete monster;
	player->IncreaseMonsterResource();
	//this->IncreaseMonsterResource();
}
// Add boss1
void Mediator::AddBoss1(Math::vec2 position) {
	bosses->push_back(new Boss1(position, this));
}
// Add boss2
void Mediator::AddBoss2(Math::vec2 position) {
	bosses->push_back(new Boss2(position, this));
}
// Add boss3
void Mediator::AddBoss3(Math::vec2 position) {
	bosses->push_back(new Boss3(position, this));
}
// Add boss4
void Mediator::AddBoss4(Math::vec2 position) {
	bosses->push_back(new Boss4(position, this));
}
// Delete boss4
void Mediator::DeleteBoss(Boss* boss) {
	bosses->erase(remove(bosses->begin(), bosses->end(), boss), bosses->end());
	delete boss;
}

// Add and delete bullet
void Mediator::AddBullet(Math::vec2 position, Math::vec2 direction) {
	bullets->push_back(new Bullet(position, direction, this, player->GetDamage()));
}
void Mediator::AddShotgun(Math::vec2 position, Math::vec2 direction) {
	bullets->push_back(new Bullet(position, direction + Math::vec2(random(-0.2, 0.2), random(-0.2, 0.2)), this, player->GetDamage()-1));
	bullets->push_back(new Bullet(position, direction + Math::vec2(random(-0.2, 0.2), random(-0.2, 0.2)), this, player->GetDamage()-1));
	bullets->push_back(new Bullet(position, direction + Math::vec2(random(-0.2, 0.2), random(-0.2, 0.2)), this, player->GetDamage()-1));
}
void Mediator::AddGatling(Math::vec2 position, Math::vec2 direction) {
	bullets->push_back(new Bullet(position, direction, this, player->GetDamage()-2));
}
void Mediator::AddHoming(Math::vec2 position, Math::vec2 direction) {
	bullets->push_back(new HomingShot(position, direction, this, player->GetDamage()-1));
}
void Mediator::DeleteBullet(Bullet* bullet) {
	bullets->erase(remove(bullets->begin(), bullets->end(), bullet), bullets->end());
	delete bullet;
}
// Add and delete monster bullet
void Mediator::AddMBullet(Math::vec2 position, Math::vec2 direction, int type) {
	//enum BulletState { NORMAL, HOMING, STRONG, FAST, BIG, HEAL, RICOCHET };
	direction.x += random(-0.2, 0.2);
	direction.y += random(-0.2, 0.2);

	switch (type) {
	case BulletState::NORMAL:
		monster_bullets->push_back(new MBullet(position, direction, this));
		break;
	case BulletState::HOMING:
		monster_bullets->push_back(new Homing(position, direction, this));
		break;
	case BulletState::STRONG:
		monster_bullets->push_back(new Strong(position, direction, this));
		break;
	case BulletState::FAST:
		monster_bullets->push_back(new Fast(position, direction, this));
		break;
	case BulletState::BIG:
		monster_bullets->push_back(new Big(position, direction, this));
		break;
	case BulletState::HEAL:
		monster_bullets->push_back(new Heal(position, direction, this));
		break;
	case BulletState::RICOCHET:
		monster_bullets->push_back(new Ricochet(position, direction, this));
		break;
	default:
		monster_bullets->push_back(new MBullet(position, direction, this));
	}
}
void Mediator::DeleteMBullet(MBullet* bullet) {
	monster_bullets->erase(remove(monster_bullets->begin(), monster_bullets->end(), bullet), monster_bullets->end());
	delete bullet;
}
void Mediator::BaseAttacked(Math::ivec2 position) {
	map->Attacked(position);
}