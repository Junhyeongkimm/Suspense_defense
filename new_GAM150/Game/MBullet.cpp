#include "MBullet.h"
#include "Mediator.h"
#include "../Engine/Engine.h"


// ------------------------------------------------ Basic Bullet ------------------------------------------------
MBullet::MBullet(Math::vec2 start_position, Math::vec2 direction, Mediator* mediator, double speed, double size, int damage) 
	: position(start_position), direction(direction), mediator(mediator), speed(speed), size(size), damage(damage) {
	boss1bullet.Load("Assets/boss1bullet.spt");
	boss2bullet.Load("Assets/boss2bullet.spt");
	boss3bullet.Load("Assets/boss3bullet.spt");
	boss4bullet.Load("Assets/boss4bullet.spt");

	scale_x = size / static_cast<double>(boss1bullet.GetFrameSize().x);
	scale_y = size / static_cast<double>(boss1bullet.GetFrameSize().y);

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
	boss1bullet.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ scale_x, scale_y })));
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
Strong::Strong(Math::vec2 start_position, Math::vec2 direction, Mediator* mediator) : MBullet(start_position, direction, mediator, 400, 20, 2) {

}
// Fast
Fast::Fast(Math::vec2 start_position, Math::vec2 direction, Mediator* mediator) : MBullet(start_position, direction, mediator, 800, 20, 1) {

}
// Big
Big::Big(Math::vec2 start_position, Math::vec2 direction, Mediator* mediator) : MBullet(start_position, direction, mediator, 300, 40, 3) {

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