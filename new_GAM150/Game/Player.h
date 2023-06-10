#pragma once
#include "../Engine/Vec2.h"
#include "../Engine/Camera.h"
#include "../Engine/Matrix.h"
#include "PopupBox.h"
#include "../Engine/Sprite.h"


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
	const CS230::Camera& camera; // It is not used
	// HP
	int hp = 10;
	int max_hp = 10;
	// Attack
	int damage = 1;
	double attack_delay = 0.5;
	double attack_count = 0;
	bool is_attacking = false;
	enum ATTACK_MODE { MELEE = 0, RANGE = 1 };
	int attack_mode = MELEE;
	bool ranged_attack_unlocked = false;
	// Invincibility
	const double invincibility_time = 0.3;
	double invincibility_count = 0;
	// Resources
	int map_resource = 0;
	int monster_resource = 0;
	int warp_resource = 0;
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
	int attack_upgrade_count = 0;
	int utility_upgrade_count = 0;
	// Box
	PopupBox* box;
public:
	//scale
	void SetWantScale(Math::vec2 new_scale);
	// Constructor
	Player(Math::vec2 start_position, const CS230::Camera& camera, Mediator* mediator, Math::ivec2 tile_position);
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
	bool Able_To_Attack() { return attack_count > attack_delay; }
	double GetSize() { return size; }
	int GetDamage() { return damage; }
	double GetDistance(Math::vec2 target) { return sqrt((position.x - target.x) * (position.x - target.x) + (position.y - target.y) * (position.y - target.y)); }
	// Increase the resource
	void IncreaseMapResource() { ++map_resource; }
	void IncreaseMonsterResource() { ++monster_resource; }
	void IncreaseWarpResource() { ++warp_resource; }
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
	// Unlock Dodge
	void UnlockDodge() { dodge_unlocked = true; }
	// Unlock rnged attack
	void UnlockRangedAttack() { ranged_attack_unlocked = true; }

	CS230::Sprite sprite;
	CS230::Sprite weaponsprite;
	CS230::Sprite warpsprite;

	double scale_x;
	double scale_y;
	bool is_moving = false;

	enum class player_action {
		None,
		waiting,
		left,
		dodgeleft,
		up,
		dodgeup,
		down,
		dodgedown
	};

	enum class warp_action
	{
		warping
	};

	enum class Weapon_action
	{
		attack
	};

	bool flipped = false;
};