#include "PopupBox.h"
#include <doodle/drawing.hpp>
#include <doodle/environment.hpp>
#include "../Engine/Input.h"
#include "../Engine/Engine.h"
#include "Mediator.h"
using namespace doodle;

PopupBox::PopupBox(Mediator* mediator) : mediator(mediator) {

}
void PopupBox::Draw() {

	push_settings();
	set_font_size(25);
	draw_rectangle(position.x, position.y, width, height);

	switch (state) {
	case 0:
		switch (menu) {
		case 0:
			set_font_size(25);
			draw_text("Player\t", position.x, position.y);
			set_font_size(20);
			draw_text("Base\t", position.x + 150, position.y);
			draw_text("Exit", position.x + 300, position.y);
			break;
		case 1:
			set_font_size(25);
			draw_text("Base\t", position.x + 150, position.y);
			set_font_size(20);
			draw_text("Player\t", position.x, position.y);
			draw_text("Exit", position.x + 300, position.y);
			break;
		case 2:
			set_font_size(25);
			draw_text("Exit", position.x + 300, position.y);
			set_font_size(20);
			draw_text("Player\t", position.x, position.y);
			draw_text("Base\t", position.x + 150, position.y);
			break;
		}
		break;
	case 1:
		switch (menu) {
		case 0:
			set_font_size(25);
			draw_text("Attack\t", position.x, position.y);
			set_font_size(20);
			draw_text("Utility\t", position.x + 150, position.y);
			draw_text("Exit", position.x + 300, position.y);
			break;
		case 1:
			set_font_size(25);
			draw_text("Utility\t", position.x + 150, position.y);
			set_font_size(20);
			draw_text("Attack\t", position.x, position.y);
			draw_text("Exit", position.x + 300, position.y);
			break;
		case 2:
			set_font_size(25);
			draw_text("Exit", position.x + 300, position.y);
			set_font_size(20);
			draw_text("Attack\t", position.x, position.y);
			draw_text("Utility\t", position.x + 150, position.y);
			break;
		}
		break;
	case 2:
		switch (menu) {
		case 0:
			set_font_size(25);
			draw_text("Upgrade\t", position.x, position.y);
			set_font_size(20);
			draw_text("Repair\t", position.x + 150, position.y);
			draw_text("Exit", position.x + 300, position.y);
			break;
		case 1:
			set_font_size(25);
			draw_text("Repair\t", position.x + 150, position.y);
			set_font_size(20);
			draw_text("Upgrade\t", position.x, position.y);
			draw_text("Exit", position.x + 300, position.y);
			break;
		case 2:
			set_font_size(25);
			draw_text("Exit", position.x + 300, position.y);
			set_font_size(20);
			draw_text("Upgrade\t", position.x, position.y);
			draw_text("Repair\t", position.x + 150, position.y);
			break;
		}
		break;
	}

	pop_settings();
}

void PopupBox::Update() {
	if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::A)) {
		menu = (menu + 2) % 3;
	}
	else if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::D)) {
		menu = (menu + 1) % 3;
	}
	
	if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::E)) {
		std::cout << "State: " << state << ", " << "Menu: " << menu << std::endl;
		switch (state) {
		case 0:
			switch (menu) {
			case 0:
				state = 1; // player upgrade
				break;
			case 1:
				state = 2; // base upgrade
				break;
			case 2:
				Deactivate();
				break;
			}
			menu = 0;
			break;
		case 1:
			switch (menu) {
			case 0:
				// upgrade attack
				mediator->UpgradePlayerAttack();
				break;
			case 1:
				// upgrade utility
				mediator->UpgradePlayerUtility();
				break;
			case 2:
				break;
			}
			Deactivate();
			break;
		case 2:
			switch (menu) {
			case 0:
				// upgrade base
				break;
			case 1:
				// repair base
				break;
			case 2:
				// exit
				break;
			}
			Deactivate();
			break;
		}
	}
}