#include "Player.h"
#include <map>
#include <vector>
#include <doodle/doodle.hpp>
#include "MapMaking.h"
#include "Monster.h"

using namespace doodle;

extern Player player;
extern std::vector<Monster*>monsters;

#define PRESSED         true
#define NOT_PRESSED     false

std::map<KeyboardButtons, bool> buttons = {
	{ KeyboardButtons::W, NOT_PRESSED },
	{ KeyboardButtons::S, NOT_PRESSED },
	{ KeyboardButtons::A, NOT_PRESSED },
	{ KeyboardButtons::D, NOT_PRESSED },
};

void on_key_pressed(KeyboardButtons button) {
	buttons[button] = PRESSED;
}

void on_key_released(KeyboardButtons button) {
	buttons[button] = NOT_PRESSED;
}

Player::Player() { }

void Player::Draw() {
	push_settings();
	set_fill_color(127);
	draw_ellipse(position.x, position.y, size);
	pop_settings();
	if (is_attacking) {
		push_settings();
		set_outline_width(20);
		draw_line(position.x, position.y, position.x + start_mouse_x, position.y + start_mouse_y);
		pop_settings();
	}
}

void Player::Draw_UI() {
	push_settings();
	set_font_size(20);
	draw_text("Resource: " + std::to_string(resource), Width / 3, Height / 3);
	draw_text("HP: " + std::to_string(hp), Width / 3, Height / 3 + 50);
	pop_settings();
}
#include <iostream>
void Player::Update(Map &map) {
	x_position_index = ((int)position.x  + (int)map.screen_width / 2) / (int)map.tile_width;
	y_position_index = ((int)position.y  + (int)map.screen_height / 2) / (int)map.tile_height;
	right_position_index = ((int)position.x + (int)size / 2 +(int)map.screen_width/2) / (int)map.tile_width;
	left_position_index = ((int)position.x - (int)size / 2 + (int)map.screen_width / 2) / (int)map.tile_width;
	up_position_index = ((int)position.y + (int)size / 2 + (int)map.screen_height / 2) / (int)map.tile_height;
	down_position_index = ((int)position.y - (int)size / 2 + (int)map.screen_height / 2) / (int)map.tile_height;

	if (buttons[KeyboardButtons::W] && map.MAP[x_position_index][up_position_index] != map.TILES::WALL && map.MAP[x_position_index][up_position_index] != map.TILES::BROKEN_WALL)
		position.y += speed * DeltaTime;
	if (buttons[KeyboardButtons::S] && map.MAP[x_position_index][down_position_index] != map.TILES::WALL && map.MAP[x_position_index][down_position_index] != map.TILES::BROKEN_WALL)
		position.y -= speed * DeltaTime;
	if (buttons[KeyboardButtons::A] && map.MAP[left_position_index][y_position_index] != map.TILES::WALL && map.MAP[left_position_index][y_position_index] != map.TILES::BROKEN_WALL)
		position.x -= speed * DeltaTime;
	if (buttons[KeyboardButtons::D] && map.MAP[right_position_index][y_position_index] != map.TILES::WALL && map.MAP[right_position_index][y_position_index] != map.TILES::BROKEN_WALL)
		position.x += speed * DeltaTime;

	static bool not_clicked = false;
	if (!MouseIsPressed) {
		not_clicked = true;
	}
	if (MouseIsPressed && not_clicked == true && is_attacking == false) {

		for (Monster* monster : monsters) {
			if (monster->Get_Distance(position.x + start_mouse_x, position.y + start_mouse_y) < monster->Get_Size() / 2) {
				monsters.erase(remove(monsters.begin(), monsters.end(), monster), monsters.end());
			}
		}

		is_attacking = true;
		double attack_distance = sqrt(get_mouse_x() * get_mouse_x() + get_mouse_y() * get_mouse_y());
		start_mouse_x = size * get_mouse_x() / attack_distance ;
		start_mouse_y = size * get_mouse_y() / attack_distance ;

		int attackpoint_x_index = (int)(start_mouse_x + map.screen_width / 2 + position.x) / (int)map.tile_width;
		int attackpoint_y_index = (int)(start_mouse_y + map.screen_height / 2 + position.y) / (int)map.tile_height;

		if (map.MAP[attackpoint_x_index][attackpoint_y_index] == map.TILES::WALL) {
			map.Change(attackpoint_x_index, attackpoint_y_index, map.TILES::BROKEN_WALL);
		} else if(map.MAP[attackpoint_x_index][attackpoint_y_index] == map.TILES::BROKEN_WALL) {
			map.Change(attackpoint_x_index, attackpoint_y_index, map.TILES::VOID);
		}
		else if (map.MAP[attackpoint_x_index][attackpoint_y_index] == map.TILES::COLONY_CORE) {
			for (int x = attackpoint_x_index - 1; x <= attackpoint_x_index + 1; x++) {
				for (int y = attackpoint_y_index - 1; y <= attackpoint_y_index + 1; y++) {
					map.Change(x, y, map.TILES::VOID);
				}
			}
			monsters.push_back(new Monster({ attackpoint_x_index * map.tile_width - map.screen_width/2, attackpoint_y_index * map.tile_height-map.screen_height/2 }));
			//monsters.push_back(new Monster({ position.x, position.y }));
			//std::cout << start_mouse_x << ", " << start_mouse_y << std::endl;
			//monsters.push_back(new Monster({ 0, 0}));
		}
		else if (map.MAP[attackpoint_x_index][attackpoint_y_index] == map.TILES::RESOURCE) {
			map.Change(attackpoint_x_index, attackpoint_y_index, map.TILES::VOID);
			resource++;
		}
			
		

		not_clicked = false;
	}

	if (is_attacking == true && attack_count < attack_delay) {
		attack_point = Attack(start_mouse_x, start_mouse_y);
		attack_count += DeltaTime;
	}
	if (is_attacking == true && attack_count >= attack_delay) {
		attack_count = 0;
		is_attacking = false;
	}


	for (Monster* monster : monsters) {
		if (monster->Get_Distance(position.x, position.y) < monster->Get_Size() / 2 && invincibility_count >= invincibility_time) {
			//monsters.erase(remove(monsters.begin(), monsters.end(), monster), monsters.end());
			hp--;
			invincibility_count = 0;
		}
	}
	invincibility_count += DeltaTime;
}

Vec2 Player::Get_Position() {
	return position;
}

Vec2 Player::Attack(double x, double y) {
	push_settings();
	set_outline_width(30);
	double distance = sqrt(x * x + y * y);
	//draw_line(position.x, position.y, 50 * x / distance, 50 * y / distance);
	pop_settings();
	return { 50 * x / distance, 50 * y / distance };
}