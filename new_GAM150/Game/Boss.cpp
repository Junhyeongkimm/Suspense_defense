#include "Boss.h"
#include <doodle/doodle.hpp>
#include "Mediator.h"
#include "MBullet.h"
using namespace doodle;

// --------------------------------- BOSS  ---------------------------------
Boss::Boss(int max_hp, double speed, Math::vec2 position, double size, double time1, double time2, double time3, int loop1, int loop2, int loop3, Mediator* mediator) :
	max_hp(max_hp), speed(speed), position(position), size(size), 
	pattern1_cool(time1), pattern2_cool(time2), pattern3_cool(time3), 
	pattern1_loop(loop1), pattern2_loop(loop2), pattern3_loop(loop3), mediator(mediator) {
	hp = max_hp;
}
void Boss::Update(double dt) {
	// Boss dead
	if (hp <= 0) {
		mediator->GetMap()->IncreaseBossCount();
		mediator->DeleteBoss(this);
		return;
	}
	Math::ivec2 tile_position = { (int)position.x / (int)mediator->GetMap()->Get_Tile_Length(), (int)position.y / (int)mediator->GetMap()->Get_Tile_Length() };
	Math::ivec2 player_tile = mediator->GetPlayer()->GetTilePosition();
	// If player is far from boss
   //if (mediator->GetPlayer()->GetDistance(position) > mediator->GetMap()->Get_Tile_Length() * 5)
	if (!(player_tile.x >= tile_position.x - 5 && player_tile.x <= tile_position.x + 5 && 
		  player_tile.y >= tile_position.y - 5 && player_tile.y <= tile_position.y + 5)) {
		heal_count += dt;
		// If the hp is not max, heal
		if (hp < max_hp && heal_count >= heal_time) {
			++hp;
			heal_count = 0;
		}
		// If the hp is full, do not call the update function
		return;
	}

	// Pattern update
	pattern_count += dt;
	switch (pattern_index) {
	case 1:
		if (pattern_count >= pattern1_cool / pattern1_loop) {
			pattern_count = 0;
			Pattern1();
			++loop_count;
			if (loop_count == pattern1_loop) {
				loop_count = 0;
				++pattern_index;
			}
		}
		break;
	case 2:
		if (pattern_count >= pattern2_cool / pattern2_loop) {
			pattern_count = 0;
			Pattern2();
			++loop_count;
			if (loop_count == pattern2_loop) {
				loop_count = 0;
				++pattern_index;
			}
		}
		break;
	case 3:
		if (pattern_count >= pattern3_cool / pattern3_loop) {
			pattern_count = 0;
			Pattern3();
			++loop_count;
			if (loop_count == pattern3_loop) {
				loop_count = 0;
				pattern_index = 1;
			}
		}
		break;
	}
}
void Boss::Draw() {

}

// --------------------------------- BOSS 1 ---------------------------------
Boss1::Boss1(Math::vec2 position, Mediator* mediator) :
	Boss(max_hp = 20, speed = 300, position, size = 100, pattern1_cool = 0.5, pattern2_cool = 0.5, pattern3_cool = 0.5, 5, 3, 2, mediator) {
}
void Boss1::Draw() {
	push_settings();
	draw_ellipse(position.x, position.y, size);
	set_fill_color(HexColor(0x888888ff));
	draw_rectangle(position.x - size / 2, position.y - size / 2 - size / 10, size, size / 10);
	set_fill_color(HexColor(0x444444ff));
	draw_rectangle(position.x - size / 2, position.y - size / 2 - size / 10, ((double)hp / max_hp) * size, size / 10);

	pop_settings();
}
void Boss1::Pattern1() {
	Math::vec2 direct = mediator->GetPlayer()->GetPosition() - position;
	direct /= direct.GetLength();

	mediator->AddMBullet(position, direct, BulletState::NORMAL);
}
void Boss1::Pattern2() {
	mediator->AddMBullet(position, Math::vec2{  1,  0 }, BulletState::NORMAL);
	mediator->AddMBullet(position, Math::vec2{  1,  1 }, BulletState::NORMAL);
	mediator->AddMBullet(position, Math::vec2{  0,  1 }, BulletState::NORMAL);
	mediator->AddMBullet(position, Math::vec2{ -1,  1 }, BulletState::NORMAL);
	mediator->AddMBullet(position, Math::vec2{ -1,  0 }, BulletState::NORMAL);
	mediator->AddMBullet(position, Math::vec2{ -1, -1 }, BulletState::NORMAL);
	mediator->AddMBullet(position, Math::vec2{  0, -1 }, BulletState::NORMAL);
	mediator->AddMBullet(position, Math::vec2{  1, -1 }, BulletState::NORMAL);
}
void Boss1::Pattern3() {
	mediator->AddMonster(position, true);
}

