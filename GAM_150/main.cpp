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
#include "Game/Game.h"

int main() {
    try {
        Engine& engine = Engine::Instance();
        engine.Start("Suspense Defense");

        Splash splash;
        engine.GetGameStateManager().AddGameState(splash);
        Game game;
        engine.GetGameStateManager().AddGameState(game);

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
