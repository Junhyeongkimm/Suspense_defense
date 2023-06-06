#include "PopupBox.h"
#include <doodle/drawing.hpp>
#include <doodle/environment.hpp>

using namespace doodle;

PopupBox::PopupBox(Math::vec2 position, double width, double height, std::string string) : position(position), width(width), height(height), string(string) {

}
void PopupBox::Draw() {
	push_settings();
	set_font_size(25);
	draw_rectangle(position.x, position.y, width, height);
	draw_text(string, position.x, position.y);
	pop_settings();
}
void PopupBox::Update() {

}