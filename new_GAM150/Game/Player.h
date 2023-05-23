#pragma once
#include "../Engine/Vec2.h"
#include "../Engine/Camera.h"
#include "../Engine/Matrix.h"

//#include "Mediator.h"
class Mediator;

class Player {
private:
	Mediator* mediator;
	Math::TransformationMatrix matrix;
	Math::vec2 position;
	Math::vec2 attack_position = { 0, 0 };
	Math::ivec2 tile_position;
	const double speed = 500;
	const double size = 40;
	const CS230::Camera& camera;

	int hp = 10;
	const double attack_delay = 0.5;
	double attack_count = 0;
	bool is_attacking = false;

	enum ATTACK_MODE { MELEE = 0, RANGE = 1 };
	int attack_mode = MELEE;

	const double invincibility_time = 1.0;
	double invincibility_count = 0;

	int map_resource = 0;
	int monster_resource = 0;
	int warp_resource = 0;

	bool is_warping = false;
	const double warp_time = 2.0;
	double warp_count = 0;

	bool is_dodging = false;
	const double dodge_time = 0.2;
	double dodge_count = 0;
	Math::vec2 dodge_direction{ 0, 0 };


public:
	Player(Math::vec2 start_position, const CS230::Camera& camera, Mediator* mediator, Math::ivec2 tile_position);
	void Update(double dt);
	void Draw();
	const Math::vec2& GetPosition() const { return position; }
	const Math::ivec2& GetTilePosition() const { return tile_position; }
	Math::vec2 GetAttackPosition();
	bool Able_To_Attack() { return attack_count > attack_delay; }
	double GetDistanceFromAttack(Math::vec2 target);
	void Attack();
	void Reduce_hp();
	void IncreaseMapResource() { ++map_resource; }
	void IncreaseMonsterResource() { ++monster_resource; }
	void IncreaseWarpResource() { ++warp_resource; }
	int GetMapResource() { return map_resource; }
	int GetMonsterResource() { return monster_resource; }
	int GetWarpResource() { return warp_resource; }
	int GetHP() { return hp; }
	void SetAttackPosition(Math::vec2 position) { attack_position = position; }
	void GoToBase();
};