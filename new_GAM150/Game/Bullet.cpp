#include "Bullet.h"
#include "Mediator.h"
#include "../Engine/Engine.h"


void Bullet::SetWantScale(Math::vec2 new_scale)
{

	Math::ivec2 want = sprite.GetFrameSize();
	scale_x = 1 / static_cast<double>(want.x) * new_scale.x;
	scale_y = 1 / static_cast<double>(want.y) * new_scale.y;
}
// Constructor
Bullet::Bullet(Math::vec2 start_position, Math::vec2 direction, Mediator* mediator) : position(start_position), direction(direction), mediator(mediator) {
	sprite.Load("Assets/bullet.spt");
	
	SetWantScale({ 125,125 });
	sprite.PlayAnimation(static_cast<int>(bullet::None));
}
// Update
void Bullet::Update(double dt) {
	// Update position
	Move(dt);

	// Check collision with tiles
	if (mediator->GetMap()->GetTileState(position) == TILES::WALL ||
		mediator->GetMap()->GetTileState(position) == TILES::COLONY_SIDE ||
		mediator->GetMap()->GetTileState(position) == TILES::RESOURCE ||
		mediator->GetMap()->GetTileState(position) == TILES::WARP) {
		mediator->DeleteBullet(this);
		return;
	}
}
// Move
void Bullet::Move(double dt) {
	position += direction * speed * dt;
}
// Draw bullet
void Bullet::Draw() {
	sprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ scale_x, scale_y })));
	/*push_settings();
	set_fill_color(HexColor(0x888888ff));
	draw_ellipse(position.x, position.y, size, size);
	pop_settings();*/

}

HomingShot::HomingShot(Math::vec2 start_positon, Math::vec2 direction, Mediator* mediator) : Bullet(start_positon, direction, mediator), target(nullptr) {
	if (mediator->GetMonster()->size()) {
		target = mediator->GetMonster()->front();
		double distance = GetDistance(target->GetPosition());

		for (auto monster : *mediator->GetMonster()) {
			if (GetDistance(monster->GetPosition()) < distance) {
				distance = GetDistance(monster->GetPosition());
				target = monster;
			}
		}
	}
}
void HomingShot::Move(double dt) {
	if (mediator->GetMonster()->size()) {
		direction = target->GetPosition() - position;
		direction /= direction.GetLength();
	}
	position += direction * speed * dt;
}