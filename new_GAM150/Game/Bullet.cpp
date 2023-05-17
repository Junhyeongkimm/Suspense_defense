#include "Bullet.h"
#include "Mediator.h"
#include "../Engine/Engine.h"

#include <iostream>
Bullet::Bullet(Math::vec2 start_position, Math::vec2 direction, Mediator* mediator) : position(start_position), direction(direction), mediator(mediator) {
	std::cout << "created!" << std::endl;
}

void Bullet::Update(double dt) {
	position += direction * speed * dt;

	if (position.x < mediator->GetPlayerPosition().x - (double)Engine::GetWindow().GetSize().x / 2
		|| position.x > mediator->GetPlayerPosition().x + (double)Engine::GetWindow().GetSize().x / 2
		|| position.y < mediator->GetPlayerPosition().y - (double)Engine::GetWindow().GetSize().y / 2
		|| position.y > mediator->GetPlayerPosition().y + (double)Engine::GetWindow().GetSize().y / 2
		)
	{
		mediator->DeleteBullet(this);
	}


}

void Bullet::Draw() {
	push_settings();
	set_fill_color(HexColor(0));
	draw_ellipse(position.x, position.y, size, size);
	pop_settings();

}
