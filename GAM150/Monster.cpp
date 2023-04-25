#include "Monster.h"
#include "Player.h"
#include <doodle/doodle.hpp>
#include "MapMaking.h"
using namespace doodle;


class Monster;
extern std::vector<Monster*>monsters;
extern Map map;
#include <iostream>
Monster::Monster(Vec2 Position) : Position(Position) {
	//std::cout << "Created!" << std::endl;
}
void Monster::Update(Player player) {
	double distance = sqrt((player.Get_Position().x - Position.x) * (player.Get_Position().x - Position.x) + (player.Get_Position().y - Position.y) * (player.Get_Position().y - Position.y));
	double x_direction = (player.Get_Position().x - Position.x) / distance;
	double y_direction = (player.Get_Position().y - Position.y) / distance;

	Position.x += x_direction * speed * DeltaTime;
	Position.y += y_direction * speed * DeltaTime;

}
void Monster::Draw() {
	push_settings();

	set_fill_color(0x666666ff);
	draw_ellipse(Position.x, Position.y, size, size);

	pop_settings();
}
Vec2 Monster::Get_Position() {
	return Position;
}
double Monster::Get_Distance(double x, double y) {
	return sqrt((Position.x - x) * (Position.x - x) + (Position.y - y) * (Position.y - y));
}
double Monster::Get_Size() {
	return size;
}
Monster::~Monster() {
	//std::cout << "Deleted!" << std::endl;
}