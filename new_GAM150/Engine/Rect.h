/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Rect.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    April 7, 2023
*/

#include "vec2.h"

namespace Math {
    struct rect {
        Math::vec2 bottom_left{ 0.0, 0.0 };
        Math::vec2 top_right{ 0.0, 0.0 };
    };
    struct irect {
        Math::ivec2 bottom_left{ 0, 0 };
        Math::ivec2 top_right{ 0, 0 };
    };
}
