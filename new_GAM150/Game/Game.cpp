#include "Game.h"
#include "State.h"
#include "../Engine/Engine.h"
#include <vector>
#include "doodle/input.hpp"
#include "doodle/angle.hpp"

using namespace doodle;
#include <iostream>

Game::Game() : 
	camera({ { 0.15 * Engine::GetWindow().GetSize().x, 0 }, { 0.35 * Engine::GetWindow().GetSize().x, 0 } }),
	player(nullptr), monsters(), bullets(), map(nullptr), mediator(nullptr), target(nullptr)
{ }

void Game::Load() {
	camera.SetPosition({ 0, 0 });
	//camera.SetLimit({ {0,0}, { background.GetSize() - Engine::GetWindow().GetSize() } });

	mediator = new Mediator();

	map = new Map(mediator);
	mediator->SetMap(map);

	player = new Player({ map->Get_Tile_Length() * map->Get_Map_Size() / 2, map->Get_Tile_Length() * map->Get_Map_Size() / 2 }, camera, mediator, { map->Get_Map_Size() / 2, map->Get_Map_Size() / 2 });
	mediator->SetPlayer(player);

	// monsters
	mediator->SetMonsters(&monsters);
	//mediator->AddMonster({ 7500, 7500 });
	mediator->SetBullets(&bullets);

	map->MapMaking();
}

void Game::Update([[maybe_unused]] double dt) {
	player->Update(dt);
	map->Update(dt);
	for (Monster* monster : monsters) {
		monster->Update(dt, player->GetPosition());
	}
	for (Bullet* bullet : bullets) {
		bullet->Update(dt);
	}
	camera.Update(player->GetPosition());

	if (player->GetHP() <= 0) {
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
	}


	if (Key == KeyboardButtons::Escape) {
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
	}


	for (Bullet* bullet : bullets) {
		if (map->GetTileState(bullet->GetPosition()) == TILES::WALL) {
			mediator->DeleteBullet(bullet);
		}
		for (Monster* monster : monsters) {
			if (monster->GetDistance(bullet->GetPosition()) < monster->GetSize()) {
				mediator->DeleteBullet(bullet);
				mediator->DeleteMonster(monster);
			}
		}
	}

	Math::vec2 middle_point{ (double)map->Get_Map_Length() / 2 + map->Get_Tile_Length() / 2, (double)map->Get_Map_Length() / 2 + map->Get_Tile_Length() / 2 };

	// Find the closest monster and set the target
	target = nullptr;
	for (Monster* monster : monsters) {
		if (target == nullptr || monster->GetDistance(middle_point) < target->GetDistance(middle_point))
			target = monster;
	}
	// Attack the target monster if it is not nullptr
	if (target != nullptr) {
		if ((target->GetDistance(middle_point) < map->Get_Tile_Length() * 15) && (tower_attack_count >= tower_attack_cool)) {
			mediator->AddBullet(middle_point, target->GetPosition() - middle_point);
			tower_attack_count = 0;
		}
	}
	// If there is no monster, set the target to the nullptr
	if (monsters.size() == 0)
		target = nullptr;

	tower_attack_count += dt;
}

void Game::Unload() {

}

void Game::Draw() {
	Engine::GetWindow().Clear(0x000000FF);

	Math::TransformationMatrix camera_matrix = camera.GetMatrix();

	push_settings();
	//apply_rotate(QUARTER_PI);
	apply_translate(-mediator->GetPlayerPosition().x + (double)Engine::GetWindow().GetSize().x / 2, -mediator->GetPlayerPosition().y + (double)Engine::GetWindow().GetSize().y / 2);

	push_settings();
	no_outline();
	map->Show_Map(player->GetTilePosition());
	pop_settings();

	player->Draw();

	for (Monster* monster : monsters) {
		monster->Draw();
	}
	for (Bullet* bullet : bullets) {
		bullet->Draw();
	}
	pop_settings();


	push_settings();
	set_font_size(25);
	
	//draw_text("Time: " + std::to_string((int)(map->GetTime() / map->GetDuration() * 100)) + "%", 0, 70);
	//draw_text("Resource: " + std::to_string(player->GetMapResource()) + ", " + std::to_string(player->GetMonsterResource()), 0, 50);
	//draw_text("Hp: " + std::to_string(player->GetHP()), 0, 30);

	draw_text("R1: " + std::to_string(player->GetMapResource()), Engine::GetWindow().GetSize().x - 150, Engine::GetWindow().GetSize().y - 50);
	draw_text("R2: " + std::to_string(player->GetMonsterResource()), Engine::GetWindow().GetSize().x - 150, Engine::GetWindow().GetSize().y - 80);
	draw_text("R3: " + std::to_string(player->GetWarpResource()), Engine::GetWindow().GetSize().x - 150, Engine::GetWindow().GetSize().y - 110);


	draw_text("C: " + std::to_string(map->GetColony()), Engine::GetWindow().GetSize().x - 150, 80);
	draw_text("M: " + std::to_string(monsters.size()), Engine::GetWindow().GetSize().x - 150, 50);

	draw_text("Hp: " + std::to_string(player->GetHP()), 0, 30);

	draw_text("Day " + std::to_string(map->GetDate()), (double)Engine::GetWindow().GetSize().x / 2 - 100, (double)Engine::GetWindow().GetSize().y - 50);
	draw_text("Time: " + std::to_string((int)(map->GetTime() / map->GetDuration() * 100)) + "%", (double)Engine::GetWindow().GetSize().x / 2 - 100, (double)Engine::GetWindow().GetSize().y - 80);

	pop_settings();
}