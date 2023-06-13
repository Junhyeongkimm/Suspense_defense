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

	tile_position = { (int)position.x / (int)mediator->GetMap()->Get_Tile_Length(), (int)position.y / (int)mediator->GetMap()->Get_Tile_Length() };
}
void Boss::Update(double dt) {
	Math::ivec2 player_tile = mediator->GetPlayer()->GetTilePosition();
	// If player is far from boss
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
		if (pattern_count >= pattern1_cool / (double)pattern1_loop) {
			pattern_count = 0;
			Pattern1();
			++loop_count;
			if (loop_count == pattern1_loop) {
				loop_count = 0;
				index_save = ++pattern_index;
				pattern_index = 4;
			}
		}
		break;
	case 2:
		if (pattern_count >= pattern2_cool / (double)pattern2_loop) {
			pattern_count = 0;
			Pattern2();
			++loop_count;
			if (loop_count == pattern2_loop) {
				loop_count = 0;
				index_save = ++pattern_index;
				pattern_index = 4;
			}
		}
		break;
	case 3:
		if (pattern_count >= pattern3_cool / (double)pattern3_loop) {
			pattern_count = 0;
			Pattern3();
			++loop_count;
			if (loop_count == pattern3_loop) {
				loop_count = 0;
				index_save = 1;
				pattern_index = 4;
			}
		}
		break;
	case 4:
		if (pattern_count >= pattern_donothing) {
			pattern_index = index_save;
		}
		break;
	}
}
void Boss::Draw() {

}

// --------------------------------- BOSS 1 ---------------------------------
Boss1::Boss1(Math::vec2 position, Mediator* mediator) :
	Boss(max_hp = 15, speed = 300, position, size = 100, pattern1_cool = 0.5, pattern2_cool = 0.5, pattern3_cool = 0.5, 3, 2, 1, mediator) {
	boss1sprite.Load("Assets/Boss1.spt");
	
	scale_x = size / static_cast<double>(boss1sprite.GetFrameSize().x);
	scale_y = size / static_cast<double>(boss1sprite.GetFrameSize().y);
	boss1sprite.PlayAnimation(static_cast<int>(Boss1_animations::basic));
}
void Boss1::Draw() {

	boss1sprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ scale_x, scale_y })));
	push_settings();
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
	Boss(max_hp = 20, speed = 300, position, size = 100, pattern1_cool = 0.5, pattern2_cool = 0.5, pattern3_cool = 0.5, 5, 3, 2, mediator) {
	boss2sprite.Load("Assets/Boss2.spt");
	boss2bullet.Load("Assets/boss2bullet.spt");
	scale_x = size / static_cast<double>(boss2sprite.GetFrameSize().x);
	scale_y = size / static_cast<double>(boss2sprite.GetFrameSize().y);
	boss2sprite.PlayAnimation(static_cast<int>(Boss2_animations::basic));
}
void Boss2::Draw() {
	boss2sprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ scale_x, scale_y })));
	push_settings();
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
	Boss(max_hp = 30, speed = 300, position, size = 100, pattern1_cool = 0.5, pattern2_cool = 0.5, pattern3_cool = 0.5, 7, 4, 3, mediator) {
	boss3sprite.Load("Assets/Boss3.spt");
	boss3bullet.Load("Assets/boss3bullet.spt");
	scale_x = size / static_cast<double>(boss3sprite.GetFrameSize().x);
	scale_y = size / static_cast<double>(boss3sprite.GetFrameSize().y);
	boss3sprite.PlayAnimation(static_cast<int>(Boss3_animations::basic));
}
void Boss3::Draw() {
	boss3sprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ scale_x, scale_y })));
	push_settings();
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
	Boss(max_hp = 50, speed = 300, position, size = 100, pattern1_cool = 0.5, pattern2_cool = 0.5, pattern3_cool = 0.5, 10, 5, 5, mediator) {
	boss4sprite.Load("Assets/Boss4.spt");
	boss4bullet.Load("Assets/boss4bullet.spt");
	scale_x = size / static_cast<double>(boss4sprite.GetFrameSize().x);
	scale_y = size / static_cast<double>(boss4sprite.GetFrameSize().y);
	boss4sprite.PlayAnimation(static_cast<int>(Boss4_animations::basic));
}
void Boss4::Draw() {
	boss4sprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ scale_x, scale_y })));
	push_settings();
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