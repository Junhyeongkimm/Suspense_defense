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
Player::Player(Math::vec2 start_position, const CS230::Camera& camera, Mediator* mediator, Math::ivec2 tile_position) : position(start_position), camera(camera), mediator(mediator), tile_position(tile_position) {
  
	box = new PopupBox(mediator);
	playersprite.Load("Assets/player.spt");
	SetWantScale({ 125,125 });
	playersprite.PlayAnimation(static_cast<int>(player_action::waiting));

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

	if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::NumPad_1)) {
		mediator->AddBoss1(position);
	}
	if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::NumPad_2)) {
		mediator->AddBoss2(position);
	}
	if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::NumPad_3)) {
		mediator->AddBoss3(position);
	}
	if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::NumPad_4)) {
		mediator->AddBoss4(position);
	}

	// Increase attack_count and invincibility_count, dodge_count by dt 
	invincibility_count += dt;
	dodge_cool_count += dt;
	attack_count += dt;
	// Differenciate attack delay based on the attack mode
	switch (attack_mode) {
	case MELEE:
		if (attack_count > attack_delay) {
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
		if (attack_count > attack_delay * 0.4) {
			is_attacking = false;
		}
		break;
	case HOMING:
		if (attack_count > attack_delay * 1.5) {
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
		if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::_0)) {
			attack_mode = MELEE;
		}
		if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::_1)) {
			attack_mode = RANGE;
		}
		if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::_2)) {
			attack_mode = SHOTGUN;
		}
		if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::_3)) {
			attack_mode = GATLING;
		}
		if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::_4)) {
			attack_mode = HOMING;
		}
	}

	// Player warp

	if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::B) && (mediator->GetMap()->GetTileState(position) != TILES::BASE_INSIDE) && (warp_resource >= 1)) {

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
			is_moving = true;
			playersprite.PlayAnimation(static_cast<int>(player_action::up));
			
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
			playersprite.PlayAnimation(static_cast<int>(player_action::down));

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
			playersprite.PlayAnimation(static_cast<int>(player_action::left));

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
			playersprite.PlayAnimation(static_cast<int>(player_action::right));

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
	
	// If the player is attacking, draw the line (in the MELEE mode)
	if (is_attacking==true && attack_mode == MELEE) {
		
		sword_weaponsprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ swordscale_x, swordscale_y })));
	}
	else if (is_attacking == true && attack_mode == RANGE) {
		
		gun_weaponsprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ gunscale_x, gunscale_y })));
	}
	else if (is_attacking == true && attack_mode == SHOTGUN) {
		
		shoutgun_weaponsprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ shoutgunscale_x, shoutgunscale_y })));

	}
	else if (is_attacking == true && attack_mode == GATLING) {
	
		gatlinggun_weaponsprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ gatlinggunscale_x, gatlinggunscale_y })));
	}
	else if (is_attacking == true && attack_mode == HOMING) {
		
		argun_weaponsprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ argunscale_x, argunscale_y })));
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
		sword_weaponsprite.Load("Assets/sword.spt");
		SwordSetWantScale({ 50, 50 });
		sword_weaponsprite.PlayAnimation(static_cast<int>(Weapon_action::attack));
		mediator->Check_Map_Attacked();
		break;
	case RANGE:
		gun_weaponsprite.Load("Assets/gun.spt");
		GunSetWantScale({ 40,40 });
		gun_weaponsprite.PlayAnimation(static_cast<int>(Weapon_action::attack));
		mediator->AddBullet(position, GetAttackPosition() - position);
		break;
	case SHOTGUN:
		shoutgun_weaponsprite.Load("Assets/shoutgun.spt");
		ShoutGunSetWantScale({ 80,80 });
		shoutgun_weaponsprite.PlayAnimation(static_cast<int>(Weapon_action::attack));
		mediator->AddBullet(position, GetAttackPosition() - position + Math::vec2(random(-0.2, 0.2), random(-0.2, 0.2)));
		mediator->AddBullet(position, GetAttackPosition() - position + Math::vec2(random(-0.2, 0.2), random(-0.2, 0.2)));
		mediator->AddBullet(position, GetAttackPosition() - position + Math::vec2(random(-0.2, 0.2), random(-0.2, 0.2)));
		break;
	case GATLING:
		gatlinggun_weaponsprite.Load("Assets/gatlinggun.spt");
		GatlingGunSetWantScale({ 80, 80 });
		gatlinggun_weaponsprite.PlayAnimation(static_cast<int>(Weapon_action::attack));
		mediator->AddBullet(position, GetAttackPosition() - position);
		break;
	case HOMING:
		argun_weaponsprite.Load("Assets/argun.spt");
		ARGunSetWantScale({ 70,40 });
		argun_weaponsprite.PlayAnimation(static_cast<int>(Weapon_action::attack));
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
	switch (attack_upgrade_count) {
	case 0:

		break;
	case 1:

		break;
	case 2:

		break;
	case 3:

		break;
	case 4:

		break;
	default:

		break;
	}
	std::cout << "Player upgrade!\n";
}
void Player::Utility_Upgrade() { 
	switch (utility_upgrade_count) {
	case 0:

		break;
	case 1:

		break;
	case 2:

		break;
	case 3:

		break;
	case 4:

		break;
	default:

		break;
	} 
	std::cout << "Utility upgrade!\n";
}