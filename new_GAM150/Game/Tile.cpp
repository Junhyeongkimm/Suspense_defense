#include "Tile.h"
#include "TileStates.h"

// Forward declare to declare vector tiles
class Tile;
std::vector<Tile*> tiles;

// Constructor
Tile::Tile(Math::vec2 position) : position(position) {
	
}
// Update
void Tile::Update() {

}
// Draw based on it is day or night
void Tile::Draw(bool is_day) {
	//draw_rectangle(position.x, position.y, size, size);
}
// Getter function
int Tile::Get_State() {
	return state;
}
// Check attcked6
void Tile::Attacked(Math::vec2 attack_point) {
	if (attack_point.x > position.x && attack_point.x < position.x + size && attack_point.y > position.y && attack_point.y < position.y + size) {
		--hp;
	}
}
// Check attacked and return true or false
bool Tile::Attacked(Math::vec2 attack_point, int i) {
	if (attack_point.x > position.x && attack_point.x < position.x + size && attack_point.y > position.y && attack_point.y < position.y + size) {
		--hp;
		return true;
	}
	return false;
}
// ---------------------------------------------------------------------------------------------------
// Tiles below are very similar. The major difference is hp and state.


#include <iostream>

// Wall
Wall::Wall(Math::vec2 position) : Tile(position) {
	tiles.push_back(this);
	state = TILES::WALL;
	hp = 2;

	sprite.Load("Assets/rock.spt");
	scale_x = size / static_cast<double>(sprite.GetFrameSize().x);
	scale_y = size / static_cast<double>(sprite.GetFrameSize().y);
	sprite.PlayAnimation(static_cast<int>(rock_animations::basic));
}
void Wall::Update() {
	/*if (hp == 1 && rockbroken == false){
		rockbroken = true;
		std::cout << "broken \n";
		sprite.PlayAnimation(static_cast<int>(rock_animations::broken));
	}*/
}
void Wall::Draw(bool is_day) {
	doodle::push_settings();
	//if (is_day) {
	//	if (hp == 2)
	//		set_fill_color(HexColor{ 0x444444ff });
	//	else if (hp == 1){}
	//		set_fill_color(HexColor{ 0x888888ff });

	//}
	//else {
	//	if (hp == 2)
	//		/*set_fill_color(HexColor{ 0x000000ff });*/
	//	else if (hp == 1)
	//		/*set_fill_color(HexColor{ 0x444444ff }*/);
	//}
	//draw_rectangle(position.x, position.y, size, size);
	if (hp == 1 && rockbroken == false) {
		rockbroken = true;
		std::cout << "broken \n";
		sprite.PlayAnimation(static_cast<int>(rock_animations::broken));
	}

	sprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ scale_x, scale_y })));
	doodle::pop_settings();
}
void Wall::Attacked() {
	--hp;
}
// Void
Void::Void(Math::vec2 position) : Tile(position) {
	state = TILES::VOID;
	sprite.Load("Assets/tile.spt");
	scale_x = size / static_cast<double>(sprite.GetFrameSize().x);
	scale_y = size / static_cast<double>(sprite.GetFrameSize().y);
	sprite.PlayAnimation(static_cast<int>(void_animations::basic));
}
void Void::Update() {

}
void Void::Draw(bool is_day) {
	doodle::push_settings();
	if (is_day) {
		sprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ scale_x, scale_y })));
	}
	else {
		sprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ scale_x, scale_y })));
	}
	
	doodle::pop_settings();
}
// Colony_Core
Colony_Core::Colony_Core(Math::vec2 position) : Tile(position) {
	state = TILES::COLONY_CORE;
	hp = 3;
}
void Colony_Core::Update() {

}
void Colony_Core::Draw(bool is_day) {
	doodle::push_settings();
	if (is_day) {
		set_fill_color(HexColor{ 0x882222ff });
	}
	else {
		set_fill_color(HexColor{ 0x440000ff });
	}
	
	draw_rectangle(position.x, position.y, size, size);
	doodle::pop_settings();
}
void Colony_Core::Attacked() {
	--hp;
}
// Colony_Side
Colony_Side::Colony_Side(Math::vec2 position) : Tile(position) {
	state = TILES::COLONY_SIDE;
	hp = 2;
}
void Colony_Side::Update() {

}
void Colony_Side::Draw(bool is_day) {
	doodle::push_settings();
	if (is_day) {
		set_fill_color(HexColor{ 0x664444ff });
	}
	else {
		set_fill_color(HexColor{ 0x220000ff });
	}
	
	draw_rectangle(position.x, position.y, size, size);
	doodle::pop_settings();
}
void Colony_Side::Attacked() {
	//--hp;
}
// Base_Wall
Base_Wall::Base_Wall(Math::vec2 position) : Tile(position) {
	state = TILES::BASE_WALL;
	hp = 10;
	sprite.Load("Assets/wall.spt");
	scale_x = size / static_cast<double>(sprite.GetFrameSize().x);
	scale_y = size / static_cast<double>(sprite.GetFrameSize().y);
	sprite.PlayAnimation(static_cast<int>(basewall_animations::basic));
}
void Base_Wall::Update() {

}
void Base_Wall::Draw(bool is_day) {
	doodle::push_settings();
	if (is_day) {
		sprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ scale_x, scale_y })));
	}
	else {
		sprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ scale_x, scale_y })));
	}
	
	doodle::pop_settings();
}
void Base_Wall::Attacked() {
	--hp;
}
// Base_Inside
Base_Inside::Base_Inside(Math::vec2 position) : Tile(position) {
	state = TILES::BASE_INSIDE;
	sprite.Load("Assets/wallinside.spt");
	scale_x = size / static_cast<double>(sprite.GetFrameSize().x);
	scale_y = size / static_cast<double>(sprite.GetFrameSize().y);
	sprite.PlayAnimation(static_cast<int>(baseinside_animations::basic));
}
void Base_Inside::Update() {
	
}
void Base_Inside::Draw(bool is_day) {
	doodle::push_settings();
	if (is_day) {
		sprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ scale_x, scale_y })));
	}
	else {
		sprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ scale_x, scale_y })));
	}
	doodle::pop_settings();
}
// Resource
Resource::Resource(Math::vec2 position) : Tile(position) {
	state = TILES::RESOURCE;
	hp = 3;
	sprite.Load("Assets/resource.spt");
	scale_x = size / static_cast<double>(sprite.GetFrameSize().x);
	scale_y = size / static_cast<double>(sprite.GetFrameSize().y);
	sprite.PlayAnimation(static_cast<int>(resource_animations::basic));
}
void Resource::Update() {
	
}
void Resource::Draw(bool is_day) {
	doodle::push_settings();
	/*if (is_day) {
		set_fill_color(HexColor{ 0xffd966ff });
	}
	else {
		set_fill_color(HexColor{ 0xbb9522ff });
	}*/
	sprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ scale_x, scale_y })));
	doodle::pop_settings();
}
void Resource::Attacked() {
	--hp;
}
// Warp
Warp::Warp(Math::vec2 position) : Tile(position) {
	state = TILES::WARP;
	hp = 2;
	sprite.Load("Assets/portalresource.spt");
	scale_x = size / static_cast<double>(sprite.GetFrameSize().x);
	scale_y = size / static_cast<double>(sprite.GetFrameSize().y);
	sprite.PlayAnimation(static_cast<int>(warp_resource_animations::basic));
}
void Warp::Update() {

}
void Warp::Draw(bool is_day) {
	push_settings();
	/*if (is_day) {
		set_fill_color(HexColor{ 0x0000ffff });
	}
	else {
		set_fill_color(HexColor{ 0x0000ffff });
	}

	draw_rectangle(position.x, position.y, size);*/
	if (hp == 1 && warpbroken == false) {
		warpbroken = true;
		std::cout << "broken \n";
		sprite.PlayAnimation(static_cast<int>(warp_resource_animations::broken));
	}
	sprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ scale_x, scale_y })));
	pop_settings();
}
// Tower
Tower::Tower(Math::vec2 position) : Tile(position) {
	state = TILES::TOWER;
	hp = 10; sprite.Load("Assets/basecore.spt");
	scale_x = size / static_cast<double>(sprite.GetFrameSize().x);
	scale_y = size / static_cast<double>(sprite.GetFrameSize().y);
	sprite.PlayAnimation(static_cast<int>(Tower_animations::basic));
	
}
void Tower::Update() {

}
void Tower::Draw(bool is_day) {
	push_settings();
	/*if (is_day) {
		set_fill_color(HexColor{ 0x0000ffff });
	}
	else {
		set_fill_color(HexColor{ 0x0000ffff });
	}*/
	sprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ scale_x, scale_y })));
	pop_settings();
}
