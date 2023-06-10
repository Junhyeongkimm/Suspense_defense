#include "Boss.h"
#include <doodle/doodle.hpp>
#include "Mediator.h"
#include "MBullet.h"
using namespace doodle;

// --------------------------------- BOSS  ---------------------------------
Boss::Boss(int hp, double speed, Math::vec2 position, double size, double time1, double time2, double time3, Mediator* mediator) : 
	hp(hp), speed(speed), position(position), size(size), pattern1_time(time1), pattern2_time(time2), pattern3_time(time3), mediator(mediator) {

}
void Boss::Update(double dt) {
	pattern_count += dt;
	
	switch (pattern_index) {
	case 1:
		if (pattern_count >= pattern1_time) {
			pattern_count = 0;
			++pattern_index;
			//Pattern1();
		}
		break;
	case 2:
		if (pattern_count >= pattern2_time) {
			pattern_count = 0;
			++pattern_index;
			//Pattern2();
		}
		break;
	case 3:
		if (pattern_count >= pattern3_time) {
			pattern_count = 0;
			pattern_index = 1;
			//Pattern3();
		}
		break;
	}

}
void Boss::Draw() {
	draw_ellipse(position.x, position.y, size);
}

// --------------------------------- BOSS 1 ---------------------------------
Boss1::Boss1(Math::vec2 position, Mediator* mediator) : 
	Boss(hp, speed, position, size, pattern1_time, pattern2_time, pattern3_time, mediator) {

}
void Boss1::Update(double dt) {
	pattern_count += dt;

	switch (pattern_index) {
	case 1:
		if (pattern_count >= pattern1_time) {
			pattern_count = 0;
			++pattern_index;
			Pattern1();
		}
		break;
	case 2:
		if (pattern_count >= pattern2_time) {
			pattern_count = 0;
			++pattern_index;
			Pattern2();
		}
		break;
	case 3:
		if (pattern_count >= pattern3_time) {
			pattern_count = 0;
			pattern_index = 1;
			Pattern3();
		}
		break;
	}
}
void Boss1::Draw() {
	draw_ellipse(position.x, position.y, size);
}
void Boss1::Pattern1() {
	Math::vec2 direct = mediator->GetPlayer()->GetPosition() - position;
	direct /= direct.GetLength();

	mediator->AddMBullet(position, direct, BulletState::FAST);
}
void Boss1::Pattern2() {
	mediator->AddMBullet(position, Math::vec2{  1,  0 }, BulletState::NORMAL);
	mediator->AddMBullet(position, Math::vec2{  1,  1 }, BulletState::FAST);
	mediator->AddMBullet(position, Math::vec2{  0,  1 }, BulletState::NORMAL);
	mediator->AddMBullet(position, Math::vec2{ -1,  1 }, BulletState::FAST);
	mediator->AddMBullet(position, Math::vec2{ -1,  0 }, BulletState::NORMAL);
	mediator->AddMBullet(position, Math::vec2{ -1, -1 }, BulletState::FAST);
	mediator->AddMBullet(position, Math::vec2{  0, -1 }, BulletState::NORMAL);
	mediator->AddMBullet(position, Math::vec2{  1, -1 }, BulletState::FAST);
}
void Boss1::Pattern3() {

	//mediator->AddMonster(position);
}
// --------------------------------- BOSS 2 ---------------------------------
Boss2::Boss2(Math::vec2 position, Mediator* mediator) : 
	Boss(hp, speed, position, size, pattern1_time, pattern2_time, pattern3_time, mediator) {

}
void Boss2::Draw() {
	draw_ellipse(position.x, position.y, size);
}
void Boss2::Pattern1() {

}
void Boss2::Pattern2() {

}
void Boss2::Pattern3() {

}
// --------------------------------- BOSS 3 ---------------------------------
Boss3::Boss3(Math::vec2 position, Mediator* mediator) : 
	Boss(hp, speed, position, size, pattern1_time, pattern2_time, pattern3_time, mediator) {

}
void Boss3::Draw() {
	draw_ellipse(position.x, position.y, size);
}
void Boss3::Pattern1() {

}
void Boss3::Pattern2() {

}
void Boss3::Pattern3() {

}
// --------------------------------- BOSS 4 ---------------------------------
Boss4::Boss4(Math::vec2 position, Mediator* mediator) : 
	Boss(hp, speed, position, size, pattern1_time, pattern2_time, pattern3_time, mediator) {

}
void Boss4::Draw() {
	draw_ellipse(position.x, position.y, size);
}
void Boss4::Pattern1() {

}
void Boss4::Pattern2() {

}
void Boss4::Pattern3() {

}