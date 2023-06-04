#include "Monster.h"
#include "Mediator.h"
#include <vector>
#include <algorithm>
#include "State.h"
#include "AStar.h"

// Constructor
Monster::Monster(Math::vec2 position, Mediator* mediator) : position(position), mediator(mediator) {
	tile_position.x = (int)((position.x) / mediator->GetTileLength());
	tile_position.y = (int)((position.y) / mediator->GetTileLength());

	if (mediator->Is_Day()) {

		created_at_day = true;
		speed = 250;
	}
	else {

		created_at_day = false;
		speed = 175;
	}
		
}
// Update
void Monster::Update(double dt) {
	// Paralyze. Monster will do nothing while the paralyze_count is smaller than the paralyze_time
	paralyze_count += dt;
	if (paralyze_count < paralyze_time)
		return;
	// During the daytime, it will move to the player.
	if (created_at_day && (mediator->GetTileStateInt(mediator->GetPlayerTilePosition()) != BASE_INSIDE) && (mediator->GetTileStateInt(mediator->GetPlayerTilePosition()) != TOWER)) {
		
		Math::ivec2 target_tile = FindPath(tile_position, mediator->GetPlayerTilePosition(), mediator);
		Math::vec2 target = { ((double)target_tile.x + 1 / 2.0) * mediator->GetTileLength(), ((double)target_tile.y + 1 / 2.0) * mediator->GetTileLength() };
		direction = target - position;
		direction /= direction.GetLength();
		position += direction * speed * dt;
	}
	// During the night time, it will move to the base
	else {
		Math::vec2 middle_point{ mediator->GetMapLength() / 2 + mediator->GetTileLength()/2, mediator->GetMapLength() / 2 + mediator->GetTileLength()/2 };

		direction.x = (middle_point.x - position.x) / GetDistance(middle_point);
		direction.y = (middle_point.y - position.y) / GetDistance(middle_point);

		double half_size = size / 2.0;

		Math::vec2 next_position_x = { position.x + speed * dt * direction.x, position.y };
		Math::vec2 next_position_y = { position.x, position.y + speed * dt * direction.y };

		bool can_move_x = (
			mediator->GetTileState({ next_position_x.x - half_size, next_position_x.y }) != TILES::BASE_WALL &&
			mediator->GetTileState({ next_position_x.x + half_size, next_position_x.y }) != TILES::BASE_WALL);

		bool can_move_y = (
			mediator->GetTileState({ next_position_y.x, next_position_y.y - half_size }) != TILES::BASE_WALL &&
			mediator->GetTileState({ next_position_y.x, next_position_y.y + half_size }) != TILES::BASE_WALL);

		if (can_move_x) {
			position.x = next_position_x.x;
		}

		if (can_move_y) {
			position.y = next_position_y.y;
		}
	}
	// Tile position update
	tile_position.x = (int)((position.x) / mediator->GetTileLength());
	tile_position.y = (int)((position.y) / mediator->GetTileLength());

	if (mediator->GetTileStateInt({ tile_position.x + 1, tile_position.y }) == TILES::BASE_WALL) {
		mediator->BaseAttacked({ tile_position.x + 1, tile_position.y });
	}
	if (mediator->GetTileStateInt({ tile_position.x - 1, tile_position.y }) == TILES::BASE_WALL) {
		mediator->BaseAttacked({ tile_position.x - 1, tile_position.y });
	}
	if (mediator->GetTileStateInt({ tile_position.x, tile_position.y + 1 }) == TILES::BASE_WALL) {
		mediator->BaseAttacked({ tile_position.x, tile_position.y + 1 });
	}
	if (mediator->GetTileStateInt({ tile_position.x, tile_position.y - 1 }) == TILES::BASE_WALL) {
		mediator->BaseAttacked({ tile_position.x, tile_position.y - 1 });
	}

	if (mediator->GetTileStateInt(tile_position) == TILES::TOWER) {
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
	}

}
// Draw
void Monster::Draw() {
	push_settings();
	set_fill_color(HexColor(0x888888ff));
	draw_ellipse(position.x, position.y, size);
	pop_settings();
}
// Getter distance from the monster to the target
double Monster::GetDistance(Math::vec2 target) {
	return sqrt((position.x - target.x) * (position.x - target.x) + (position.y - target.y) * (position.y - target.y));
}
// Reduce hp
void Monster::Reduce_hp() {
	hp -= mediator->GetDamage();
}
// Check attaced, check died
void Monster::Attacked(Math::vec2 attack_position) {
	if (GetDistance(attack_position) < size / 2) {
		Reduce_hp();
		if (hp <= 0) {
			mediator->DeleteMonster(this);
		}
	}
}
// Destructor
Monster::~Monster() {

}