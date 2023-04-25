#include <iostream>
#include <doodle/doodle.hpp>
#include "MapMaking.h"
#include "Player.h"
#include "Game.h"

using namespace doodle;
using namespace std;

Player player;
Map map(player);
std::vector<Monster*>monsters;
Game game;

int main(void) {
	
	create_window(Width, Height);
	//set_frame_of_reference(FrameOfReference::RightHanded_OriginBottomLeft);
	
	game.Load();

	while (!is_window_closed()) {
		
		update_window();

		clear_background(255);

		game.Update();
		game.Draw();
	}
	

	return 0;
}