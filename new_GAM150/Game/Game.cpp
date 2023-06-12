#include "Game.h"
#include "State.h"
#include "../Engine/Engine.h"
#include <vector>
#include "doodle/input.hpp"
#include "doodle/angle.hpp"
using namespace doodle;


void Game::SetWantScale(Math::vec2 new_scale)
{

	Math::ivec2 want = sprite.GetFrameSize();
	scale_x = 1 / static_cast<double>(want.x) * new_scale.x;
	scale_y = 1 / static_cast<double>(want.y) * new_scale.y;
}
// Constructor of Game
Game::Game() : 
	camera({ { 0.15 * Engine::GetWindow().GetSize().x, 0 }, { 0.35 * Engine::GetWindow().GetSize().x, 0 } }),

	player(nullptr), monsters(), bosses(), bullets(), monster_bullets(), map(nullptr), mediator(nullptr), target(nullptr)
{ 
	sprite.Load("Assets/bullet.spt");

	SetWantScale({ 125,125 });
	sprite.PlayAnimation(static_cast<int>(bullet::None));
}
// Load. Create mediator and set map, monster, player, bullet.
void Game::Load() {
	camera.SetPosition({ 0, 0 }); // Camera is not used for now LOL
	//camera.SetLimit({ {0,0}, { background.GetSize() - Engine::GetWindow().GetSize() } });
	// Create mediator
	mediator = new Mediator();
	// Create map and give it to the mediator
	map = new Map(mediator);
	mediator->SetMap(map);
	// Create player and give it to the mediator
	player = new Player(middle_point, camera, mediator, { map->Get_Map_Size() / 2, map->Get_Map_Size() / 2 });
	mediator->SetPlayer(player);
	// Give monsters to the mediator
	mediator->SetMonsters(&monsters);
	// Give bosses to the mediator
	mediator->SetBosses(&bosses);
	// Give bullets to the mediator
	mediator->SetBullets(&bullets);
	// Give monster bullets to the mediator
	mediator->SetMBullets(&monster_bullets);
	// Create map by function MapMaking()
	map->MapMaking();
}
// Update Game
void Game::Update([[maybe_unused]] double dt) {
	// Update player, map, monster, bullets update
	player->Update(dt);
	map->Update(dt);
	for (int i = 0; i < monsters.size(); i++) {
		monsters[i]->Update(dt);
	}
	for (int i = 0; i < bosses.size(); i++) {
		bosses[i]->Update(dt);
	}
	for (int i = 0; i < bullets.size(); i++) {
		bullets[i]->Update(dt);
	}
	for (int i = 0; i < bullets.size(); i++) {
		// Check collision with monster
		for (int j = 0; j < monsters.size(); j++) {
			if (monsters[j]->GetDistance(bullets[i]->GetPosition()) < (monsters[j]->GetSize() / 2 + bullets[i]->GetSize() / 2)) {
				monsters[j]->Reduce_hp(bullets[i]->GetDamage());
				if (monsters[j]->GetHp() <= 0)
					mediator->DeleteMonster(monsters[j]);
				mediator->DeleteBullet(bullets[i]);
				break;
			}
		}
	}
	for (int i = 0; i < bullets.size(); i++) {
		// Check collision with bosses
		for (int j = 0; j < bosses.size(); j++) {
			if (bosses[j]->GetDistance(bullets[i]->GetPosition()) < (bosses[j]->GetSize() + bullets[i]->GetSize()) / 2) {
				bosses[j]->ReduceHP(bullets[i]->GetDamage());
				mediator->DeleteBullet(bullets[i]);
				break;
			}
		}
	}
	for (int i = 0; i < monster_bullets.size(); i++) {
		monster_bullets[i]->Update(dt);
	}
	// Update camera. (Meaningless)
	camera.Update(player->GetPosition());
	// If the player press "Escape" key, change the scene to the mainmenu
	if (Key == KeyboardButtons::Escape) {
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
	}
	// ------------------------------- TOWER -------------------------------
	
}
// Unload game
void Game::Unload() {

}
// Draw things
void Game::Draw() {
	Engine::GetWindow().Clear(0x000000FF);


	Math::TransformationMatrix camera_matrix = camera.GetMatrix(); // Not used.

	// Draw map, player, monster, bullet
	push_settings();
	// Translate
	apply_translate(-mediator->GetPlayer()->GetPosition().x + (double)Engine::GetWindow().GetSize().x / 2, -mediator->GetPlayer()->GetPosition().y + (double)Engine::GetWindow().GetSize().y / 2);
	push_settings();
	no_outline();
	// No outline only for the map. Maybe need to be changed after we apply the images.
	map->Show_Map();
	pop_settings();
	map->Base_Show_Arrow();
	map->Colony_Show_Arrow();
	// Draw player
	player->Draw();
	// Draw monsters if they are near the screen.
	for (Monster* monster : monsters) {
		if( monster->GetPosition().x < player->GetPosition().x + map->Get_Tile_Length() * (map->GetOffset() + 2) &&
			monster->GetPosition().x > player->GetPosition().x - map->Get_Tile_Length() * (map->GetOffset() + 2) &&
			monster->GetPosition().y < player->GetPosition().y + map->Get_Tile_Length() * (map->GetOffset() + 2) &&
			monster->GetPosition().y > player->GetPosition().y - map->Get_Tile_Length() * (map->GetOffset() + 2)
			)
			monster->Draw();
	}
	for (int i = 0; i < bosses.size(); i++) {
		bosses[i]->Draw();
	}
	/*for (Boss* boss : bosses) {
		boss->Draw();
	}*/
	for (int i = 0; i < bullets.size(); i++) {
		bullets[i]->Draw();
	}
	/*for (Bullet* bullet : bullets) {
		bullet->Draw();
	}*/
	for (int i = 0; i < monster_bullets.size(); i++) {
		monster_bullets[i]->Draw();
	}
	/*for (MBullet* bullet : monster_bullets) {
		bullet->Draw();
	}*/
	pop_settings();


	// Draw texts
	push_settings();
	set_font_size(25);

	draw_text("R1: " + std::to_string(player->GetMapResource()), Engine::GetWindow().GetSize().x - 150, Engine::GetWindow().GetSize().y - 50);
	draw_text("R2: " + std::to_string(player->GetMonsterResource()), Engine::GetWindow().GetSize().x - 150, Engine::GetWindow().GetSize().y - 80);
	draw_text("R3: " + std::to_string(player->GetWarpResource()), Engine::GetWindow().GetSize().x - 150, Engine::GetWindow().GetSize().y - 110);

	draw_text("C: " + std::to_string(map->GetColony()), Engine::GetWindow().GetSize().x - 150, 80);
	draw_text("M: " + std::to_string(monsters.size()), Engine::GetWindow().GetSize().x - 150, 50);

	draw_text("Hp: " + std::to_string(player->GetHP()) + " / " + std::to_string(player->GetMaxHP()), 10, 30);

	draw_text("Day " + std::to_string(map->GetDate() + 1), (double)Engine::GetWindow().GetSize().x / 2 - 100, (double)Engine::GetWindow().GetSize().y - 50);
	draw_text("Time: " + std::to_string((int)(map->GetTime() / map->GetDuration() * 100)) + "%", (double)Engine::GetWindow().GetSize().x / 2 - 100, (double)Engine::GetWindow().GetSize().y - 80);

	pop_settings();
}