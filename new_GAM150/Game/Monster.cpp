#include "Monster.h"
#include "Mediator.h"

Monster::Monster(Math::vec2 position, Mediator* mediator) : position(position), mediator(mediator) {

}

void Monster::Update(double dt, Math::vec2 target) {

	double x_direction = (target.x - position.x) / GetDistance(target);
	double y_direction = (target.y - position.y) / GetDistance(target);

	// 몬스터 크기의 절반을 미리 계산해둡니다.
	double half_size = size / 2.0;

	// 몬스터가 이동할 위치를 미리 계산합니다.
	Math::vec2 next_position_x = { position.x + speed * dt * x_direction, position.y };
	Math::vec2 next_position_y = { position.x, position.y + speed * dt * y_direction };

	// 벽과 충돌하는 경우는 움직이지 않습니다.
	bool can_move_x = (
		mediator->GetMapState({ next_position_x.x - half_size, next_position_x.y }) != TILES::WALL &&
		mediator->GetMapState({ next_position_x.x + half_size, next_position_x.y }) != TILES::WALL &&
		mediator->GetMapState({ next_position_x.x - half_size, next_position_x.y }) != TILES::BASE_WALL &&
		mediator->GetMapState({ next_position_x.x + half_size, next_position_x.y }) != TILES::BASE_WALL);

	bool can_move_y = (
		mediator->GetMapState({ next_position_y.x, next_position_y.y - half_size }) != TILES::WALL &&
		mediator->GetMapState({ next_position_y.x, next_position_y.y + half_size }) != TILES::WALL &&
		mediator->GetMapState({ next_position_y.x, next_position_y.y - half_size }) != TILES::BASE_WALL &&
		mediator->GetMapState({ next_position_y.x, next_position_y.y + half_size }) != TILES::BASE_WALL);

	if (can_move_x) {
		position.x = next_position_x.x;
	}

	if (can_move_y) {
		position.y = next_position_y.y;
	}

	//position += speed * dt * Math::vec2({ x_direction, y_direction });

	

	/*if ((mediator->GetMapState({ position.x, position.y + size / 2 }) == TILES::WALL) || mediator->GetMapState({ position.x, position.y + size / 2 }) == TILES::COLONY_SIDE) {
		position.y -= speed * dt;
	}
	if ((mediator->GetMapState({ position.x, position.y - size / 2 }) == TILES::WALL) || (mediator->GetMapState({ position.x, position.y - size / 2 }) == TILES::COLONY_SIDE)) {
		position.y += speed * dt;
	}
	if ((mediator->GetMapState({ position.x - size / 2, position.y }) == TILES::WALL) || (mediator->GetMapState({ position.x - size / 2, position.y }) == TILES::COLONY_SIDE)) {
		position.x += speed * dt;
	}
	if ((mediator->GetMapState({ position.x + size / 2, position.y }) == TILES::WALL) || (mediator->GetMapState({ position.x + size / 2, position.y }) == TILES::COLONY_SIDE)) {
		position.x -= speed * dt;
	}
	position.x += speed * dt;
	position.x -= speed * dt;
	position.y -= speed * dt;
	position.y += speed * dt;*/
}

void Monster::Move(Math::vec2 target, double dt) {
}

void Monster::Draw() {
	push_settings();
	set_fill_color(HexColor(0x888888ff));
	draw_ellipse(position.x, position.y, size);
	pop_settings();
}

double Monster::GetDistance(Math::vec2 target) {
	return sqrt((position.x - target.x) * (position.x - target.x) + (position.y - target.y) * (position.y - target.y));
}

void Monster::Reduce_hp() {
	--hp;
}
#include <iostream>
void Monster::Attacked(Math::vec2 attack_position) {
	if (GetDistance(attack_position) < size / 2) {
		Reduce_hp();
		std::cout << "attacked!\n";

		if (hp <= 0) {
			mediator->IncreaseMonsterResource();
			mediator->DeleteMonster(this);
		}
	}
}

Monster::~Monster() {

}