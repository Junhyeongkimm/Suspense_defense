/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Sprite.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    April 28, 2023
*/

#include "Sprite.h"
#include "../Engine/Texture.h"
#include "../Engine/Engine.h"
#include <iostream>

using namespace std;

CS230::Sprite::Sprite() : current_animation(0), texture(texture)
{ }

CS230::Sprite::~Sprite() {
    for (int i = 0; i < animations.size(); i++) {
        delete animations[i];
    }
    animations.clear();
}

void CS230::Sprite::Update(double dt) {

    animations[current_animation]->Update(dt);
}

void CS230::Sprite::Load(const std::filesystem::path& sprite_file) {
    animations.clear();

    if (sprite_file.extension() != ".spt") {
        throw std::runtime_error(sprite_file.generic_string() + " is not a .spt file");
    }
    std::ifstream in_file(sprite_file);

    if (in_file.is_open() == false) {
        throw std::runtime_error("Failed to load " + sprite_file.generic_string());
    }

    hotspots.clear(); 
    frame_texels.clear();

    std::string text;
    in_file >> text;
    texture = Engine::GetTextureManager().Load(text);
    frame_size = texture->GetSize();

    in_file >> text;
    while (in_file.eof() == false) {
        if (text == "FrameSize") {
            in_file >> frame_size.x;
            in_file >> frame_size.y;
        }
        else if (text == "NumFrames") {
            int frame_count;
            in_file >> frame_count;
            for (int i = 0; i < frame_count; i++) {
                frame_texels.push_back({ frame_size.x * i, 0 });
            }
        }
        else if (text == "Frame") {
            int frame_location_x, frame_location_y;
            in_file >> frame_location_x;
            in_file >> frame_location_y;
            frame_texels.push_back({ frame_location_x, frame_location_y });
        }
        else if (text == "HotSpot") {
            int hotspot_x, hotspot_y;
            in_file >> hotspot_x;
            in_file >> hotspot_y;
            hotspots.push_back({ hotspot_x, hotspot_y });
        }
        else if (text == "Anim") {
            std::string animation_path;
            in_file >> animation_path;
            animations.push_back(new Animation(animation_path));
        }
        else {
            Engine::GetLogger().LogError("Unknown command: " + text);
        }
        in_file >> text;
    }
    if (frame_texels.empty() == true) {
        frame_texels.push_back({ 0,0 });
    }

    if (animations.empty() == true) {
        animations.push_back(new Animation());
        PlayAnimation(0);
    }
}


Math::ivec2 CS230::Sprite::GetHotSpot(int index)
{
    if (index < 0 || index >= hotspots.size()) {
        //std::cout << "Error: Invalid hotspot index\n";
        return Math::ivec2(0, 0);
    }
    return hotspots[index];
}

Math::ivec2 CS230::Sprite::GetFrameSize()
{
    return frame_size;

}

void CS230::Sprite::PlayAnimation(int animation)
{

    if (animation < 0 || animation >= animations.size()) {
        Engine::GetLogger().LogError(" animation doesn't exist (Sprite::PlayAnimation)");
        return;
    }
    else {
        if (animation != current_animation)
        {
            current_animation = animation;
            animations[current_animation]->Reset();
        }
    }

}

bool CS230::Sprite::AnimationEnded()
{
    if (animations[current_animation]->Ended()) {
        return true;
    }

    return false;
}

Math::ivec2 CS230::Sprite::GetFrameTexel(int index) const
{
    if (index >= 0 && index < frame_texels.size()) {
        return frame_texels[index];
    }
    else {
        Engine::GetLogger().LogError("Invalid index ! (Sprite::GetFrameTexel");
        return { 0,0 };
    }
}

void CS230::Sprite::Draw(Math::TransformationMatrix display_matrix) {
    int current_frame = animations[current_animation]->CurrentFrame();
    texture->Draw(display_matrix * Math::TranslationMatrix(-GetHotSpot(0)), GetFrameTexel(current_frame), GetFrameSize());
}