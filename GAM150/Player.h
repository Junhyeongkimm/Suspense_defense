#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Vec2.h"

class Map;

class Player {
private:
	Vec2 position;
	inline static const double size = 50;
	inline static const double speed = 500;
	bool is_attacking = false;
	double attack_count = 0;
	inline static const double attack_delay = 0.5;

	double start_mouse_x = 0;
	double start_mouse_y = 0;

	int x_position_index = 0;
	int y_position_index = 0;
	int right_position_index = 0;
	int left_position_index = 0;
	int up_position_index = 0;
	int down_position_index = 0;

	int hp = 10;
	inline static const double invincibility_time = 1.0;
	double invincibility_count = 0;

	Vec2 attack_point;

	int resource = 0;
public:
	Player();
	void Draw();
	void Update(Map& map);
	Vec2 Get_Position();
	Vec2 Attack(double x, double y);
	void Draw_UI();
};

#endif