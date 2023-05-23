#include "Tile.h"
#include "TileStates.h"

class Tile;
std::vector<Tile*> tiles;

Tile::Tile(Math::vec2 position) : position(position) {

}

void Tile::Update() {

}

void Tile::Draw(bool is_day) {
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

bool Tile::Attacked(Math::vec2 attack_point, int i) {
	if (attack_point.x > position.x && attack_point.x < position.x + size && attack_point.y > position.y && attack_point.y < position.y + size) {
		--hp;
		return true;
	}
	return false;
}

// ---------------------------------------------------------------------------------------------------

Wall::Wall(Math::vec2 position) : Tile(position) {
	tiles.push_back(this);
	state = TILES::WALL;
	hp = 2;
}
void Wall::Update() {

}
void Wall::Draw(bool is_day) {
	doodle::push_settings();
	if (is_day) {
		if (hp == 2)
			set_fill_color(HexColor{ 0x444444ff });
		else if (hp == 1)
			set_fill_color(HexColor{ 0x888888ff });
	}
	else {
		if (hp == 2)
			set_fill_color(HexColor{ 0x000000ff });
		else if (hp == 1)
			set_fill_color(HexColor{ 0x444444ff });
	}
	
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
void Void::Draw(bool is_day) {
	doodle::push_settings();
	if (is_day) {
		set_fill_color(HexColor{ 0xffffffff });
	}
	else {
		set_fill_color(HexColor{ 0xbbbbbbff });
	}
	
	draw_rectangle(position.x, position.y, size, size);
	doodle::pop_settings();
}

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

Base_Wall::Base_Wall(Math::vec2 position) : Tile(position) {
	state = TILES::BASE_WALL;
	hp = 10;
}
void Base_Wall::Update() {

}
void Base_Wall::Draw(bool is_day) {
	doodle::push_settings();
	if (is_day) {
		set_fill_color(HexColor{ 0x496f35ff });
	}
	else {
		set_fill_color(HexColor{ 0x052c01ff });
	}
	
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
void Base_Inside::Draw(bool is_day) {
	doodle::push_settings();
	if (is_day) {
		set_fill_color(HexColor{ 0xffffffff });
	}
	else {
		set_fill_color(HexColor{ 0xbbbbbbff });
	}
	
	draw_rectangle(position.x, position.y, size, size);
	doodle::pop_settings();
}

Resource::Resource(Math::vec2 position) : Tile(position) {
	state = TILES::RESOURCE;
	hp = 1;
}
void Resource::Update() {
	
}
void Resource::Draw(bool is_day) {
	doodle::push_settings();
	if (is_day) {
		set_fill_color(HexColor{ 0xffd966ff });
	}
	else {
		set_fill_color(HexColor{ 0xbb9522ff });
	}
	
	draw_rectangle(position.x, position.y, size, size);
	doodle::pop_settings();
}

Warp::Warp(Math::vec2 position) : Tile(position) {
	state = TILES::WARP;
	hp = 1;
}
void Warp::Update() {

}
void Warp::Draw(bool is_day) {
	push_settings();
	if (is_day) {
		set_fill_color(HexColor{ 0x0000ffff });
	}
	else {
		set_fill_color(HexColor{ 0x0000ffff });
	}

	draw_rectangle(position.x, position.y, size);
	pop_settings();
}

Tower::Tower(Math::vec2 position) : Tile(position) {
	state = TILES::TOWER;
	hp = 10;
}
void Tower::Update() {

}
void Tower::Draw(bool is_day) {
	push_settings();
	if (is_day) {
		set_fill_color(HexColor{ 0x0000ffff });
	}
	else {
		set_fill_color(HexColor{ 0x0000ffff });
	}

	draw_rectangle(position.x, position.y, size);
	pop_settings();
}
