#include "Bullet.h"
#include "Mediator.h"
#include "../Engine/Engine.h"

Bullet::Bullet(Math::vec2 start_positon, Math::vec2 direction, Mediator* mediator) : positoin(start_positon), direction(direction), mediator(mediator) {

}

void Bullet::Update(double dt) {

}

bool Bullet::IsOutOfScreen() {
	return true;
}