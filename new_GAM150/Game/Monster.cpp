#include "Monster.h"
#include "Mediator.h"
#include <vector>
#include <algorithm>
#include "State.h"
#include "AStar.h"

void Monster::ColonySetWantScale(Math::vec2 new_scale)
{
	Math::ivec2 want = colonymonstersprite.GetFrameSize();
	scale_x = 1 / static_cast<double>(want.x) * new_scale.x;
	scale_y = 1 / static_cast<double>(want.y) * new_scale.y;
}
void Monster::FlySetWantScale(Math::vec2 new_scale)
{
	Math::ivec2 want = flymonstersprite.GetFrameSize();
	scale_x = 1 / static_cast<double>(want.x) * new_scale.x;
	scale_y = 1 / static_cast<double>(want.y) * new_scale.y;
}
// Constructor
Monster::Monster(Math::vec2 position, Mediator* mediator, bool created_by_boss) 
	: position(position), mediator(mediator), created_by_boss(created_by_boss) {
	tile_position.x = (int)((position.x) / mediator->GetMap()->Get_Tile_Length());
	tile_position.y = (int)((position.y) / mediator->GetMap()->Get_Tile_Length());
	
	if (mediator->GetMap()->IsDay() || created_by_boss) {
		colonymonstersprite.Load("Assets/colonymonster.spt");
		colonymonstersprite.PlayAnimation(static_cast<int>(colonymonster_action::left));
		ColonySetWantScale({ 60,60 });
		created_at_day = true;
		colonymonstertype = true;
		speed = mediator->GetPlayer()->GetSpeed();
	}
	else {
		flymonstersprite.Load("Assets/flymonster.spt");
		flymonstersprite.PlayAnimation(static_cast<int>(flymonster_action::flymove1));
		FlySetWantScale({ 60,60 });
		created_at_day = false;
		flymonstertype = true;
		speed = mediator->GetPlayer()->GetSpeed() / 2;
		
	}
		
}
// Update
void Monster::Update(double dt) {
	// Paralyze. Monster will do nothing while the paralyze_count is smaller than the paralyze_time
	//is_monstermoving = false;
	paralyze_count += dt;
	if (paralyze_count < paralyze_time)
		return;
	// During the daytime, it will move to the player.
	if (created_at_day && (mediator->GetMap()->GetTileStateInt(mediator->GetPlayer()->GetTilePosition()) != BASE_INSIDE) && (mediator->GetMap()->GetTileStateInt(mediator->GetPlayer()->GetTilePosition()) != TOWER)) {
		

		Math::ivec2 target_tile = FindPath(tile_position, mediator->GetPlayer()->GetTilePosition(), mediator);
		Math::vec2 target = { ((double)target_tile.x + 1 / 2.0) * mediator->GetMap()->Get_Tile_Length(), ((double)target_tile.y + 1 / 2.0) * mediator->GetMap()->Get_Tile_Length() };
		direction = target - position;
		direction /= direction.GetLength();
		position += direction * speed * dt;
		if (direction.x <= 0)
		{
			colonymonstersprite.PlayAnimation(static_cast<int>(colonymonster_action::left));
		}
		else
		{
			colonymonstersprite.PlayAnimation(static_cast<int>(colonymonster_action::right));
		}
		colonymonstersprite.Update(dt);
	}
	// During the night time, it will move to the base
	else {
		flymonstersprite.PlayAnimation(static_cast<int>(flymonster_action::flymove1));
		Math::vec2 middle_point{ mediator->GetMap()->Get_Map_Length() / 2 + mediator->GetMap()->Get_Tile_Length()/2, mediator->GetMap()->Get_Map_Length() / 2 + mediator->GetMap()->Get_Tile_Length()/2 };

		direction.x = (middle_point.x - position.x) / GetDistance(middle_point);
		direction.y = (middle_point.y - position.y) / GetDistance(middle_point);

		double half_size = size / 2.0;

		Math::vec2 next_position_x = { position.x + speed * dt * direction.x, position.y };
		Math::vec2 next_position_y = { position.x, position.y + speed * dt * direction.y };

		bool can_move_x = (
			mediator->GetMap()->GetTileState({ next_position_x.x - half_size, next_position_x.y }) != TILES::BASE_WALL &&
			mediator->GetMap()->GetTileState({ next_position_x.x + half_size, next_position_x.y }) != TILES::BASE_WALL);

		bool can_move_y = (
			mediator->GetMap()->GetTileState({ next_position_y.x, next_position_y.y - half_size }) != TILES::BASE_WALL &&
			mediator->GetMap()->GetTileState({ next_position_y.x, next_position_y.y + half_size }) != TILES::BASE_WALL);

		if (can_move_x) {
			position.x = next_position_x.x;
		}

		if (can_move_y) {
			position.y = next_position_y.y;
		}
		
		if (direction.x <= 0)
		{
			flymonstersprite.PlayAnimation(static_cast<int>(flymonster_action::flymove1));
		}
		else
		{
			flymonstersprite.PlayAnimation(static_cast<int>(flymonster_action::flymove2));
		}
		flymonstersprite.Update(dt);

	}
	// Tile position update
	tile_position.x = (int)((position.x) / mediator->GetMap()->Get_Tile_Length());
	tile_position.y = (int)((position.y) / mediator->GetMap()->Get_Tile_Length());

	if (mediator->GetMap()->GetTileStateInt({ tile_position.x + 1, tile_position.y }) == TILES::BASE_WALL) {
		mediator->BaseAttacked({ tile_position.x + 1, tile_position.y });
	}
	if (mediator->GetMap()->GetTileStateInt({ tile_position.x - 1, tile_position.y }) == TILES::BASE_WALL) {
		mediator->BaseAttacked({ tile_position.x - 1, tile_position.y });
	}
	if (mediator->GetMap()->GetTileStateInt({ tile_position.x, tile_position.y + 1 }) == TILES::BASE_WALL) {
		mediator->BaseAttacked({ tile_position.x, tile_position.y + 1 });
	}
	if (mediator->GetMap()->GetTileStateInt({ tile_position.x, tile_position.y - 1 }) == TILES::BASE_WALL) {
		mediator->BaseAttacked({ tile_position.x, tile_position.y - 1 });
	}

	if (mediator->GetMap()->GetTileStateInt(tile_position) == TILES::TOWER) {
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
	}
	

}
// Draw
void Monster::Draw() {
	if (colonymonstertype == true)
	{
		colonymonstersprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ scale_x, scale_y })));
	}
	if(flymonstertype == true)
	{ 
		flymonstersprite.Draw((Math::TranslationMatrix(position) * Math::ScaleMatrix({ scale_x, scale_y })));
	}
	

}
// Getter distance from the monster to the target
double Monster::GetDistance(Math::vec2 target) {
	return sqrt((position.x - target.x) * (position.x - target.x) + (position.y - target.y) * (position.y - target.y));
}
// Reduce hp
void Monster::Reduce_hp(int damage) {
	hp -= damage;
}
// Destructor
Monster::~Monster() {

}