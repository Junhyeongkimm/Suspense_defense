#include "MBullet.h"
#include "Mediator.h"
#include "../Engine/Engine.h"


// ------------------------------------------------ Basic Bullet ------------------------------------------------
MBullet::MBullet(Math::vec2 start_position, Math::vec2 direction, Mediator* mediator, double speed, double size, int damage) 
	: position(start_position), direction(direction), mediator(mediator), speed(speed), size(size), damage(damage) {

}

void MBullet::Update(double dt) {
	// Update position
	Move(dt);
	if (mediator->GetMap()->GetTileState(position) == TILES::WALL ||
		mediator->GetMap()->GetTileState(position) == TILES::COLONY_SIDE ||
		mediator->GetMap()->GetTileState(position) == TILES::RESOURCE ||
		mediator->GetMap()->GetTileState(position) == TILES::WARP) {
		mediator->DeleteMBullet(this);
		return;
	}
	// Check collision with player
	if (GetDistance(mediator->GetPlayer()->GetPosition()) < size) {
		mediator->GetPlayer()->Reduce_hp(damage);
		mediator->DeleteMBullet(this);
		return;
	}
}
void MBullet::Move(double dt) {
	if (direction.GetLength() != 1)
		direction /= direction.GetLength();
	position += direction * speed * dt;
}
void MBullet::Draw() {
	push_settings();
	set_fill_color(HexColor(0xBBBBBBff));
	draw_ellipse(position.x, position.y, size);
	pop_settings();
}
double MBullet::GetDistance(Math::vec2 target) {
	return (position - target).GetLength();
}
// ------------------------------------------------ Other Bullets ------------------------------------------------
// Homing
Homing::Homing(Math::vec2 start_position, Math::vec2 direction, Mediator* mediator) : MBullet(start_position, direction, mediator) {

}
void Homing::Move(double dt) {
	direction = mediator->GetPlayer()->GetPosition() - position;
	direction /= direction.GetLength();

	position += direction * speed * dt;
}
// Strong
Strong::Strong(Math::vec2 start_position, Math::vec2 direction, Mediator* mediator) : MBullet(start_position, direction, mediator, 600, 20, 2) {

}
// Fast
Fast::Fast(Math::vec2 start_position, Math::vec2 direction, Mediator* mediator) : MBullet(start_position, direction, mediator, 1200, 20, 1) {

}
// Big
Big::Big(Math::vec2 start_position, Math::vec2 direction, Mediator* mediator) : MBullet(start_position, direction, mediator, 600, 40, 1) {

}
// Heal
Heal::Heal(Math::vec2 start_position, Math::vec2 direction, Mediator* mediator) : MBullet(start_position, direction, mediator) {

}
void Heal::Update(double dt) {
	// Update position
	Move(dt);
	if (mediator->GetMap()->GetTileState(position) == TILES::WALL ||
		mediator->GetMap()->GetTileState(position) == TILES::COLONY_SIDE ||
		mediator->GetMap()->GetTileState(position) == TILES::RESOURCE ||
		mediator->GetMap()->GetTileState(position) == TILES::WARP) {
		mediator->DeleteMBullet(this);
		return;
	}
	// Check collision with player
	if (GetDistance(mediator->GetPlayer()->GetPosition()) < size) {
		mediator->GetPlayer()->Heal();
		mediator->DeleteMBullet(this);
		return;
	}
}
// Ricochet
Ricochet::Ricochet(Math::vec2 start_position, Math::vec2 direction, Mediator* mediator) : MBullet(start_position, direction, mediator) {

}
void Ricochet::Update(double dt) {
	// Update position
	Move(dt);
	if (mediator->GetMap()->GetTileState(position) == TILES::WALL ||
		mediator->GetMap()->GetTileState(position) == TILES::COLONY_SIDE ||
		mediator->GetMap()->GetTileState(position) == TILES::RESOURCE ||
		mediator->GetMap()->GetTileState(position) == TILES::WARP) {

		if (count <= 0)
			mediator->DeleteMBullet(this);
		else {
			if (abs(direction.x) > abs(direction.y)) {

				direction.x = -direction.x;
			}
			else {

				direction.y = -direction.y;
			}
			--count;
		}

		return;
	}
	// Check collision with player
	if (GetDistance(mediator->GetPlayer()->GetPosition()) < size) {
		mediator->GetPlayer()->Reduce_hp(damage);
		mediator->DeleteMBullet(this);
		return;
	}
}