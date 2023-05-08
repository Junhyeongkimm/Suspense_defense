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
	for (Monster* monster : monsters) {
		monster->Update(dt, player->GetPosition());
	}
	camera.Update(player->GetPosition());

	if (Key == KeyboardButtons::Escape) {
		Engine::GetGameStateManager().ClearNextGameState();
	}

	static bool not_clicked = false;

	if (!MouseIsPressed) {
		not_clicked = true;
	}
	if (MouseIsPressed && not_clicked) {
		if (player->Able_To_Attack()) {
			player->Attack();
		}
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
	//apply_translate(-player->GetPosition().x + Engine::GetWindow().GetSize().x / 2, -player->GetPosition().y + Engine::GetWindow().GetSize().y / 2);
	apply_translate(-mediator->GetPlayerPosition().x + Engine::GetWindow().GetSize().x / 2, -mediator->GetPlayerPosition().y + Engine::GetWindow().GetSize().y / 2);
	map->Show_Map(player->GetTilePosition());
	player->Draw();
	for (Monster* monster : monsters) {
		monster->Draw();
	}
	pop_settings();
}