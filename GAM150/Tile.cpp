#include "Tile.h"

Tile::Tile(Vec2 position, double size, HexColor color, int state, int hp) : position(position), size(size), color(color), state(state), hp(hp) {

}
void Tile::Update() {

}
void Tile::Draw() {
	push_settings();
	switch (state) {
	case 0:
		set_fill_color(color);
		break;
	case 1:
		set_fill_color(color);
		break;
	case 2:
		set_fill_color(color);
		break;
	case 3:
		set_fill_color(color);
		break;
	case 4:
		set_fill_color(color);
		break;
	}
	draw_rectangle(position.x, position.y, size, size);
	pop_settings();
}
void Tile::Change_State(int state) {
	this->state = state;
}
int Tile::Get_State() {
	return state;
}
void Tile::Check_Attacked(Vec2 pos) {
	if (state == 0 && position.x <= pos.x && position.x + size >= pos.x && position.y <= pos.y && position.y + size <= pos.y) {
		hp--;
		if (hp <= 0) {
			state = 1;
		}
	}
}