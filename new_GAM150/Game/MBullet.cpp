#include "MBullet.h"
#include "Mediator.h"
#include "../Engine/Engine.h"
#include <iostream>
MBullet::MBullet(Math::vec2 starat_position, Math::vec2 direction, Mediator* mediator) : position(starat_position), direction(direction), mediator(mediator){

}

void MBullet::Update(double dt) {
	position += direction * speed * dt;

	if (mediator->GetTileState(position) == TILES::WALL ||
		mediator->GetTileState(position) == TILES::COLONY_SIDE ||
		mediator->GetTileState(position) == TILES::RESOURCE ||
		mediator->GetTileState(position) == TILES::WARP) {
		mediator->DeleteMBullet(this);
	}


}

void MBullet::Draw() {
	push_settings();
	set_fill_color(HexColor(0xBBBBBBff));
	draw_ellipse(position.x, position.y, size);
	pop_settings();
}