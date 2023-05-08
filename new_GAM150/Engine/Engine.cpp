/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Engine.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
Updated:    March 20, 2023
*/

#pragma once
#include "Engine.h"

Engine::Engine() :
#ifdef _DEBUG				
    logger(CS230::Logger::Severity::Debug, true, last_tick)
#else 						
    logger(CS230::Logger::Severity::Event, false, last_tick)
#endif
{
    last_tick = std::chrono::system_clock::now();
    frame_count = 0;
}
Engine::~Engine() {}

void Engine::Start(std::string window_title) {
    unsigned int seed = (unsigned int)time(NULL);
    srand(seed);
    logger.LogEvent("Seed: " + std::to_string(seed));

    logger.LogEvent("Engine Started");
    window.Start(window_title);
    last_test = last_tick;
}



void Engine::Stop() {
    logger.LogEvent("Engine Stopped");
}

void Engine::Update() {
    auto now = std::chrono::system_clock::now();
    std::chrono::duration<double> now_and_tick = now - last_tick;
    double dt = 0;
    dt = now_and_tick.count();

    double FPSUpdate = 1.0 / TargetFPS;

    if (dt >= FPSUpdate) {

        logger.LogVerbose("Engine Update");
        last_tick = now;

        frame_count++;

        gameStateManager.Update(dt);
        //input.Update();
        window.Update();

        if (frame_count >= FPSTargetFrames)
        {
            std::chrono::duration<double> now_and_test = now - last_test;
            double actual_time = frame_count / now_and_test.count();
            logger.LogDebug("FPS: " + std::to_string(actual_time));
            frame_count = 0;
            last_test = now;
        }
    }
}

bool Engine::HasGameEnded() {
    return  gameStateManager.HasGameEnded();
}
