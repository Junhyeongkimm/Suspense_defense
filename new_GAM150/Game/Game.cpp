#include "Game.h"
#include "State.h"
#include "../Engine/Engine.h"
#include <vector>
#include "doodle/input.hpp"
#include "doodle/angle.hpp"
using namespace doodle;

// Constructor of Game
Game::Game() : 
	camera({ { 0.15 * Engine::GetWindow().GetSize().x, 0 }, { 0.35 * Engine::GetWindow().GetSize().x, 0 } }),
	player(nullptr), monsters(), bullets(), map(nullptr), mediator(nullptr), target(nullptr)
{ }
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
	// Give bullets to the mediator
	mediator->SetBullets(&bullets);
	// Create map by function MapMaking()
	map->MapMaking();
}
// Update Game
void Game::Update([[maybe_unused]] double dt) {
	// Update player, map, monster, bullets
	player->Update(dt);
	map->Update(dt);
	for (Monster* monster : monsters) {
		monster->Update(dt);
	}
	for (Bullet* bullet : bullets) {
		bullet->Update(dt);
		// Check collision with monsters
		for (Monster* monster : monsters) {
			if (monster->GetDistance(bullet->GetPosition()) < (monster->GetSize() / 2 + bullet->GetSize() / 2)) {
				mediator->DeleteBullet(bullet);
				mediator->DeleteMonster(monster);
			}
		}
	}
	// Update camera. (Meaningless)
	camera.Update(player->GetPosition());
	// If the player press "Escape" key, change the scene to the mainmenu
	if (Key == KeyboardButtons::Escape) {
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
	}
	// ------------------------------- TOWER -------------------------------
	// Find the closest monster and set the target
	target = nullptr;
	for (Monster* monster : monsters) {
		if (target == nullptr || monster->GetDistance(middle_point) < target->GetDistance(middle_point))
			target = monster;
	}
	// Attack the target monster if it is not nullptr and in range
	tower_attack_count += dt;
	if (target != nullptr) {
		if ((target->GetDistance(middle_point) < map->Get_Tile_Length() * 15) && tower_attack_count >= tower_attack_cool) {
			Math::vec2 direction = target->GetPosition() - middle_point;
			direction /= direction.GetLength();
			mediator->AddBullet(middle_point, direction);
			tower_attack_count = 0;
		}
	}
	// If there is no monster, set the target to the nullptr
	if (monsters.size() == 0)
		target = nullptr;
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
	apply_translate(-mediator->GetPlayerPosition().x + (double)Engine::GetWindow().GetSize().x / 2, -mediator->GetPlayerPosition().y + (double)Engine::GetWindow().GetSize().y / 2);
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
	for (Bullet* bullet : bullets) {
		bullet->Draw();
	}
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

	draw_text("Day " + std::to_string(map->GetDate()), (double)Engine::GetWindow().GetSize().x / 2 - 100, (double)Engine::GetWindow().GetSize().y - 50);
	draw_text("Time: " + std::to_string((int)(map->GetTime() / map->GetDuration() * 100)) + "%", (double)Engine::GetWindow().GetSize().x / 2 - 100, (double)Engine::GetWindow().GetSize().y - 80);

	pop_settings();
}