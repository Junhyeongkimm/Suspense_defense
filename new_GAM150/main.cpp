/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  main.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Hyeonjoon Nam
Created:    March 8, 2023
Updated:    April 28, 2023
*/

#include <iostream>
#include "Engine/Engine.h"
#include "Game/Splash.h"
#include "Game/Splash1.h"
#include "Game/Splash2.h"
#include "Game/Game.h"
#include "Game/MainMenu.h"

#include <Windows.h>

void make_window_not_resizable()
{
    HWND window_handle = GetActiveWindow();
    SetWindowLong(window_handle, GWL_STYLE, GetWindowLong(window_handle, GWL_STYLE) & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX);
}

int main() {
    try {
        Engine& engine = Engine::Instance();
        engine.Start("Suspense Defense");
        Splash splash;
        engine.GetGameStateManager().AddGameState(splash);
        Splash1 splash1;
        engine.GetGameStateManager().AddGameState(splash1);
        Splash2 splash2;
        engine.GetGameStateManager().AddGameState(splash2);
        MainMenu mainmenu;
        engine.GetGameStateManager().AddGameState(mainmenu);
        Game game;
        engine.GetGameStateManager().AddGameState(game);

        make_window_not_resizable();
        while (engine.HasGameEnded() == false) {
            engine.Update();
        }

        engine.Stop();

        return 0;
    }
    catch (std::exception& e) {
        std::cerr << e.what() << "\n";
        return -1;
    }
}
