#include "Monster.h"
#include "Mediator.h"

Monster::Monster(Math::vec2 position, Mediator* mediator) : position(position), mediator(mediator) {

}

void Monster::Update(double dt, Math::vec2 target) {

	if (mediator->Is_Day()) {
		double x_direction = (target.x - position.x) / GetDistance(target);
		double y_direction = (target.y - position.y) / GetDistance(target);

		double half_size = size / 2.0;

		Math::vec2 next_position_x = { position.x + speed * dt * x_direction, position.y };
		Math::vec2 next_position_y = { position.x, position.y + speed * dt * y_direction };

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
	}
	else {
		Math::vec2 middle_point{ mediator->GetMapLength() / 2, mediator->GetMapLength() / 2 };

		double x_direction = (middle_point.x - position.x) / GetDistance(middle_point);
		double y_direction = (middle_point.y - position.y) / GetDistance(middle_point);

		double half_size = size / 2.0;

		Math::vec2 next_position_x = { position.x + speed * dt * x_direction, position.y };
		Math::vec2 next_position_y = { position.x, position.y + speed * dt * y_direction };

		bool can_move_x = (
			mediator->GetMapState({ next_position_x.x - half_size, next_position_x.y }) != TILES::BASE_WALL &&
			mediator->GetMapState({ next_position_x.x + half_size, next_position_x.y }) != TILES::BASE_WALL);

		bool can_move_y = (
			mediator->GetMapState({ next_position_y.x, next_position_y.y - half_size }) != TILES::BASE_WALL &&
			mediator->GetMapState({ next_position_y.x, next_position_y.y + half_size }) != TILES::BASE_WALL);

		if (can_move_x) {
			position.x = next_position_x.x;
		}

		if (can_move_y) {
			position.y = next_position_y.y;
		}
	}
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

void Monster::Attacked(Math::vec2 attack_position) {
	if (GetDistance(attack_position) < size / 2) {
		Reduce_hp();

		if (hp <= 0) {
			mediator->IncreaseMonsterResource();
			mediator->DeleteMonster(this);
		}
	}
}

Monster::~Monster() {

}