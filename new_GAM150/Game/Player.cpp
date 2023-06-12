#include "Player.h"
#include <map>
#include "doodle/input.hpp"
#include "doodle/angle.hpp"
#include "doodle/random.hpp"
#include "../Engine/Engine.h"
#include "Mediator.h"
#include "State.h"
using namespace doodle;

void Player::SetWantScale(Math::vec2 new_scale)
{

		Math::ivec2 want = sprite.GetFrameSize();
		scale_x = 1 / static_cast<double>(want.x)* new_scale.x;
		scale_y = 1 / static_cast<double>(want.y)* new_scale.y;
}
// Constructor
Player::Player(Math::vec2 start_position, const CS230::Camera& camera, Mediator* mediator, Math::ivec2 tile_position) : position(start_position), camera(camera), mediator(mediator), tile_position(tile_position) {
  
	box = new PopupBox(mediator);
	sprite.Load("Assets/player.spt");
	SetWantScale({ 125,125 });
	sprite.PlayAnimation(static_cast<int>(player_action::waiting));
}
// Update
void Player::Update(double dt) {
	is_moving = false;
	if (mediator->GetMap()->GetTileStateInt(tile_position) == TILES::TOWER) {
		if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::E) && !box->is_activated()) {
			box->Activate();
			return;
		}
	}
	if (box->is_activated()) {
		box->Update();
		return;
	}

	// Increase attack_count and invincibility_count, dodge_count by dt 
	invincibility_count += dt;
	dodge_cool_count += dt;
	attack_count += dt;
	// Differenciate attack delay based on the attack mode
	switch (attack_mode) {
	case MELEE:
		if (attack_count > attack_delay * 0.7) {
			is_attacking = false;
		}
		break;
	case RANGE:
		if (attack_count > attack_delay) {
			is_attacking = false;
		}
		break;
	case SHOTGUN:
		if (attack_count > attack_delay * 2) {
			is_attacking = false;
		}
		break;
	case GATLING:
		if (attack_count > attack_delay * 0.3) {
			is_attacking = false;
		}
		break;
	case HOMING:
		if (attack_count > attack_delay * 1.4) {
			is_attacking = false;
		}
		break;
	}
	// Attack
	if (!is_attacking && MouseIsPressed && MouseButton == MouseButtons::Left) {
		Attack();
	}
	// Check Clicked
	if (!MouseIsPressed) {
		not_clicked = true;
	}
	// Dodge
	if (not_clicked && MouseIsPressed) { // When the player click the mouse
		if (dodge_unlocked && MouseButton == MouseButtons::Right && dodge_cool_count >= dodge_cool_time) { // If the player is able to dodge and clicked the right button of mosue, dodge
			dodge_direction = { 0, 0 };
			if (Engine::GetInput().KeyDown(CS230::Input::Keys::W)) {
				dodge_direction.y += 1;
				sprite.PlayAnimation(static_cast<int>(player_action::dodgeup));
			}
			if (Engine::GetInput().KeyDown(CS230::Input::Keys::S)) {
				dodge_direction.y -= 1;
				sprite.PlayAnimation(static_cast<int>(player_action::dodgedown));
			}
			if (Engine::GetInput().KeyDown(CS230::Input::Keys::A)) {
				dodge_direction.x -= 1;
				sprite.PlayAnimation(static_cast<int>(player_action::dodgeleft));
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

	
	// Change the attack mode by 0, 1, 2, 3, 4 key
	if (!is_attacking) {

		if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Tab)) {
			if (attack_mode == MELEE)
				attack_mode = RANGE;
			else
				attack_mode = MELEE;
		}
		if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::_1)) {
			attack_mode = RANGE;
		}
		if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::_2) && shotgun_unlocked) {
			attack_mode = SHOTGUN;
		}
		if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::_3) && gatling_unlocked) {
			attack_mode = HOMING;
		}
		if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::_4) && homing_unlocked) {
			attack_mode = GATLING;
		}
	}

	// Player warp
	if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::B) && 
		(mediator->GetMap()->GetTileState(position) != TILES::BASE_INSIDE) &&
		(mediator->GetMap()->GetTileState(position) != TILES::BASE_WALL) &&
		(mediator->GetMap()->GetTileState(position) != TILES::TOWER)
		&& (warp_resource >= 1)) {

		if(is_warping==false){
			
			warpsprite.Load("Assets/teleport.spt");
			warpsprite.PlayAnimation(static_cast<int>(warp_action::warping));
		}
		is_warping = true;
		
	}
	if (is_warping) {
		warp_count += dt;
		warpsprite.Update(dt);
		
		if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::W) || Engine::GetInput().KeyJustPressed(CS230::Input::Keys::A) ||
			Engine::GetInput().KeyJustPressed(CS230::Input::Keys::S) || Engine::GetInput().KeyJustPressed(CS230::Input::Keys::D)) {
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
		if ((mediator->GetMap()->GetTileState({ position.x + dodge_direction.x * size / 2, position.y + dodge_direction.y * size / 2 }) != TILES::WALL) &&
			(mediator->GetMap()->GetTileState({ position.x + dodge_direction.x * size / 2, position.y + dodge_direction.y * size / 2 }) != TILES::COLONY_SIDE) &&
			(mediator->GetMap()->GetTileState({ position.x + dodge_direction.x * size / 2, position.y + dodge_direction.y * size / 2 }) != TILES::RESOURCE) &&
			(mediator->GetMap()->GetTileState({ position.x + dodge_direction.x * size / 2, position.y + dodge_direction.y * size / 2 }) != TILES::WARP) &&
			(mediator->GetMap()->GetTileState({ position.x + dodge_direction.x * size / 2, position.y + dodge_direction.y * size / 2 }) != TILES::TREASURE)) {
			position += dodge_direction * 1.5 * speed * dt;
			
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
			is_moving = true;
				sprite.PlayAnimation(static_cast<int>(player_action::up));
			
			if ((mediator->GetMap()->GetTileState({ position.x, position.y + size / 2 }) != TILES::WALL) && 
				(mediator->GetMap()->GetTileState({ position.x, position.y + size / 2 }) != TILES::COLONY_SIDE) &&
				(mediator->GetMap()->GetTileState({ position.x, position.y + size / 2 }) != TILES::RESOURCE)&&
				(mediator->GetMap()->GetTileState({ position.x, position.y + size / 2 }) != TILES::WARP) &&
				(mediator->GetMap()->GetTileState({ position.x, position.y + size / 2 }) != TILES::TREASURE)) {
				direction.y += 1;
				

			}
		}
		if (Engine::GetInput().KeyDown(CS230::Input::Keys::S)) {
			is_moving = true;
			sprite.PlayAnimation(static_cast<int>(player_action::down));
			if ((mediator->GetMap()->GetTileState({ position.x, position.y - size / 2 }) != TILES::WALL) &&
				(mediator->GetMap()->GetTileState({ position.x, position.y - size / 2 }) != TILES::COLONY_SIDE) &&
				(mediator->GetMap()->GetTileState({ position.x, position.y - size / 2 }) != TILES::RESOURCE) &&
				(mediator->GetMap()->GetTileState({ position.x, position.y - size / 2 }) != TILES::WARP) &&
				(mediator->GetMap()->GetTileState({ position.x, position.y - size / 2 }) != TILES::TREASURE)) {
				direction.y -= 1;
				

			}
		}
		if (Engine::GetInput().KeyDown(CS230::Input::Keys::A)) {
			is_moving = true;
			sprite.PlayAnimation(static_cast<int>(player_action::left));
			if ((mediator->GetMap()->GetTileState({ position.x - size / 2, position.y }) != TILES::WALL) &&
				(mediator->GetMap()->GetTileState({ position.x - size / 2, position.y }) != TILES::COLONY_SIDE) &&
				(mediator->GetMap()->GetTileState({ position.x - size / 2, position.y }) != TILES::RESOURCE) &&
				(mediator->GetMap()->GetTileState({ position.x - size / 2, position.y }) != TILES::WARP) &&
				(mediator->GetMap()->GetTileState({ position.x - size / 2, position.y }) != TILES::TREASURE)) {
				direction.x -= 1;
			}
		}
		if (Engine::GetInput().KeyDown(CS230::Input::Keys::D)) {
			is_moving = true;
			if ((mediator->GetMap()->GetTileState({ position.x + size / 2, position.y }) != TILES::WALL) &&
				(mediator->GetMap()->GetTileState({ position.x + size / 2, position.y }) != TILES::COLONY_SIDE) &&
				(mediator->GetMap()->GetTileState({ position.x + size / 2, position.y }) != TILES::RESOURCE) &&
				(mediator->GetMap()->GetTileState({ position.x + size / 2, position.y }) != TILES::WARP) &&
				(mediator->GetMap()->GetTileState({ position.x + size / 2, position.y }) != TILES::TREASURE)) {
				direction.x += 1;
			}
		}
		// If the player move diagonally, divide speed by sqrt(2)
		if (direction.GetLength() == sqrt(2)) {
			direction /= sqrt(2);
		}
		position += direction * speed * dt;

		if (mediator->GetMap()->GetTileState(position) == TILES::WALL ||
			mediator->GetMap()->GetTileState(position) == TILES::RESOURCE ||
			mediator->GetMap()->GetTileState(position) == TILES::COLONY_SIDE ||
			mediator->GetMap()->GetTileState(position) == TILES::WARP ||
			mediator->GetMap()->GetTileState(position) == TILES::TREASURE) {
			position -= direction * speed * dt;
		}
	}
	// Tile_position update based on the player's position
	tile_position.x = (int)((position.x) / mediator->GetMap()->Get_Tile_Length());
	tile_position.y = (int)((position.y) / mediator->GetMap()->Get_Tile_Length());
	// Check player attacked
	mediator->CheckPlayerAttacked();
	// HP recovery
	recover_count += dt;
	if (mediator->GetMap()->GetTileStateInt(tile_position) == TILES::BASE_INSIDE) {
		Heal();
	}
	// Game over
	if (hp <= 0) {
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
	}
	if (is_moving == false && is_dodging == false)
	{
		sprite.PlayAnimation(static_cast<int>(player_action::waiting));
	}
	sprite.Update(dt);
}
// Draw player
void Player::Draw() {
	if (box->is_activated())
		box->Draw();

	//player draw
	sprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ scale_x, scale_y })));
	
	// If the player is attacking, draw the line (in the MELEE mode)
	if (is_attacking == true && attack_mode == MELEE) {
		push_settings();
		weaponsprite.Load("Assets/sword.spt");
		weaponsprite.PlayAnimation(static_cast<int>(Weapon_action::attack));
		weaponsprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ scale_x, scale_y })));
		pop_settings();
	}
	else if (is_attacking == true && attack_mode == RANGE) {
		push_settings();
		weaponsprite.Load("Assets/gun.spt");
		weaponsprite.PlayAnimation(static_cast<int>(Weapon_action::attack));
		weaponsprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ scale_x, scale_y })));
		pop_settings();
	}

	if (is_warping) {
		warpsprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ scale_x, scale_y })));
	}
}
// Reduce hp
void Player::Reduce_hp(int damage) {
	if (invincibility_count > invincibility_time) {
		hp -= damage;
		invincibility_count = 0;
		is_warping = false;
		warp_count = 0;
	}
}
// Heal
void Player::Heal() {
	if (hp < max_hp && recover_count >= recover_cool) {
		++hp;
		recover_count = 0;
	}
}
// Get distacne from the player to the target
double Player::GetDistanceFromAttack(Math::vec2 target) {
	return (GetAttackPosition() - target).GetLength();
	//return sqrt((GetAttackPosition().x - target.x) * (GetAttackPosition().x - target.x) + (GetAttackPosition().y - target.y) * (GetAttackPosition().y - target.y));
}
// Attack function
void Player::Attack() {
	SetAttackPosition(GetAttackPosition() - position);

	is_attacking = true;
	attack_count = 0;

	switch (attack_mode) {
	case MELEE:
		mediator->Check_Map_Attacked();
		break;
	case RANGE:
		mediator->AddBullet(position, GetAttackPosition() - position);
		break;
	case SHOTGUN:
		mediator->AddShotgun(position, GetAttackPosition() - position);
		break;
	case GATLING:
		mediator->AddGatling(position, GetAttackPosition() - position);
		break;
	case HOMING:
		mediator->AddHoming(position, GetAttackPosition() - position);
		break;
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
	position = { mediator->GetMap()->Get_Map_Length() / 2 + mediator->GetMap()->Get_Tile_Length() / 2, mediator->GetMap()->Get_Map_Length() / 2 + mediator->GetMap()->Get_Tile_Length() / 2 };
}
// Upgrade the player
void Player::Attack_Upgrade() {
	if (map_resource >= GetAttackUpgradeCost()) {
		switch (attack_upgrade_count) {
		case 0:
			attack_delay -= 0.1;
			break;
		case 1:
			attack_delay -= 0.1;
			++damage;
			break;
		case 2:
			attack_delay -= 0.1;
			break;
		case 3:
			attack_delay -= 0.1;
			++damage;
			break;
		case 4:
			attack_delay -= 0.1;
			break;
		case 5:
			attack_delay -= 0.1;
			++damage;
			break;
		}
		UseMapResource(GetAttackUpgradeCost());
		//map_resource -= GetAttackUpgradeCost();
		++attack_upgrade_count;
	}
}
void Player::Utility_Upgrade() { 
	if (map_resource >= GetUtilityUpgradeCost()) {
		switch (utility_upgrade_count) {
		case 0:
			max_hp += 2;
			hp = max_hp;
			speed += 25;
			break;
		case 1:
			max_hp += 3;
			hp = max_hp;
			speed += 25;
			break;
		case 2:
			max_hp += 2;
			hp = max_hp;
			hp = max_hp;
			speed += 25;
			break;
		case 3:
			max_hp += 3;
			hp = max_hp;
			speed += 25;
			break;
		case 4:
			max_hp += 2;
			hp = max_hp;
			speed += 25;
			break;
		case 5:
			max_hp += 3;
			hp = max_hp;
			speed += 25;
			break;
		}
		UseMapResource(GetUtilityUpgradeCost());
		//map_resource -= GetUtilityUpgradeCost();
		++utility_upgrade_count;
	}
	
}

int Player::GetAttackUpgradeCost() {
	switch (attack_upgrade_count) {
	case 0 :
		return 5;
		break;
	case 1:
		return 10;
		break;
	case 2:
		return 15;
		break;
	case 3:
		return 20;
		break;
	case 4:
		return 25;
		break;
	case 5:
		return 30;
		break;
	default:
		return 0;
	}
	return 0;
}
int Player::GetUtilityUpgradeCost() {
	switch (utility_upgrade_count) {
	case 0:
		return 5;
		break;
	case 1:
		return 10;
		break;
	case 2:
		return 15;
		break;
	case 3:
		return 20;
		break;
	case 4:
		return 25;
		break;
	case 5:
		return 30;
		break;
	default:
		return 0;
	}
	return 0;
}