// --------------------------------- BOSS 2 ---------------------------------
Boss2::Boss2(Math::vec2 position, Mediator* mediator) : 
	Boss(max_hp = 20, speed = 300, position, size = 100, pattern1_cool = 0.5, pattern2_cool = 0.5, pattern3_cool = 0.5, 5, 2, 3, mediator) {

}
void Boss2::Draw() {
	push_settings();
	draw_ellipse(position.x, position.y, size);
	set_fill_color(HexColor(0x888888ff));
	draw_rectangle(position.x - size / 2, position.y - size / 2 - size / 10, size, size / 10);
	set_fill_color(HexColor(0x444444ff));
	draw_rectangle(position.x - size / 2, position.y - size / 2 - size / 10, ((double)hp / max_hp) * size, size / 10);

	pop_settings();
}
void Boss2::Pattern1() {
	Math::vec2 direct = mediator->GetPlayer()->GetPosition() - position;
	direct /= direct.GetLength();

	mediator->AddMBullet(position, direct, BulletState::STRONG);
}
void Boss2::Pattern2() {
	mediator->AddMBullet(position, Math::vec2{ 1,  0 }, BulletState::FAST);
	mediator->AddMBullet(position, Math::vec2{ 1,  1 }, BulletState::FAST);
	mediator->AddMBullet(position, Math::vec2{ 0,  1 }, BulletState::FAST);
	mediator->AddMBullet(position, Math::vec2{ -1,  1 }, BulletState::FAST);
	mediator->AddMBullet(position, Math::vec2{ -1,  0 }, BulletState::FAST);
	mediator->AddMBullet(position, Math::vec2{ -1, -1 }, BulletState::FAST);
	mediator->AddMBullet(position, Math::vec2{ 0, -1 }, BulletState::FAST);
	mediator->AddMBullet(position, Math::vec2{ 1, -1 }, BulletState::FAST);
}
void Boss2::Pattern3() {
	mediator->AddMonster(position, true);
}
// --------------------------------- BOSS 3 ---------------------------------
Boss3::Boss3(Math::vec2 position, Mediator* mediator) : 
	Boss(max_hp = 20, speed = 300, position, size = 100, pattern1_cool = 0.5, pattern2_cool = 0.5, pattern3_cool = 0.5, 5, 2, 3, mediator) {

}
void Boss3::Draw() {
	push_settings();
	draw_ellipse(position.x, position.y, size);
	set_fill_color(HexColor(0x888888ff));
	draw_rectangle(position.x - size / 2, position.y - size / 2 - size / 10, size, size / 10);
	set_fill_color(HexColor(0x444444ff));
	draw_rectangle(position.x - size / 2, position.y - size / 2 - size / 10, ((double)hp / max_hp) * size, size / 10);

	pop_settings();
}
void Boss3::Pattern1() {
	Math::vec2 direct = mediator->GetPlayer()->GetPosition() - position;
	direct /= direct.GetLength();

	mediator->AddMBullet(position, direct, BulletState::BIG);
}
void Boss3::Pattern2() {
	mediator->AddMBullet(position, Math::vec2{ 1,  0 }, BulletState::BIG);
	mediator->AddMBullet(position, Math::vec2{ 1,  1 }, BulletState::BIG);
	mediator->AddMBullet(position, Math::vec2{ 0,  1 }, BulletState::BIG);
	mediator->AddMBullet(position, Math::vec2{ -1,  1 }, BulletState::BIG);
	mediator->AddMBullet(position, Math::vec2{ -1,  0 }, BulletState::BIG);
	mediator->AddMBullet(position, Math::vec2{ -1, -1 }, BulletState::BIG);
	mediator->AddMBullet(position, Math::vec2{ 0, -1 }, BulletState::BIG);
	mediator->AddMBullet(position, Math::vec2{ 1, -1 }, BulletState::BIG);
}
void Boss3::Pattern3() {
	mediator->AddMonster(position, true);
}
// --------------------------------- BOSS 4 ---------------------------------
Boss4::Boss4(Math::vec2 position, Mediator* mediator) : 
	Boss(max_hp = 20, speed = 300, position, size = 100, pattern1_cool = 0.5, pattern2_cool = 0.5, pattern3_cool = 0.5, 5, 2, 3, mediator) {

}
void Boss4::Draw() {
	push_settings();
	draw_ellipse(position.x, position.y, size);
	set_fill_color(HexColor(0x888888ff));
	draw_rectangle(position.x - size / 2, position.y - size / 2 - size / 10, size, size / 10);
	set_fill_color(HexColor(0x444444ff));
	draw_rectangle(position.x - size / 2, position.y - size / 2 - size / 10, ((double)hp / max_hp) * size, size / 10);

	pop_settings();
}
void Boss4::Pattern1() {
	Math::vec2 direct = mediator->GetPlayer()->GetPosition() - position;
	direct /= direct.GetLength();

	mediator->AddMBullet(position, direct, BulletState::HOMING);
}
void Boss4::Pattern2() {
	mediator->AddMBullet(position, Math::vec2{ 1,  0 }, BulletState::RICOCHET);
	mediator->AddMBullet(position, Math::vec2{ 1,  1 }, BulletState::RICOCHET);
	mediator->AddMBullet(position, Math::vec2{ 0,  1 }, BulletState::RICOCHET);
	mediator->AddMBullet(position, Math::vec2{ -1,  1 }, BulletState::RICOCHET);
	mediator->AddMBullet(position, Math::vec2{ -1,  0 }, BulletState::RICOCHET);
	mediator->AddMBullet(position, Math::vec2{ -1, -1 }, BulletState::RICOCHET);
	mediator->AddMBullet(position, Math::vec2{ 0, -1 }, BulletState::RICOCHET);
	mediator->AddMBullet(position, Math::vec2{ 1, -1 }, BulletState::RICOCHET);
}
void Boss4::Pattern3() {
	mediator->AddMonster(position, true);
}