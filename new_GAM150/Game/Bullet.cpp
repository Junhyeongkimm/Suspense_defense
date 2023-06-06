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