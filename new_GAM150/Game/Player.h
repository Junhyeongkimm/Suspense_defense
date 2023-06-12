#pragma once
#include "../Engine/Vec2.h"
#include "../Engine/Camera.h"
#include "../Engine/Matrix.h"
#include "PopupBox.h"
#include "../Engine/Sprite.h"
#include "doodle/input.hpp"
using namespace doodle;

class Mediator;

class Player {
private:
	Mediator* mediator;
	Math::TransformationMatrix matrix; // It is not used
	// Position of the player
	Math::vec2 position;
	// Attack direction of the player
	Math::vec2 attack_direction = { 0, 0 };
	// Tile position of the player on the map
	Math::ivec2 tile_position;
	double speed = 350;
	const double size = 40;
	// HP
	int hp = 10;
	int max_hp = 10;
	// Attack
	int damage = 2;
	double attack_delay = 1.0;
	double attack_count = 0;
	bool is_attacking = false;
	enum ATTACK_MODE { MELEE, RANGE, SHOTGUN, GATLING, HOMING };
	int attack_mode = MELEE;
	bool shotgun_unlocked = false;
	bool gatling_unlocked = false;
	bool homing_unlocked = false;

	// Invincibility
	const double invincibility_time = 0.3;
	double invincibility_count = 0;
	// Resources
	int map_resource = 0;
	int monster_resource = 0;
	int warp_resource = 1;
	// Warp
	bool is_warping = false;
	const double warp_time = 2.0;
	double warp_count = 0;
	// Dodge
	bool dodge_unlocked = true;
	bool is_dodging = false;
	const double dodging_time = 0.4;
	double dodging_count = 0;
	const double dodge_cool_time = 1.0;
	double dodge_cool_count = 0;
	Math::vec2 dodge_direction{ 0, 0 };
	// HP recovery
	double recover_count = 0.0;
	const double recover_cool = 1.0;
	// Upgrade count
	int upgrade_max = 0;
	int attack_upgrade_count = 0;
	int utility_upgrade_count = 0;
	// Box
	PopupBox* box;
	// Click

	bool not_clicked = false;

public:
	//scale
	void SetWantScale(Math::vec2 new_scale);
	
	void SwordSetWantScale(Math::vec2 new_scale);

	void GunSetWantScale(Math::vec2 new_scale);

	void ShoutGunSetWantScale(Math::vec2 new_scale);

	void GatlingGunSetWantScale(Math::vec2 new_scale);

	void ARGunSetWantScale(Math::vec2 new_scale);

	// Constructor
	Player(Math::vec2 start_position, Mediator* mediator, Math::ivec2 tile_position);
	// Update
	void Update(double dt);
	// Draw
	void Draw();
	// Getter functions
	Math::vec2 GetPosition() { return position; }
	Math::ivec2 GetTilePosition() { return tile_position; }
	Math::vec2 GetAttackPosition();
	Math::vec2 GetAttackDirection() { return attack_direction; }
	double GetDistanceFromAttack(Math::vec2 target);
	int GetMapResource() { return map_resource; }
	int GetMonsterResource() { return monster_resource; }
	int GetWarpResource() { return warp_resource; }
	int GetHP() { return hp; }
	int GetMaxHP() { return max_hp; }
	double GetSpeed() { return speed; }
	double GetAttackDelay() { return attack_delay; }
	double GetSize() { return size; }
	int GetDamage() { return damage; }
	double GetDistance(Math::vec2 target) { return sqrt((position.x - target.x) * (position.x - target.x) + (position.y - target.y) * (position.y - target.y)); }
	// Increase the resource
	void IncreaseMapResource() { ++map_resource; }
	void IncreaseMonsterResource() { ++monster_resource; }
	void IncreaseWarpResource() { ++warp_resource; }
	int GetAttackUpgradeCount() { return attack_upgrade_count; }
	int GetUtilityUpgradeCount() { return utility_upgrade_count; }
	int GetMaximumUpgrade() { return upgrade_max; }
	// Attack
	void Attack();
	// Reduce hp
	void Reduce_hp(int damage);
	// Heal
	void Heal();
	// Set the attack position
	void SetAttackPosition(Math::vec2 position) { attack_direction = position; }
	// Warp to the base
	void GoToBase();
	// Upgrade the player
	void Attack_Upgrade();
	void Utility_Upgrade();
	void UseMapResource(int resource) { map_resource -= resource; }
	void UseMonsterResource(int resource) { monster_resource -= resource; }
	int GetAttackUpgradeCost();
	int GetUtilityUpgradeCost();
	void IncreaseUpgradeMax() { upgrade_max += 2; }
	// Unlock Dodge
	void UnlockDodge() { dodge_unlocked = true; }
	// Unlock ranged attack
	void UnlockShotgun() { shotgun_unlocked = true; }
	void UnlockGatling() { gatling_unlocked = true; }
	void UnlockHoming() { homing_unlocked = true; }

	CS230::Sprite playersprite;
	CS230::Sprite sword_weaponsprite;
	CS230::Sprite gun_weaponsprite;
	CS230::Sprite shoutgun_weaponsprite;
	CS230::Sprite gatlinggun_weaponsprite;
	CS230::Sprite argun_weaponsprite;
	CS230::Sprite warpsprite;

	double scale_x;
	double scale_y;
	double swordscale_x;
	double swordscale_y;

	double gunscale_x;
	double gunscale_y;

	double shoutgunscale_x;
	double shoutgunscale_y;

	double gatlinggunscale_x;
	double gatlinggunscale_y;

	double argunscale_x;
	double argunscale_y;

	bool is_moving = false;

	enum class player_action {
		waiting,
		left,
		dodgeleft,
		dodgedown,
		down,
		dodgeup,
		up,
		right,
		dodgeright,
	};

	enum class warp_action
	{
		warping
	};

	enum class Weapon_action
	{
		attack
	};
};