#include "Player.h"
#include <map>
#include "doodle/input.hpp"
#include "doodle/angle.hpp"
#include "../Engine/Engine.h"
#include "Mediator.h"
using namespace doodle;

#define PRESSED         true
#define NOT_PRESSED     false
#include <iostream>
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

	if (buttons[KeyboardButtons::W]) {
		if ((mediator->GetMapState({ position.x, position.y + size / 2 }) != TILES::WALL) && (mediator->GetMapState({ position.x, position.y + size / 2 }) != TILES::COLONY_SIDE)) {
			position.y += speed * dt;
		}
	}
	if (buttons[KeyboardButtons::S]) {
		if ((mediator->GetMapState({ position.x, position.y - size / 2 }) != TILES::WALL) && (mediator->GetMapState({ position.x, position.y - size / 2 }) != TILES::COLONY_SIDE)) {
			position.y -= speed * dt;
		}
	}
	if (buttons[KeyboardButtons::A]) {
		if ((mediator->GetMapState({ position.x - size / 2, position.y }) != TILES::WALL) && (mediator->GetMapState({ position.x - size / 2, position.y }) != TILES::COLONY_SIDE)) {
			position.x -= speed * dt;
		}
	}
	if (buttons[KeyboardButtons::D]) {
		if ((mediator->GetMapState({ position.x + size / 2, position.y }) != TILES::WALL) && (mediator->GetMapState({ position.x + size / 2, position.y }) != TILES::COLONY_SIDE)) {
			position.x += speed * dt;
		}
	}

	pop_settings();

	attack_count += dt;
	invincibility_count += dt;

	static bool not_clicked = false;

	if (!MouseIsPressed) {
		not_clicked = true;
	}
	if (MouseIsPressed && not_clicked) {
		if (Able_To_Attack()) {
			Attack();
		}
		SetAttackPosition(GetAttackPosition());
		//attack_position = GetAttackPosition();
		//monsters.push_back(new Monster(player->GetAttackPosition(), mediator));
		not_clicked = false;
	}

	// tile_position Update!!
	static const double map_length = mediator->GetMapLength() / mediator->GetMapSize();
	tile_position.x = (int)((position.x) / map_length);
	tile_position.y = (int)((position.y) / map_length);

	if (attack_count > attack_delay) {
		is_attacking = false;
	}

	mediator->CheckPlayerAttacked();

	if (Key == KeyboardButtons::NumPad_1) {
		attack_mode = MELEE;
		std::cout << "Melee mode!" << std::endl;
	}
	else if (Key == KeyboardButtons::NumPad_2) {
		attack_mode = RANGE;
		std::cout << "Range mode!" << std::endl;
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
		set_outline_width(10);
		//draw_line(position.x, position.y, attack_position.x, attack_position.y);
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
	if (attack_mode == MELEE) {
		is_attacking = true;

		mediator->Check_Monster_Attacked();
		mediator->Check_Map_Attacked();
		attack_count = 0;
	}
	else if (attack_mode == RANGE) {
		mediator->AddBullet(position, GetAttackPosition()-position);
	}

}

Math::vec2 Player::GetAttackPosition() {
	double distance = sqrt((get_mouse_x() - Engine::GetWindow().GetSize().x / 2) * (get_mouse_x() - Engine::GetWindow().GetSize().x / 2) + (get_mouse_y() - Engine::GetWindow().GetSize().y / 2) * (get_mouse_y() - Engine::GetWindow().GetSize().y / 2));

	double attack_x_pos = position.x + size * (get_mouse_x() - Engine::GetWindow().GetSize().x / 2) / distance;
	double attack_y_pos = position.y + size * (get_mouse_y() - Engine::GetWindow().GetSize().y / 2) / distance;

	return { attack_x_pos, attack_y_pos };
}

void Player::GoToBase() {
	position = { mediator->GetMapLength() / 2 + size / 2, mediator->GetMapLength() / 2 + size / 2 };
}