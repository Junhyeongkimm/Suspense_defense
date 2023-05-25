#pragma once
#include "../Engine/Vec2.h"
#include "../Engine/Camera.h"
#include "../Engine/Matrix.h"

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
	double attack_delay = 0.5;
	double attack_count = 0;
	bool is_attacking = false;
	enum ATTACK_MODE { MELEE = 0, RANGE = 1 };
	int attack_mode = MELEE;
	// Invincibility
	const double invincibility_time = 1.0;
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
	bool is_dodging = false;
	const double dodging_time = 0.2;
	double dodging_count = 0;
	const double dodge_cool_time = 1.0;
	double dodge_cool_count = 0;
	Math::vec2 dodge_direction{ 0, 0 };
public:
	// Constructor
	Player(Math::vec2 start_position, const CS230::Camera& camera, Mediator* mediator, Math::ivec2 tile_position);
	// Update
	void Update(double dt);
	// Draw
	void Draw();
	// Getter functions
	Math::vec2& GetPosition() { return position; }
	const Math::ivec2& GetTilePosition() const { return tile_position; }
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
	// Increase the resource
	void IncreaseMapResource() { ++map_resource; }
	void IncreaseMonsterResource() { ++monster_resource; }
	void IncreaseWarpResource() { ++warp_resource; }
	// Attack
	void Attack();
	// Reduce hp
	void Reduce_hp();
	// Set the attack position
	void SetAttackPosition(Math::vec2 position) { attack_direction = position; }
	// Warp to the base
	void GoToBase();
};