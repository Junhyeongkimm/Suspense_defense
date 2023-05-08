/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Texture.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
Updated:    March 21, 2023
*/

#pragma once

#include <doodle/image.hpp>
#include "Matrix.h"

namespace CS230 {
    class Texture {
    public:
        friend class TextureManager;
        void Draw(Math::TransformationMatrix display_matrix);
        void Draw(Math::TransformationMatrix display_matrix, Math::ivec2 texel_position, Math::ivec2 frame_size);

        Math::ivec2 GetSize();
    private:
        Texture(const std::filesystem::path& file_path);
        doodle::Image image;
    };
}
