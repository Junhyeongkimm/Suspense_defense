#include "Monster.h"
#include "Mediator.h"

Monster::Monster(Math::vec2 position, Mediator* mediator) : position(position), mediator(mediator) {

}

void Monster::Update(double dt, Math::vec2 target) {
	//Move(target, dt);

	double x_direction = (target.x - position.x) / GetDistance(target);
	double y_direction = (target.y - position.y) / GetDistance(target);


	/*if ((mediator->GetMapState({ position.x - size / 2, position.y }) != TILES::WALL) && (mediator->GetMapState({ position.x + size / 2, position.y }) != TILES::WALL)) {
		position.x += speed * dt * x_direction;
	}

	if ((mediator->GetMapState({ position.x, position.y - size / 2 }) != TILES::WALL) && (mediator->GetMapState({ position.x, position.y + size / 2 }) != TILES::WALL)) {
		position.y += speed * dt * y_direction;
	}*/

	if ((mediator->GetMapState({ position.x - size / 2, position.y }) == TILES::WALL)
		|| (mediator->GetMapState({ position.x + size / 2, position.y }) == TILES::WALL)
		|| (mediator->GetMapState({ position.x - size / 2, position.y }) == TILES::BASE_WALL)
		|| (mediator->GetMapState({ position.x + size / 2, position.y }) == TILES::BASE_WALL)) {
		position.x -= speed * dt * x_direction;
	}
	if ((mediator->GetMapState({ position.x, position.y - size / 2 }) == TILES::WALL)
		|| (mediator->GetMapState({ position.x, position.y + size / 2 }) == TILES::WALL)
		|| (mediator->GetMapState({ position.x, position.y - size / 2 }) == TILES::BASE_WALL)
		|| (mediator->GetMapState({ position.x, position.y + size / 2 }) == TILES::BASE_WALL)) {
		position.y -= speed * dt * y_direction;
	}
	position += speed * dt * Math::vec2({ x_direction, y_direction });

	

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