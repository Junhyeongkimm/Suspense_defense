#include "Player.h"
#include <map>
#include "doodle/input.hpp"
#include "doodle/angle.hpp"
#include "../Engine/Engine.h"
#include "Mediator.h"
using namespace doodle;

#define PRESSED         true
#define NOT_PRESSED     false

std::map<KeyboardButtons, bool> buttons = {
	{ KeyboardButtons::W, NOT_PRESSED },
	{ KeyboardButtons::S, NOT_PRESSED },
	{ KeyboardButtons::A, NOT_PRESSED },
	{ KeyboardButtons::D, NOT_PRESSED },
};

void on_key_pressed(KeyboardButtons button) {
	buttons[button] = PRESSED;
}

void on_key_released(KeyboardButtons button) {
	buttons[button] = NOT_PRESSED;
}

Player::Player(Math::vec2 start_position, const CS230::Camera& camera, Mediator* mediator, Math::ivec2 tile_position) : position(start_position), camera(camera), mediator(mediator), tile_position(tile_position) {
	
}

void Player::Update(double dt) {
	push_settings();
	//apply_rotate(-QUARTER_PI);

	/*if (buttons[KeyboardButtons::W]) {
		position.y += speed * dt;
		position.x += speed * dt * (1 / sqrt(2));
	}
	if (buttons[KeyboardButtons::S]) {
		position.y -= speed * dt;
		position.x -= speed * dt * (1 / sqrt(2));
	}
	if (buttons[KeyboardButtons::A]) {
		position.x -= speed * dt;
		position.y += speed * dt * (1 / sqrt(2));
	}
	if (buttons[KeyboardButtons::D]) {
		position.x += speed * dt;
		position.y -= speed * dt * (1 / sqrt(2));
	}*/

	if (buttons[KeyboardButtons::W] && (mediator->GetMapState({ position.x, position.y + size / 2 }) != TILES::WALL) && mediator->GetMapState({ position.x, position.y + size / 2 }) != TILES::COLONY_SIDE) {
		position.y += speed * dt;
	}
	if (buttons[KeyboardButtons::S] && (mediator->GetMapState({ position.x, position.y - size / 2 }) != TILES::WALL) &&(mediator->GetMapState({ position.x, position.y - size / 2 }) != TILES::COLONY_SIDE)) {
		position.y -= speed * dt;
	}
	if (buttons[KeyboardButtons::A] && (mediator->GetMapState({ position.x - size / 2, position.y }) != TILES::WALL) && (mediator->GetMapState({ position.x - size / 2, position.y }) != TILES::COLONY_SIDE)) {
		position.x -= speed * dt;
	}
	if (buttons[KeyboardButtons::D] && (mediator->GetMapState({ position.x + size / 2, position.y }) != TILES::WALL) && (mediator->GetMapState({ position.x + size / 2, position.y }) != TILES::COLONY_SIDE)) {
		position.x += speed * dt;
	}
	pop_settings();

	attack_count += dt;
	invincibility_count += dt;


	// tile_position Update!!
	static const double map_length = 15000 / 300;
	tile_position.x = (int)((position.x) / map_length);
	tile_position.y = (int)((position.y) / map_length);

	if (attack_count > attack_delay) {
		is_attacking = false;
	}
}

void Player::Draw() {
	push_settings();
	//apply_translate(-position.x + Engine::GetWindow().GetSize().x / 2, -position.y + Engine::GetWindow().GetSize().y / 2);
	set_fill_color(HexColor(0x888888ff));
	draw_ellipse(position.x, position.y, size, size);
	pop_settings();
	
	if (is_attacking == true) {
		push_settings();
		set_outline_width(100);
		draw_line(position.x, position.y, GetAttackPosition().x, GetAttackPosition().y);

		pop_settings();
	}
	
}

void Player::Reduce_hp() {
	if (invincibility_count > invincibility_time) {
		--hp;
		invincibility_count = 0;
	}
}

double Player::GetDistanceFromAttack(Math::vec2 target) {
	return sqrt((GetAttackPosition().x - target.x) * (GetAttackPosition().x - target.x) + (GetAttackPosition().y - target.y) * (GetAttackPosition().y - target.y));
}

void Player::Attack() {
	is_attacking = true;
	attack_position = GetAttackPosition();

	mediator->Check_Monster_Attacked();
	mediator->Check_Map_Attacked();

	attack_count = 0;
}

Math::vec2 Player::GetAttackPosition() {
	double distance = sqrt((get_mouse_x() - Engine::GetWindow().GetSize().x / 2) * (get_mouse_x() - Engine::GetWindow().GetSize().x / 2) + (get_mouse_y() - Engine::GetWindow().GetSize().y / 2) * (get_mouse_y() - Engine::GetWindow().GetSize().y / 2));

	double attack_x_pos = position.x + size * (get_mouse_x() - Engine::GetWindow().GetSize().x / 2) / distance;
	double attack_y_pos = position.y + size * (get_mouse_y() - Engine::GetWindow().GetSize().y / 2) / distance;

	return { attack_x_pos, attack_y_pos };
}