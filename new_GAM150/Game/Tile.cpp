#include "Tile.h"
#include "TileStates.h"

class Tile;
std::vector<Tile*> tiles;

Tile::Tile(Math::vec2 position) : position(position) {

}

void Tile::Update() {

}

void Tile::Draw() {
	//draw_rectangle(position.x, position.y, size, size);
}

int Tile::Get_State() {
	return state;
}

void Tile::Attacked(Math::vec2 attack_point) {
	if (attack_point.x > position.x && attack_point.x < position.x + size && attack_point.y > position.y && attack_point.y < position.y + size) {
		--hp;
	}
}

// ---------------------------------------------------------------------------------------------------

Wall::Wall(Math::vec2 position) : Tile(position) {
	tiles.push_back(this);
	state = TILES::WALL;
	hp = 2;
}
void Wall::Update() {

}
void Wall::Draw() {
	doodle::push_settings();
	if (hp == 2)
		set_fill_color(HexColor{ 0x0000ffff });
	else if (hp == 1)
		set_fill_color(HexColor{ 0x000088ff });
	draw_rectangle(position.x, position.y, size, size);
	doodle::pop_settings();
}
void Wall::Attacked() {
	--hp;
}

Void::Void(Math::vec2 position) : Tile(position) {
	state = TILES::VOID;
}
void Void::Update() {

}
void Void::Draw() {
	doodle::push_settings();
	set_fill_color(HexColor{ 0xffffffff });
	draw_rectangle(position.x, position.y, size, size);
	doodle::pop_settings();
}

Colony_Core::Colony_Core(Math::vec2 position) : Tile(position) {
	state = TILES::COLONY_CORE;
	hp = 1;
}
void Colony_Core::Update() {

}
void Colony_Core::Draw() {
	doodle::push_settings();
	set_fill_color(HexColor{ 0x660000ff });
	draw_rectangle(position.x, position.y, size, size);
	doodle::pop_settings();
}
void Colony_Core::Attacked() {
	--hp;
}

Colony_Side::Colony_Side(Math::vec2 position) : Tile(position) {
	state = TILES::COLONY_SIDE;
	hp = 2;
}
void Colony_Side::Update() {

}
void Colony_Side::Draw() {
	doodle::push_settings();
	set_fill_color(HexColor{ 0x440000ff });
	draw_rectangle(position.x, position.y, size, size);
	doodle::pop_settings();
}
void Colony_Side::Attacked() {
	--hp;
}

Base_Wall::Base_Wall(Math::vec2 position) : Tile(position) {
	state = TILES::BASE_WALL;
	hp = 10;
}
void Base_Wall::Update() {

}
void Base_Wall::Draw() {
	doodle::push_settings();
	set_fill_color(HexColor{ 0x274e13ff });
	draw_rectangle(position.x, position.y, size, size);
	doodle::pop_settings();
}
void Base_Wall::Attacked() {
	--hp;
}


Base_Inside::Base_Inside(Math::vec2 position) : Tile(position) {
	state = TILES::BASE_INSIDE;
}
void Base_Inside::Update() {
	
}
void Base_Inside::Draw() {
	doodle::push_settings();
	set_fill_color(HexColor{ 0xffffffff });
	draw_rectangle(position.x, position.y, size, size);
	doodle::pop_settings();
}

Resource::Resource(Math::vec2 position) : Tile(position) {
	state = TILES::RESOURCE;
}
void Resource::Update() {
	
}
void Resource::Draw() {
	doodle::push_settings();
	set_fill_color(HexColor{ 0xffd966ff });
	draw_rectangle(position.x, position.y, size, size);
	doodle::pop_settings();
}