#include "Player.h"
#include <map>
#include "doodle/input.hpp"
#include "doodle/angle.hpp"
#include "../Engine/Engine.h"
#include "Mediator.h"
#include "State.h"
using namespace doodle;

// Constructor
Player::Player(Math::vec2 start_position, const CS230::Camera& camera, Mediator* mediator, Math::ivec2 tile_position) : position(start_position), camera(camera), mediator(mediator), tile_position(tile_position) {
	//sprite.Load("Assets/player.spt");
	scale_x = size / static_cast<double>(sprite.GetFrameSize().x);
	scale_y = size / static_cast<double>(sprite.GetFrameSize().y);
	sprite.PlayAnimation(static_cast<int>(player_action::waiting));
}
// Update
void Player::Update(double dt) {
	// Increase attack_count and invincibility_count, dodge_count by dt
	attack_count += dt;
	invincibility_count += dt;
	//dodging_count += dt;
	dodge_cool_count += dt;
	// Check click
	static bool not_clicked = false;
	if (!MouseIsPressed) {
		not_clicked = true;
	}
	if (MouseIsPressed && not_clicked) { // When the player click the mouse
		if (Able_To_Attack() && MouseButton == MouseButtons::Left) { // If the player is able to attack and clicked the left button of mouse, attack
			Attack();
		}
		if (dodge_unlocked && MouseButton == MouseButtons::Right && dodge_cool_count >= dodge_cool_time) { // If the player is able to dodge and clicked the right button of mosue, dodge
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
			// If the player move diagonally, divide speed by sqrt(2)
			if (dodge_direction.GetLength() == 0) {
				return;
			}
			else if (dodge_direction.GetLength() == sqrt(2)) {
				dodge_direction /= sqrt(2);
			}
			is_dodging = true;
			dodge_cool_count = 0;
		}
		not_clicked = false;
	}
	if (attack_count > attack_delay) {
		is_attacking = false;
	}
	// Change the attack mode by 'Tab'
	if (ranged_attack_unlocked && Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Tab)) {
		if (attack_mode == MELEE)
			attack_mode = RANGE;
		else
			attack_mode = MELEE;
	}
	// Player warp
	if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::B) && (mediator->GetTileState(position) != TILES::BASE_INSIDE) && (warp_resource >= 1)) {
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
	if (is_dodging) {
		dodging_count += dt;
		invincibility_count = invincibility_time - dodging_time;
		// Check collision while dodging
		if ((mediator->GetTileState({ position.x + dodge_direction.x * size / 2, position.y + dodge_direction.y * size / 2 }) != TILES::WALL) &&
			(mediator->GetTileState({ position.x + dodge_direction.x * size / 2, position.y + dodge_direction.y * size / 2 }) != TILES::COLONY_SIDE) &&
			(mediator->GetTileState({ position.x + dodge_direction.x * size / 2, position.y + dodge_direction.y * size / 2 }) != TILES::RESOURCE) &&
			(mediator->GetTileState({ position.x + dodge_direction.x * size / 2, position.y + dodge_direction.y * size / 2 }) != TILES::WARP) &&
			(mediator->GetTileState({ position.x + dodge_direction.x * size / 2, position.y + dodge_direction.y * size / 2 }) != TILES::TREASURE)) {
			position += dodge_direction * 2 * speed * dt;
		}
		if (dodging_count >= dodging_time) {
			dodging_count = 0;
			is_dodging = false;
		}
	}
	else {
		// Player moving with W, A, S, D
		Math::vec2 direction{ 0, 0 };
		if (Engine::GetInput().KeyDown(CS230::Input::Keys::W)) {
			if ((mediator->GetTileState({ position.x, position.y + size / 2 }) != TILES::WALL) && 
				(mediator->GetTileState({ position.x, position.y + size / 2 }) != TILES::COLONY_SIDE) &&
				(mediator->GetTileState({ position.x, position.y + size / 2 }) != TILES::RESOURCE)&&
				(mediator->GetTileState({ position.x, position.y + size / 2 }) != TILES::WARP) &&
				(mediator->GetTileState({ position.x, position.y + size / 2 }) != TILES::TREASURE)) {
				direction.y += 1;
			}
		}
		if (Engine::GetInput().KeyDown(CS230::Input::Keys::S)) {
			if ((mediator->GetTileState({ position.x, position.y - size / 2 }) != TILES::WALL) && 
				(mediator->GetTileState({ position.x, position.y - size / 2 }) != TILES::COLONY_SIDE) &&
				(mediator->GetTileState({ position.x, position.y - size / 2 }) != TILES::RESOURCE) &&
				(mediator->GetTileState({ position.x, position.y - size / 2 }) != TILES::WARP) &&
				(mediator->GetTileState({ position.x, position.y - size / 2 }) != TILES::TREASURE)) {
				direction.y -= 1;
			}
		}
		if (Engine::GetInput().KeyDown(CS230::Input::Keys::A)) {
			if ((mediator->GetTileState({ position.x - size / 2, position.y }) != TILES::WALL) &&
				(mediator->GetTileState({ position.x - size / 2, position.y }) != TILES::COLONY_SIDE) &&
				(mediator->GetTileState({ position.x - size / 2, position.y }) != TILES::RESOURCE) &&
				(mediator->GetTileState({ position.x - size / 2, position.y }) != TILES::WARP) &&
				(mediator->GetTileState({ position.x - size / 2, position.y }) != TILES::TREASURE)) {
				direction.x -= 1;
			}
		}
		if (Engine::GetInput().KeyDown(CS230::Input::Keys::D)) {
			if ((mediator->GetTileState({ position.x + size / 2, position.y }) != TILES::WALL) && 
				(mediator->GetTileState({ position.x + size / 2, position.y }) != TILES::COLONY_SIDE) &&
				(mediator->GetTileState({ position.x + size / 2, position.y }) != TILES::RESOURCE) &&
				(mediator->GetTileState({ position.x + size / 2, position.y }) != TILES::WARP) &&
				(mediator->GetTileState({ position.x + size / 2, position.y }) != TILES::TREASURE)) {
				direction.x += 1;
			}
		}
		// If the player move diagonally, divide speed by sqrt(2)
		if (direction.GetLength() == sqrt(2)) {
			direction /= sqrt(2);
		}
		position += direction * speed * dt;
	}
	// Tile_position update based on the player's position
	tile_position.x = (int)((position.x) / mediator->GetTileLength());
	tile_position.y = (int)((position.y) / mediator->GetTileLength());
	// Check player attacked
	mediator->CheckPlayerAttacked();

	if (hp <= 0) {
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
	}
}
// Draw player
void Player::Draw() {

	//sprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ scale_x, scale_y })));
	
	// If the player is attacking, draw the line (in the MELEE mode)
	if (is_attacking == true && attack_mode == MELEE) {
		push_settings();
		set_outline_width(10);
		draw_line(position.x, position.y, position.x + size * attack_direction.x, position.y + size * attack_direction.y);
		//draw_line(position.x, position.y, position.x + (size * (GetAttackPosition().x - position.x)), position.y + (size * (GetAttackPosition().y - position.y)));
		pop_settings();
	}
}
// Reduce hp
void Player::Reduce_hp() {
	if (invincibility_count > invincibility_time) {
		--hp;
		invincibility_count = 0;
		is_warping = false;
		warp_count = 0;
	}
}
// Get distacne from the player to the target
double Player::GetDistanceFromAttack(Math::vec2 target) {
	return sqrt((GetAttackPosition().x - target.x) * (GetAttackPosition().x - target.x) + (GetAttackPosition().y - target.y) * (GetAttackPosition().y - target.y));
}
// Attack function
void Player::Attack() {
	SetAttackPosition(GetAttackPosition() - position);
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

	double attack_x_pos = position.x + ((double)get_mouse_x() - (double)Engine::GetWindow().GetSize().x / 2) / distance;
	double attack_y_pos = position.y + ((double)get_mouse_y() - (double)Engine::GetWindow().GetSize().y / 2) / distance;

	return { attack_x_pos, attack_y_pos };
}
// Warp to the base
void Player::GoToBase() {
	position = { mediator->GetMapLength() / 2 + mediator->GetTileLength() / 2, mediator->GetMapLength() / 2 + mediator->GetTileLength() / 2 };
}
// Upgrade the player
void Player::Upgrade() {

}