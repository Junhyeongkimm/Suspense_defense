#include "PopupBox.h"
#include <doodle/drawing.hpp>
#include <doodle/environment.hpp>
#include "../Engine/Input.h"
#include "../Engine/Engine.h"
#include "Mediator.h"
#include <string>
using namespace doodle;

PopupBox::PopupBox(Mediator* mediator) : mediator(mediator), table(table) {
	table = Engine::GetTextureManager().Load("Assets/popupbox.png");
}
void PopupBox::Draw() {

	push_settings();
	set_font_size(25);
	table->Draw(Math::TranslationMatrix{ Math::ivec2{static_cast<int>(position.x),static_cast<int>(position.y)} } *Math::ScaleMatrix{ (1.05, 1.05) });
	push_settings();
	apply_translate(20, 0);
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
		{
			set_font_size(25);
			draw_text("Attack\t", position.x, position.y + 150);
			set_font_size(20);
			draw_text("Utility\t", position.x + 150, position.y + 150);
			draw_text("Exit", position.x + 300, position.y + 150);

			if (mediator->GetPlayer()->GetAttackUpgradeCount() == mediator->GetPlayer()->GetMaximumUpgrade()) {
				draw_text("You cannont upgrade more", position.x + 25, position.y + 100);
			}
			else {
				std::string str1 = std::to_string(mediator->GetPlayer()->GetAttackDelay());
				std::string str2 = std::to_string(mediator->GetPlayer()->GetAttackDelay() - 0.1);
				size_t pos1 = str1.find('.');
				size_t pos2 = str2.find('.');
				if (pos1 != std::string::npos && pos1 + 2 < str1.length()) {
					str1 = str1.substr(0, pos1 + 2 + 1);
				}
				if (pos2 != std::string::npos && pos2 + 2 < str2.length()) {
					str2 = str2.substr(0, pos2 + 2 + 1);
				}
				draw_text("Upgrade attack\n" + str1 + "->" + str2 + "\n You need " + std::to_string(mediator->GetPlayer()->GetAttackUpgradeCost()) + " map resources", position.x + 25, position.y + 100);
			}
			break;
		}
		case 1:
		{
			set_font_size(25);
			draw_text("Utility\t", position.x + 150, position.y + 150);
			set_font_size(20);
			draw_text("Attack\t", position.x, position.y + 150);
			draw_text("Exit", position.x + 300, position.y + 150);

			if (mediator->GetPlayer()->GetUtilityUpgradeCount() == mediator->GetPlayer()->GetMaximumUpgrade()) {
				draw_text("You cannont upgrade more", position.x + 25, position.y + 100);
			}
			else {
				int hp_gap = (mediator->GetPlayer()->GetUtilityUpgradeCount() % 2 == 0) ? 2 : 3;
				draw_text("Upgrade utility\nSpeed: " +
					std::to_string((int)mediator->GetPlayer()->GetSpeed()) + "->" + std::to_string((int)mediator->GetPlayer()->GetSpeed() + 25) +
					"\nMax hp: " + std::to_string(mediator->GetPlayer()->GetMaxHP()) + "->" + std::to_string(mediator->GetPlayer()->GetMaxHP() + hp_gap) +
					"\nYou need " + std::to_string(mediator->GetPlayer()->GetUtilityUpgradeCost()) + " map resources", position.x + 25, position.y + 100);
			}
			break;
		}
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

			if (!(mediator->GetMap()->GetUpgradeCount() == mediator->GetMap()->GetUpgradeMax())) {
				draw_text("Upgrade base\nPlayer upgrade max " + std::to_string(mediator->GetPlayer()->GetMaximumUpgrade()) + "->" + std::to_string(mediator->GetPlayer()->GetMaximumUpgrade() + 2) +
					"\nBase wall max hp + 5" +
					"\nTower attack delay -0.1"
					"\nYou need " + std::to_string(mediator->GetMap()->GetUpgradeCost()) + " monster resources", position.x + 25, position.y + 100);
			}
			else {
				draw_text("You cannot upgrade more", position.x + 25, position.y + 100);
			}
			break;
		case 1:
			set_font_size(25);
			draw_text("Repair\t", position.x + 150, position.y + 150);
			set_font_size(20);
			draw_text("Upgrade\t", position.x, position.y + 150);
			draw_text("Exit", position.x + 300, position.y + 150);

			if (mediator->GetMap()->GetRepairCost() == 0) {
				draw_text("All walls have full hp", position.x + 25, position.y + 100);
			}
			else {
				draw_text("Repiar base\nYou need " + std::to_string(mediator->GetMap()->GetRepairCost()) + "monster resources", position.x + 25, position.y + 100);
			}
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
				if (!(mediator->GetPlayer()->GetAttackUpgradeCount() == mediator->GetPlayer()->GetMaximumUpgrade())) {
					mediator->GetPlayer()->Attack_Upgrade();
				}
				break;
			case 1:
				// upgrade utility
				if (!(mediator->GetPlayer()->GetUtilityUpgradeCount() == mediator->GetPlayer()->GetMaximumUpgrade())) {
					mediator->GetPlayer()->Utility_Upgrade();
				}
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
				if (!(mediator->GetMap()->GetUpgradeCount() == mediator->GetMap()->GetUpgradeMax())) {
					mediator->GetMap()->UpgradeBase();
				}
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