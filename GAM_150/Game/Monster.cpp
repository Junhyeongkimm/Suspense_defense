#include "Monster.h"
#include "Mediator.h"

Monster::Monster(Math::vec2 position, Mediator* mediator) : position(position), mediator(mediator) {

}

void Monster::Update(double dt, Math::vec2 target) {
	Move(target, dt);


}

void Monster::Move(Math::vec2 target, double dt) {
	double x_direction = (target.x - position.x) / GetDistance(target);
	double y_direction = (target.y - position.y) / GetDistance(target);

	position += speed * dt * Math::vec2(x_direction, y_direction);
}

void Monster::Draw() {
	push_settings();
	set_fill_color(0);
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
			mediator->DeleteMonster(this);
		}
	}
}

Monster::~Monster() {

}