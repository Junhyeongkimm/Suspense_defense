#include "Player.h"
#include <map>
#include "doodle/input.hpp"
#include "doodle/angle.hpp"
#include "doodle/random.hpp"
#include "../Engine/Engine.h"
#include "Mediator.h"
#include "State.h"
#include <cmath>
using namespace doodle;

void Player::SetWantScale(Math::vec2 new_scale)
{
	Math::ivec2 want = playersprite.GetFrameSize();
	scale_x = 1 / static_cast<double>(want.x)* new_scale.x;
	scale_y = 1 / static_cast<double>(want.y)* new_scale.y;
}

void Player::SwordSetWantScale(Math::vec2 new_scale)
{
	Math::ivec2 want1 = sword_weaponsprite.GetFrameSize();
	swordscale_x = 1 / static_cast<double>(want1.x) * new_scale.x;
	swordscale_y = 1 / static_cast<double>(want1.y) * new_scale.y;
}

void Player::GunSetWantScale(Math::vec2 new_scale)
{

	Math::ivec2 want2 = gun_weaponsprite.GetFrameSize();
	gunscale_x = 1 / static_cast<double>(want2.x) * new_scale.x;
	gunscale_y = 1 / static_cast<double>(want2.y) * new_scale.y;
}

void Player::ShoutGunSetWantScale(Math::vec2 new_scale)
{
	Math::ivec2 want3 = shoutgun_weaponsprite.GetFrameSize();
	shoutgunscale_x = 1 / static_cast<double>(want3.x) * new_scale.x;
	shoutgunscale_y = 1 / static_cast<double>(want3.y) * new_scale.y;
}

void Player::GatlingGunSetWantScale(Math::vec2 new_scale)
{
	Math::ivec2 want4 = gatlinggun_weaponsprite.GetFrameSize();
	gatlinggunscale_x = 1 / static_cast<double>(want4.x) * new_scale.x;
	gatlinggunscale_y = 1 / static_cast<double>(want4.y) * new_scale.y;
}

void Player::ARGunSetWantScale(Math::vec2 new_scale)
{
	Math::ivec2 want5 = argun_weaponsprite.GetFrameSize();
	argunscale_x = 1 / static_cast<double>(want5.x) * new_scale.x;
	argunscale_y = 1 / static_cast<double>(want5.y) * new_scale.y;
}

