#include "Player.h"
#include <map>
#include "doodle/input.hpp"
#include "doodle/angle.hpp"
#include "../Engine/Engine.h"
#include "Mediator.h"
using namespace doodle;

// Constructor
Player::Player(Math::vec2 start_position, const CS230::Camera& camera, Mediator* mediator, Math::ivec2 tile_position) : position(start_position), camera(camera), mediator(mediator), tile_position(tile_position) {
	
}
// Update
void Player::Update(double dt) {
	// Increase attack_count and invincibility_count, dodge_count by dt
	attack_count += dt;
	invincibility_count += dt;
	dodge_count += dt;
	// Check click
	static bool not_clicked = false;
	if (!MouseIsPressed) {
		not_clicked = true;
	}
	if (MouseIsPressed && not_clicked) { // When the player click the mouse
		if (Able_To_Attack()) { // If the player is able to attack, attack
			Attack();
		}
		SetAttackPosition(GetAttackPosition());
		not_clicked = false;
	}
	if (attack_count > attack_delay) {
		is_attacking = false;
	}
	// Change the attack mode by 'Tab'
	if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Tab)) {
		if (attack_mode == MELEE)
			attack_mode = RANGE;
		else
			attack_mode = MELEE;
	}
	// Player warp
	if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::B) && mediator->GetMapState(position) != TILES::BASE_INSIDE && warp_resource > 0) {
		is_warping = true;
	}
	if (is_warping) {
		warp_count += dt;
		if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::W) || Engine::GetInput().KeyJustPressed(CS230::Input::Keys::A) || Engine::GetInput().KeyJustPressed(CS230::Input::Keys::S) || Engine::GetInput().KeyJustPressed(CS230::Input::Keys::D)) {
			warp_count = 0;
			is_warping = false;
		}
		if (warp_count >= warp_time) {
			warp_count = 0;
			GoToBase();
			--warp_resource;
			is_warping = false;
		}
	}
	// Player dodge
	if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Space) && dodge_count >= dodge_time) {
		is_dodging = true;
		dodge_count = 0;
		dodge_direction = { 0, 0 };
		if (Engine::GetInput().KeyDown(CS230::Input::Keys::W)) {
			dodge_direction.y += 1;
		}
		if (Engine::GetInput().KeyDown(CS230::Input::Keys::S)) {
			dodge_direction.y -= 1;
		}
		if (Engine::GetInput().KeyDown(CS230::Input::Keys::A)) {
			dodge_direction.x -= 1;
		}
		if (Engine::GetInput().KeyDown(CS230::Input::Keys::D)) {
			dodge_direction.x += 1;
		}
	}
	if (is_dodging) {
		invincibility_count = 0;
		// Check collision while dodging
		if ((mediator->GetMapState({ position.x + dodge_direction.x * size / 2, position.y + dodge_direction.y * size / 2 }) != TILES::WALL) &&
			(mediator->GetMapState({ position.x + dodge_direction.x * size / 2, position.y + dodge_direction.y * size / 2 }) != TILES::COLONY_SIDE)) {
			position += dodge_direction * 2 * speed * dt;
		}
		if (dodge_count >= dodge_time) {
			dodge_count = 0;
			is_dodging = false;
		}
	}
	else {
		// Player moving with W, A, S, D
		if (Engine::GetInput().KeyDown(CS230::Input::Keys::W)) {
			if ((mediator->GetMapState({ position.x, position.y + size / 2 }) != TILES::WALL) && (mediator->GetMapState({ position.x, position.y + size / 2 }) != TILES::COLONY_SIDE)) {
				position.y += speed * dt;
			}
		}
		if (Engine::GetInput().KeyDown(CS230::Input::Keys::S)) {
			if ((mediator->GetMapState({ position.x, position.y - size / 2 }) != TILES::WALL) && (mediator->GetMapState({ position.x, position.y - size / 2 }) != TILES::COLONY_SIDE)) {
				position.y -= speed * dt;
			}
		}
		if (Engine::GetInput().KeyDown(CS230::Input::Keys::A)) {
			if ((mediator->GetMapState({ position.x - size / 2, position.y }) != TILES::WALL) && (mediator->GetMapState({ position.x - size / 2, position.y }) != TILES::COLONY_SIDE)) {
				position.x -= speed * dt;
			}
		}
		if (Engine::GetInput().KeyDown(CS230::Input::Keys::D)) {
			if ((mediator->GetMapState({ position.x + size / 2, position.y }) != TILES::WALL) && (mediator->GetMapState({ position.x + size / 2, position.y }) != TILES::COLONY_SIDE)) {
				position.x += speed * dt;
			}
		}
	}
	// Tile_position update based on the player's position
	static const double map_length = mediator->GetMapLength() / mediator->GetMapSize();
	tile_position.x = (int)((position.x) / map_length);
	tile_position.y = (int)((position.y) / map_length);
	// Check player attacked
	mediator->CheckPlayerAttacked();
}
// Draw player
void Player::Draw() {
	push_settings();
	set_fill_color(HexColor(0x888888ff));
	draw_ellipse(position.x, position.y, size, size);
	pop_settings();
	// If the player is attacking, draw the line (in the MELEE mode)
	if (is_attacking == true && attack_mode == MELEE) {
		push_settings();
		set_outline_width(10);
		//draw_line(position.x, position.y, attack_position.x, attack_position.y);
		draw_line(position.x, position.y, GetAttackPosition().x, GetAttackPosition().y);
		pop_settings();
	}
}
// Reduce hp
void Player::Reduce_hp() {
	if (invincibility_count > invincibility_time) {
		--hp;
		invincibility_count = 0;
	}
}
// Get distacne from the player to the target
double Player::GetDistanceFromAttack(Math::vec2 target) {
	return sqrt((GetAttackPosition().x - target.x) * (GetAttackPosition().x - target.x) + (GetAttackPosition().y - target.y) * (GetAttackPosition().y - target.y));
}
// Attack function
void Player::Attack() {
	if (attack_mode == MELEE) {
		is_attacking = true;
		mediator->Check_Monster_Attacked();
		mediator->Check_Map_Attacked();
		attack_count = 0;
	}
	else if (attack_mode == RANGE) {
		is_attacking = true;
		attack_count = 0;
		mediator->AddBullet(position, GetAttackPosition()-position);
	}

}
// Get the attack position
Math::vec2 Player::GetAttackPosition() {
	double distance = sqrt((get_mouse_x() - Engine::GetWindow().GetSize().x / 2) * (get_mouse_x() - Engine::GetWindow().GetSize().x / 2) + (get_mouse_y() - Engine::GetWindow().GetSize().y / 2) * (get_mouse_y() - Engine::GetWindow().GetSize().y / 2));

	double attack_x_pos = position.x + size * (get_mouse_x() - Engine::GetWindow().GetSize().x / 2) / distance;
	double attack_y_pos = position.y + size * (get_mouse_y() - Engine::GetWindow().GetSize().y / 2) / distance;

	return { attack_x_pos, attack_y_pos };
}
// Warp to the base
void Player::GoToBase() {
	position = { mediator->GetMapLength() / 2 + size / 2, mediator->GetMapLength() / 2 + size / 2 };
}