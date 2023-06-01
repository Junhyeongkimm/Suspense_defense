/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  TextureManager.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
Updated:    April 26, 2023
*/

#include "TextureManager.h"
#include "Engine.h"
#include "Texture.h"

CS230::Texture* CS230::TextureManager::Load(const std::filesystem::path& file_path) {
    auto find = textures.find(file_path);
    if (find != textures.end()) {
        //Engine::GetLogger().LogEvent("Loading texture: " + file_path.string());
        return find->second;
    }
    else {
        Texture* texture = new Texture(file_path.string());
        textures[file_path] = texture;
        Engine::GetLogger().LogEvent("Loading texture: " + file_path.string());
        return texture;
    }
}

void CS230::TextureManager::Unload()
{
    for (auto& tex : textures) {
        delete tex.second;
    }
    Engine::GetLogger().LogEvent("Clearing texture");
    textures.clear();
}
