#include "Game.h"
#include <doodle/doodle.hpp>
using namespace doodle;

extern Player player;
extern std::vector<Monster*>monsters;

Game::Game() : player(), map(player) {
	
}
void Game::Load() {
	map.MapMaking();
	//monsters.push_back(new Monster({ 10, 0 }));

}
void Game::Update() {
	
	player.Update(map);
	
	for (int i = 0; i < monsters.size(); i++) {
		monsters[i]->Update(player);
	}
	/*
	for (Monster* monster : monsters) {
		monster->Update(player);
	}
	*/
}

void Game::Draw() {
	push_settings();

	apply_translate(-player.Get_Position().x, -player.Get_Position().y);

	push_settings();

	no_outline();
	map.Show_Map();

	pop_settings();

	player.Draw();

	for (Monster* monster : monsters) {
		monster->Draw();
	}

	pop_settings();

	player.Draw_UI();
}