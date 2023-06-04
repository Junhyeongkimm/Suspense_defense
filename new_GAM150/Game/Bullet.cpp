#include "Bullet.h"
#include "Mediator.h"
#include "../Engine/Engine.h"

// Constructor
Bullet::Bullet(Math::vec2 start_position, Math::vec2 direction, Mediator* mediator) : position(start_position), direction(direction), mediator(mediator) {

}
// Update
void Bullet::Update(double dt) {
	// Update position
	position += direction * speed * dt;
	// Check collision with Wall
	if (mediator->GetTileState(position) == TILES::WALL ||
		mediator->GetTileState(position) == TILES::COLONY_SIDE ||
		mediator->GetTileState(position) == TILES::RESOURCE ||
		mediator->GetTileState(position) == TILES::WARP) {
		mediator->DeleteBullet(this);
	}
}
// Draw bullet
void Bullet::Draw() {
	push_settings();
	set_fill_color(HexColor(0x888888ff));
	draw_ellipse(position.x, position.y, size, size);
	pop_settings();

}