// Constructor
Player::Player(Math::vec2 start_position, Mediator* mediator, Math::ivec2 tile_position) : position(start_position), mediator(mediator), tile_position(tile_position) {
  
	box = new PopupBox(mediator);
	playersprite.Load("Assets/player.spt");
	SetWantScale({ 125,125 });
	playersprite.PlayAnimation(static_cast<int>(player_action::waiting));
	sword_weaponsprite.Load("Assets/sword.spt");
	gun_weaponsprite.Load("Assets/gun.spt");
	shoutgun_weaponsprite.Load("Assets/shoutgun.spt");
	gatlinggun_weaponsprite.Load("Assets/gatlinggun.spt");
	argun_weaponsprite.Load("Assets/argun.spt");
	sword_weaponsprite.PlayAnimation(static_cast<int>(Weapon_action::attack));
	gun_weaponsprite.PlayAnimation(static_cast<int>(Weapon_action::attack));


}
// Update
void Player::Update(double dt) { 
	// HP recovery
	recover_count += dt;
	if (mediator->GetMap()->GetTileStateInt(tile_position) == TILES::BASE_INSIDE ||
		mediator->GetMap()->GetTileStateInt(tile_position) == TILES::TOWER) {
		Heal();
	}

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
		if (MouseButton == MouseButtons::Right && dodge_cool_count >= dodge_cool_time) { // If the player is able to dodge and clicked the right button of mosue, dodge
			dodge_direction = { 0, 0 };
			if (Engine::GetInput().KeyDown(CS230::Input::Keys::W)) {
				dodge_direction.y += 1;
				playersprite.PlayAnimation(static_cast<int>(player_action::dodgeup));
			
			}
			if (Engine::GetInput().KeyDown(CS230::Input::Keys::S)) {
				dodge_direction.y -= 1;
				playersprite.PlayAnimation(static_cast<int>(player_action::dodgedown));
	
			}
			if (Engine::GetInput().KeyDown(CS230::Input::Keys::A)) {
				dodge_direction.x -= 1;
				playersprite.PlayAnimation(static_cast<int>(player_action::dodgeleft));
			
			}
			if (Engine::GetInput().KeyDown(CS230::Input::Keys::D)) {
				dodge_direction.x += 1;
				playersprite.PlayAnimation(static_cast<int>(player_action::dodgeright));

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
		if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::_3) && homing_unlocked) {
			attack_mode = HOMING;
		}
		if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::_4) && gatling_unlocked) {
			attack_mode = GATLING;
		}
	}

	// Player warp
	if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::B) && 
		(mediator->GetMap()->GetTileState(position) != TILES::BASE_INSIDE) &&
		(mediator->GetMap()->GetTileState(position) != TILES::BASE_WALL) &&
		(mediator->GetMap()->GetTileState(position) != TILES::TOWER)
		&& (warp_resource >= 1) &&
		!is_attacking) {

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

	if (is_attacking == true && attack_mode == MELEE) {
		sword_weaponsprite.Update(dt);
	}
	else if (is_attacking == true && attack_mode == RANGE) {
		gun_weaponsprite.Update(dt);
	}
	else if (is_attacking == true && attack_mode == SHOTGUN) {
		shoutgun_weaponsprite.Update(dt);

	}
	else if (is_attacking == true && attack_mode == HOMING) {
		argun_weaponsprite.Update(dt);
	}
	else if (is_attacking == true && attack_mode == GATLING) {
		gatlinggun_weaponsprite.Update(dt);
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
		if (direction.GetLength() == sqrt(2))
			direction /= sqrt(2);
		else if (direction.x == 0 && direction.y == 0)
			is_moving = false;

		position += direction * speed * dt;

		if(direction.x == 0 && direction.y == 1)
			playersprite.PlayAnimation(static_cast<int>(player_action::up));
		else if(direction.x == 0 && direction.y == -1)
			playersprite.PlayAnimation(static_cast<int>(player_action::down));
		else if(direction.x == -1 && direction.y == 0)
			playersprite.PlayAnimation(static_cast<int>(player_action::left));
		else if(direction.x == 1 && direction.y == 0)
			playersprite.PlayAnimation(static_cast<int>(player_action::right));


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
	// Game over
	if (hp <= 0) {
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::GameOver));
	}
	if (is_moving == false && is_dodging == false)
	{
		playersprite.PlayAnimation(static_cast<int>(player_action::waiting));
	}
	playersprite.Update(dt);

}
// Draw player
void Player::Draw() {
	if (box->is_activated())
		box->Draw();

	//player draw
	playersprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ scale_x, scale_y })));
	
	// Draw attack
	if (is_attacking) {
		switch (attack_mode) {
		case MELEE:
			sword_weaponsprite.Draw((Math::TranslationMatrix(position) * Math::RotationMatrix{ radians } *Math::ScaleMatrix({ swordscale_x, swordscale_y })));
			break;
		case RANGE:
			if (radians > 1.5 && radians < 4.2) {
				gun_weaponsprite.Draw((Math::TranslationMatrix(position) * Math::RotationMatrix{ radians } *Math::ScaleMatrix({ gunscale_x, -gunscale_y })));
			}
			else {
				gun_weaponsprite.Draw((Math::TranslationMatrix(position) * Math::RotationMatrix{ radians } *Math::ScaleMatrix({ gunscale_x, gunscale_y })));
			}
			break;
		case SHOTGUN:
			if (radians > 1.5 && radians < 4.2) {
				shoutgun_weaponsprite.Draw((Math::TranslationMatrix(position) * Math::RotationMatrix{ radians } *Math::ScaleMatrix({ shoutgunscale_x, -shoutgunscale_y })));
			}
			else {
				shoutgun_weaponsprite.Draw((Math::TranslationMatrix(position) * Math::RotationMatrix{ radians } *Math::ScaleMatrix({ shoutgunscale_x, shoutgunscale_y })));
			}
			break;
		case HOMING:
			if (radians > 1.5 && radians < 4.2) {
				argun_weaponsprite.Draw((Math::TranslationMatrix(position) * Math::RotationMatrix{ radians }*Math::ScaleMatrix({ argunscale_x, -argunscale_y })));
			}
			else {
				argun_weaponsprite.Draw((Math::TranslationMatrix(position) * Math::RotationMatrix{ radians }*Math::ScaleMatrix({ argunscale_x, argunscale_y })));
			}
			break;
		case GATLING:
			if (radians > 1.5 && radians < 4.2) {
				gatlinggun_weaponsprite.Draw((Math::TranslationMatrix(position) * Math::RotationMatrix{ radians } *Math::ScaleMatrix({ gatlinggunscale_x, -gatlinggunscale_y })));
			}
			else {
				gatlinggun_weaponsprite.Draw((Math::TranslationMatrix(position) * Math::RotationMatrix{ radians } *Math::ScaleMatrix({ gatlinggunscale_x, gatlinggunscale_y })));
			}
			break;
		}
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
}

// Attack function
void Player::Attack() {
	SetAttackPosition(GetAttackPosition() - position);

	is_attacking = true;
	attack_count = 0;

	Math::vec2 weaponDir{ static_cast<double>(doodle::get_mouse_x() - (Engine::GetWindow().GetSize().x / 2)), static_cast<double>(doodle::get_mouse_y() - (Engine::GetWindow().GetSize().y / 2)) };
	weaponDir /= weaponDir.GetLength();
	radians = atan(weaponDir.y / weaponDir.x);
	if (weaponDir.x < 0) {
		radians += PI;
	}
	else if (weaponDir.x >= 0 && weaponDir.y < 0) {
		radians += 2 * PI;
	}
	switch (attack_mode) {
	case MELEE:
		SwordSetWantScale({ 50, 50 });
		mediator->Check_Map_Attacked();
		sword_weaponsprite.PlayNotLoopAnimation(static_cast<int>(Weapon_action::attack));
		break;
	case RANGE:
		GunSetWantScale({ 40,40 });
		mediator->AddBullet(position, GetAttackPosition() - position);
		gun_weaponsprite.PlayAnimation(static_cast<int>(Weapon_action::attack));
		break;
	case SHOTGUN:
		ShoutGunSetWantScale({ 80,80 });
		mediator->AddShotgun(position, GetAttackPosition() - position);
		shoutgun_weaponsprite.PlayAnimation(static_cast<int>(Weapon_action::attack));
		break;
	case GATLING:
		GatlingGunSetWantScale({ 80, 80 });
		mediator->AddGatling(position, GetAttackPosition() - position);
		gatlinggun_weaponsprite.PlayAnimation(static_cast<int>(Weapon_action::attack));
		break;
	case HOMING:
		ARGunSetWantScale({ 70,40 });
		mediator->AddHoming(position, GetAttackPosition() - position);
		argun_weaponsprite.PlayAnimation(static_cast<int>(Weapon_action::attack));
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