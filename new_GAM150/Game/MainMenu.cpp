#include "../Engine/Engine.h"
#include "State.h"
#include "MainMenu.h"
#include "doodle/drawing.hpp"
#include "doodle/input.hpp"

using namespace doodle;
// Need to be updated

MainMenu::MainMenu():texture(texture), playbutton(playbutton), howtoplaybutton(howtoplaybutton), creditbutton(creditbutton), exitbutton(exitbutton), loading(loading),
                    selectcreditbutton(selectcreditbutton), selectexitbutton(selectexitbutton), selecthowtoplaybutton(selecthowtoplaybutton), 
                    selectplaybutton(selectplaybutton), music(nullptr)
{ }

void MainMenu::Load() {
    music = Engine::GetMusicManager().Load("Assets/Music/MainMenu.wav");
    texture = Engine::GetTextureManager().Load("Assets/maintitle.png");
    playbutton = Engine::GetTextureManager().Load("Assets/playbutton.png");
    howtoplaybutton = Engine::GetTextureManager().Load("Assets/howtoplaybutton.png");
    creditbutton = Engine::GetTextureManager().Load("Assets/creditbutton.png");
    exitbutton = Engine::GetTextureManager().Load("Assets/exit.png");

    selectplaybutton = Engine::GetTextureManager().Load("Assets/selectplaybutton.png");
    selecthowtoplaybutton = Engine::GetTextureManager().Load("Assets/selecthowtoplaybutton.png");
    selectcreditbutton = Engine::GetTextureManager().Load("Assets/selectcreditbutton.png");
    selectexitbutton = Engine::GetTextureManager().Load("Assets/selectexit.png");

    loading = Engine::GetTextureManager().Load("Assets/loading.png");
    music->play();
    music->setLoop(true);
}

void MainMenu::Draw() {
    Engine::GetWindow().Clear(UINT_MAX);
    texture->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - texture->GetSize()) / 2.0 }));
    if (menu == 0)
    {
        selectplaybutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - selectplaybutton->GetSize().x) / 10 }, { (Engine::GetWindow().GetSize().y - selectplaybutton->GetSize().y) - 300 })));
        howtoplaybutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - howtoplaybutton->GetSize().x) / 10 }, { (Engine::GetWindow().GetSize().y - howtoplaybutton->GetSize().y) - 420 })));
        creditbutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - creditbutton->GetSize().x) / 10 }, { (Engine::GetWindow().GetSize().y - creditbutton->GetSize().y) - 540 })));
        exitbutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - selectcreditbutton->GetSize().x) / 10 }, { (Engine::GetWindow().GetSize().y - selectcreditbutton->GetSize().y) - 660 })));
    }
    if (menu == 1)
    {
        playbutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - playbutton->GetSize().x) / 10 }, { (Engine::GetWindow().GetSize().y - playbutton->GetSize().y) - 300 })));
        selecthowtoplaybutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - selecthowtoplaybutton->GetSize().x) / 10 }, { (Engine::GetWindow().GetSize().y - selecthowtoplaybutton->GetSize().y) - 420 })));
        creditbutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - creditbutton->GetSize().x) / 10 }, { (Engine::GetWindow().GetSize().y - creditbutton->GetSize().y) - 540 })));
        exitbutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - selectcreditbutton->GetSize().x) /10 }, { (Engine::GetWindow().GetSize().y - selectcreditbutton->GetSize().y) - 660 })));
    }
    if (menu == 2)
    {
        playbutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - playbutton->GetSize().x) / 10 }, { (Engine::GetWindow().GetSize().y - playbutton->GetSize().y) - 300 })));
        howtoplaybutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - howtoplaybutton->GetSize().x) / 10 }, { (Engine::GetWindow().GetSize().y - howtoplaybutton->GetSize().y) - 420 })));
        selectcreditbutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - selectcreditbutton->GetSize().x) / 10 }, { (Engine::GetWindow().GetSize().y - selectcreditbutton->GetSize().y) - 540 })));
        exitbutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - selectcreditbutton->GetSize().x) /10 }, { (Engine::GetWindow().GetSize().y - selectcreditbutton->GetSize().y) - 660 })));

    }
    if (menu == 3)
    {
        playbutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - playbutton->GetSize().x) / 10 }, { (Engine::GetWindow().GetSize().y - playbutton->GetSize().y) - 300 })));
        howtoplaybutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - howtoplaybutton->GetSize().x) / 10 }, { (Engine::GetWindow().GetSize().y - howtoplaybutton->GetSize().y) - 420 })));
        creditbutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - selectcreditbutton->GetSize().x) / 10 }, { (Engine::GetWindow().GetSize().y - selectcreditbutton->GetSize().y) - 540 })));
        selectexitbutton->Draw(Math::TranslationMatrix(Math::ivec2({ (Engine::GetWindow().GetSize().x - selectcreditbutton->GetSize().x) / 10 }, { (Engine::GetWindow().GetSize().y - selectcreditbutton->GetSize().y) - 660 })));
    }

   
    
  
}

void MainMenu::Update([[maybe_unused]] double dt) {

	if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::W)) {
		menu = (menu - 1) % 4;
	}
	if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::S)) {
		menu = (menu + 1) % 4;
	}


	if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Enter)) {
		switch (menu) {
		case 0:
			Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Game));
			loading->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - loading->GetSize()) / 2.0 }));
			break;
		case 1:
			Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::HowToPlay));
			break;
		case 2:
			Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Credit));
			break;
		case 3:
			Engine::GetGameStateManager().ClearNextGameState();
			break;
		}
	}
}

void MainMenu::Unload() {
    music->stop();
}
