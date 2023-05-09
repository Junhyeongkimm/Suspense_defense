#include "Game.h"
#include "State.h"
#include "../Engine/Engine.h"
#include <vector>
#include "doodle/input.hpp"
#include "doodle/angle.hpp"

using namespace doodle;

//Player*player, std::vector<Monster*>monsters, Map*map, Mediator* mediator
Game::Game() : 
	camera({ { 0.15 * Engine::GetWindow().GetSize().x, 0 }, { 0.35 * Engine::GetWindow().GetSize().x, 0 } }),
	player(nullptr), monsters(), map(nullptr), mediator(nullptr)
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

	map->MapMaking();
}

void Game::Update([[maybe_unused]] double dt) {
	player->Update(dt);
	map->Update(dt);
	for (Monster* monster : monsters) {
		monster->Update(dt, player->GetPosition());
	}
	camera.Update(player->GetPosition());

	if (player->GetHP() <= 0) {
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
	}


	if (Key == KeyboardButtons::Escape) {
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
	}

	static bool not_clicked = false;

	if (!MouseIsPressed) {
		not_clicked = true;
	}
	if (MouseIsPressed && not_clicked) {
		if (player->Able_To_Attack()) {
			player->Attack();
		}
		player->SetAttackPosition(player->GetAttackPosition());
		//attack_position = GetAttackPosition();
		//monsters.push_back(new Monster(player->GetAttackPosition(), mediator));
		not_clicked = false;
	}
}

void Game::Unload() {

}
#include <iostream>
void Game::Draw() {
	Engine::GetWindow().Clear(0x000000FF);

	Math::TransformationMatrix camera_matrix = camera.GetMatrix();

	push_settings();
	//apply_rotate(QUARTER_PI);
	apply_translate(-mediator->GetPlayerPosition().x + Engine::GetWindow().GetSize().x / 2, -mediator->GetPlayerPosition().y + Engine::GetWindow().GetSize().y / 2);

	push_settings();
	no_outline();
	map->Show_Map(player->GetTilePosition());
	pop_settings();

	player->Draw();

	for (Monster* monster : monsters) {
		monster->Draw();
	}
	pop_settings();


	push_settings();
	set_font_size(25);
	
	//draw_text("Time: " + std::to_string((int)(map->GetTime() / map->GetDuration() * 100)) + "%", 0, 70);
	draw_text("Resource: " + std::to_string(player->GetMapResource()) + ", " + std::to_string(player->GetMonsterResource()), 0, 50);
	draw_text("Hp: " + std::to_string(player->GetHP()), 0, 30);
	pop_settings();
}