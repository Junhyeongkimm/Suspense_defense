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
			draw_text("Player\t", position.x, position.y + 150);
			set_font_size(20);
			draw_text("Base\t", position.x + 150, position.y + 150);
			draw_text("Exit", position.x + 300, position.y + 150);

			draw_text("Upgrade player's \nattack or utility", position.x + 25, position.y + 100);
			break;
		case 1:
			set_font_size(25);
			draw_text("Base\t", position.x + 150, position.y + 150);
			set_font_size(20);
			draw_text("Player\t", position.x, position.y + 150);
			draw_text("Exit", position.x + 300, position.y + 150);

			draw_text("Upgrade base or \nrepair base", position.x + 25, position.y + 100);
			break;
		case 2:
			set_font_size(25);
			draw_text("Exit", position.x + 300, position.y + 150);
			set_font_size(20);
			draw_text("Player\t", position.x, position.y + 150);
			draw_text("Base\t", position.x + 150, position.y + 150);

			draw_text("Exit", position.x + 25, position.y + 100);
			break;
		}
		break;
	case 1:
		switch (menu) {
		case 0:
			set_font_size(25);
			draw_text("Attack\t", position.x, position.y + 150);
			set_font_size(20);
			draw_text("Utility\t", position.x + 150, position.y + 150);
			draw_text("Exit", position.x + 300, position.y + 150);

			draw_text("Upgrade attack\nSomething -> Something\n You need " + std::to_string(mediator->GetPlayer()->GetAttackUpgradeCost()) + " map resources", position.x + 25, position.y + 100);
			break;
		case 1:
			set_font_size(25);
			draw_text("Utility\t", position.x + 150, position.y + 150);
			set_font_size(20);
			draw_text("Attack\t", position.x, position.y + 150);
			draw_text("Exit", position.x + 300, position.y + 150);

			draw_text("Upgrade utility\nSomething -> Something\nYou need " + std::to_string(mediator->GetPlayer()->GetUtilityUpgradeCost()) + " map resources", position.x + 25, position.y + 100);
			break;
		case 2:
			set_font_size(25);
			draw_text("Exit", position.x + 300, position.y + 150);
			set_font_size(20);
			draw_text("Attack\t", position.x, position.y + 150);
			draw_text("Utility\t", position.x + 150, position.y + 150);

			draw_text("Exit", position.x + 25, position.y + 100);
			break;
		}
		break;
	case 2:
		switch (menu) {
		case 0:
			set_font_size(25);
			draw_text("Upgrade\t", position.x, position.y + 150);
			set_font_size(20);
			draw_text("Repair\t", position.x + 150, position.y + 150);
			draw_text("Exit", position.x + 300, position.y + 150);

			draw_text("Upgrade base\nPlayer maximum upgrade ? - > ?\nYou need " + std::to_string(mediator->GetMap()->GetUpgradeCost()) + " map resources", position.x + 25, position.y + 100);
			break;
		case 1:
			set_font_size(25);
			draw_text("Repair\t", position.x + 150, position.y + 150);
			set_font_size(20);
			draw_text("Upgrade\t", position.x, position.y + 150);
			draw_text("Exit", position.x + 300, position.y + 150);

			draw_text("Repiar base\nYou need " + std::to_string(mediator->GetMap()->GetRepairCost() / 2) + "monster resources", position.x + 25, position.y + 100);
			break;
		case 2:
			set_font_size(25);
			draw_text("Exit", position.x + 300, position.y + 150);
			set_font_size(20);
			draw_text("Upgrade\t", position.x, position.y + 150);
			draw_text("Repair\t", position.x + 150, position.y + 150);

			draw_text("Exit", position.x + 25, position.y + 100);
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
				mediator->GetPlayer()->Attack_Upgrade();
				break;
			case 1:
				// upgrade utility
				mediator->GetPlayer()->Utility_Upgrade();
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
				mediator->GetMap()->UpgradeBase();
				break;
			case 1:
				// repair base
				mediator->GetMap()->RepairBase();
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