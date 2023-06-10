#include "Tile.h"
#include "TileStates.h"

// Forward declare to declare vector tiles
class Tile;
std::vector<Tile*> tiles;

// Constructor
Tile::Tile(Math::vec2 position) : position(position) {
	scale_x = 0;
	scale_y = 0;
}
// Update
void Tile::Update(double dt) {

}
// Draw based on it is day or night
void Tile::Draw(bool is_day) {

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

void Wall::Update(double dt) {

}
void Wall::Draw(bool is_day) {
	if (hp == 1 && rockbroken == false) {
		rockbroken = true;
		sprite.PlayAnimation(static_cast<int>(rock_animations::broken));
	}

	sprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ scale_x, scale_y })));
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
void Void::Update(double dt) {

}
void Void::Draw(bool is_day) {
	if (is_day) {
		sprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ scale_x, scale_y })));
	}
	else {
		sprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ scale_x, scale_y })));
	}
}
// Colony_Core
Colony_Core::Colony_Core(Math::vec2 position) : Tile(position) {
	state = TILES::COLONY_CORE;
	hp = 3;
	sprite.Load("Assets/colony_core.spt");
	scale_x = size / static_cast<double>(sprite.GetFrameSize().x);
	scale_y = size / static_cast<double>(sprite.GetFrameSize().y);
	sprite.PlayAnimation(static_cast<int>(colonycore_animations::basic));
}
void Colony_Core::Update(double dt) {

}
void Colony_Core::Draw(bool is_day) {
	if (hp == 2 && colonyattacked == false) {
		colonyattacked = true;
		sprite.PlayAnimation(static_cast<int>(colonycore_animations::attacked1));
	}
	if (hp == 1 && colonybroken == false) {
		colonybroken = true;
		sprite.PlayAnimation(static_cast<int>(colonycore_animations::attacked2));
	}
	sprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ scale_x, scale_y })));
}
// Colony_Side
Colony_Side::Colony_Side(Math::vec2 position) : Tile(position) {
	state = TILES::COLONY_SIDE;
	hp = 2;
	sprite.Load("Assets/colonyside.spt");
	scale_x = size / static_cast<double>(sprite.GetFrameSize().x);
	scale_y = size / static_cast<double>(sprite.GetFrameSize().y);
	sprite.PlayAnimation(static_cast<int>(colony_side::basic));
}
void Colony_Side::Update(double dt) {

}
void Colony_Side::Draw(bool is_day) {
	
	sprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ scale_x, scale_y })));
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
void Base_Wall::Update(double dt) {
	invincibility_count += dt;
}
void Base_Wall::Draw(bool is_day) {
		sprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ scale_x, scale_y })));
	
}
bool Base_Wall::AbleToBeAttacked() { 
	if (invincibility_count > invincibility_time) { 
		invincibility_count = 0; 
		return true; 
	} 
	else { 
		return false; 
	} 
}
void Base_Wall::Attacked() {
	if (AbleToBeAttacked()) {
		--hp;
	}
}
// Base_Inside
Base_Inside::Base_Inside(Math::vec2 position) : Tile(position) {
	state = TILES::BASE_INSIDE;
	sprite.Load("Assets/wallinside.spt");
	scale_x = size / static_cast<double>(sprite.GetFrameSize().x);
	scale_y = size / static_cast<double>(sprite.GetFrameSize().y);
	sprite.PlayAnimation(static_cast<int>(baseinside_animations::basic));
}
void Base_Inside::Update(double dt) {

}
void Base_Inside::Draw(bool is_day) {
	
	sprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ scale_x, scale_y })));

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
void Resource::Update(double dt) {

}
void Resource::Draw(bool is_day) {
	if (hp == 2 && resourceattacked == false) {
		resourceattacked = true;
	
		sprite.PlayAnimation(static_cast<int>(resource_animations::attacked));
	}
	if (hp == 1 && resourcebroken == false) {
		resourcebroken = true;
		sprite.PlayAnimation(static_cast<int>(resource_animations::broken));
	}
	sprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ scale_x, scale_y })));
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
void Warp::Update(double dt) {

}
void Warp::Draw(bool is_day) {

	if (hp == 1 && warpbroken == false) {
		warpbroken = true;
		sprite.PlayAnimation(static_cast<int>(warp_resource_animations::broken));
	}
	sprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ scale_x, scale_y })));

}
// Tower


Tower::Tower(Math::vec2 position) : Tile(position) {
	state = TILES::TOWER;
	hp = 10;
	sprite.Load("Assets/basecore.spt");
	scale_x = size / static_cast<double>(sprite.GetFrameSize().x);
	scale_y = size / static_cast<double>(sprite.GetFrameSize().y);
	sprite.PlayAnimation(static_cast<int>(Tower_animations::None));
}
void Tower::Update(double dt) {

}
void Tower::Draw(bool is_day) {
	sprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ scale_x, scale_y })));
}

// Treasure
Treasure::Treasure(Math::vec2 position) : Tile(position) {
	state = TILES::TREASURE;
	hp = 3;
	sprite.Load("Assets/chest.spt");
	scale_x = size / static_cast<double>(sprite.GetFrameSize().x);
	scale_y = size / static_cast<double>(sprite.GetFrameSize().y);
	sprite.PlayAnimation(static_cast<int>(treasure_animations::None));
}
void Treasure::Update(double dt) {

}
void Treasure::Draw(bool is_day) {

	if (hp == 1 && treasurebroken == false) {
		treasurebroken = true;
		sprite.PlayAnimation(static_cast<int>(treasure_animations::broken));
	}
	sprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ scale_x, scale_y })));

}