/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  TextureManager.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
Updated:    April 24, 2023
*/

#pragma once
#include <filesystem>
#include <map>

namespace CS230 {
    class Texture;

    class TextureManager {
    public:
        Texture* Load(const std::filesystem::path& file_path);
        void Unload();

    private:
        std::map<std::filesystem::path, Texture*> textures;
    };
}
