/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Window.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 17, 2023
Updated:    March 17, 2023
*/

#include <string>
#include "Vec2.h"
#include <doodle/window.hpp>

void on_window_resized(int, int);

namespace CS230 {
    class Window {
    public:
        void Start(std::string title);
        void Update();
        Math::ivec2 GetSize();
        void Clear(unsigned int color);
    private:
        static constexpr unsigned int default_background = UINT_MAX;

        friend void ::on_window_resized(int, int);
        Math::ivec2 window_size;
        static constexpr int default_width = 1000;
        static constexpr int default_height = 750;
    };
}



