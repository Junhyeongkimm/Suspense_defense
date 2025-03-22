/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Engine.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
Updated:    March 20, 2023
*/

#pragma once
#include "Window.h"
#include "Logger.h"
#include "Input.h"
#include "GameStateManager.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "MusicManager.h"
#include <chrono>


class Engine {
public:
    static Engine& Instance() {
        static Engine instance;
        return instance;
    }
    static CS230::Logger& GetLogger() {
        return Instance().logger;
    }
    static CS230::Window& GetWindow() {
        return Instance().window;
    }
    static CS230::GameStateManager& GetGameStateManager() {
        return Instance().gameStateManager;
    }
    static CS230::Input& GetInput() {
        return Instance().input;
    }
    static CS230::TextureManager& GetTextureManager() {
        return Instance().textureManager;
    }
    static CS230::SoundManager& GetSoundsManager()
    {
        return Instance().soundmanager;
    }
    static CS230::MusicManager& GetMusicManager()
    {
        return Instance().musicmanager;
    }

    void Start(std::string window_title);
    void Stop();
    void Update();
    bool HasGameEnded();

private:
    std::chrono::system_clock::time_point last_tick = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point last_test;

    int frame_count = 0;

    static constexpr double TargetFPS = 30.0;
    static constexpr int FPSDuration = 5;
    static constexpr int FPSTargetFrames = static_cast<int>(FPSDuration * TargetFPS);



    Engine();
    ~Engine();
    CS230::MusicManager musicmanager;
    CS230::SoundManager soundmanager;
    CS230::Logger logger;
    CS230::Input input;
    CS230::Window window;
    CS230::GameStateManager gameStateManager;
    CS230::TextureManager textureManager;
};


