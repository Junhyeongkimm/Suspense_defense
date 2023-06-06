#include "MBullet.h"
#include "Mediator.h"
#include "../Engine/Engine.h"

MBullet::MBullet(Math::vec2 start_position, Math::vec2 direction, Mediator* mediator) : position(start_position), direction(direction), mediator(mediator){

}

void MBullet::Update(double dt) {
	// Update position
	position += direction * speed * dt;
}

void MBullet::Draw() {
	push_settings();
	set_fill_color(HexColor(0xBBBBBBff));
	draw_ellipse(position.x, position.y, size);
	pop_settings();
}