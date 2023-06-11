#include <doodle/input.hpp>
#include "Input.h"
#include "../Engine/Engine.h"

CS230::Input::Input() {
    keys_down.resize(static_cast<int>(Keys::Unknown));
    previous_keys_down.resize(static_cast<int>(Keys::Unknown));
}

void CS230::Input::Update() {
    previous_keys_down = keys_down;
}

void CS230::Input::SetKeyDown(Keys key, bool value) {
    keys_down[static_cast<int>(key)] = value;
}

CS230::Input::Keys convert_doodle_to_cs230(doodle::KeyboardButtons doodle_key) {
    switch (doodle_key) {
    case doodle::KeyboardButtons::A:
        return CS230::Input::Keys::A;
    case doodle::KeyboardButtons::B:
        return CS230::Input::Keys::B;
    case doodle::KeyboardButtons::C:
        return CS230::Input::Keys::C;
    case doodle::KeyboardButtons::D:
        return CS230::Input::Keys::D;
    case doodle::KeyboardButtons::E:
        return CS230::Input::Keys::E;
    case doodle::KeyboardButtons::F:
        return CS230::Input::Keys::F;
    case doodle::KeyboardButtons::G:
        return CS230::Input::Keys::G;
    case doodle::KeyboardButtons::H:
        return CS230::Input::Keys::H;
    case doodle::KeyboardButtons::I:
        return CS230::Input::Keys::I;
    case doodle::KeyboardButtons::J:
        return CS230::Input::Keys::J;
    case doodle::KeyboardButtons::K:
        return CS230::Input::Keys::K;
    case doodle::KeyboardButtons::L:
        return CS230::Input::Keys::L;
    case doodle::KeyboardButtons::M:
        return CS230::Input::Keys::M;
    case doodle::KeyboardButtons::N:
        return CS230::Input::Keys::N;
    case doodle::KeyboardButtons::O:
        return CS230::Input::Keys::O;
    case doodle::KeyboardButtons::P:
        return CS230::Input::Keys::P;
    case doodle::KeyboardButtons::Q:
        return CS230::Input::Keys::Q;
    case doodle::KeyboardButtons::R:
        return CS230::Input::Keys::R;
    case doodle::KeyboardButtons::S:
        return CS230::Input::Keys::S;
    case doodle::KeyboardButtons::T:
        return CS230::Input::Keys::T;
    case doodle::KeyboardButtons::U:
        return CS230::Input::Keys::U;
    case doodle::KeyboardButtons::V:
        return CS230::Input::Keys::V;
    case doodle::KeyboardButtons::W:
        return CS230::Input::Keys::W;
    case doodle::KeyboardButtons::X:
        return CS230::Input::Keys::X;
    case doodle::KeyboardButtons::Y:
        return CS230::Input::Keys::Y;
    case doodle::KeyboardButtons::Z:
        return CS230::Input::Keys::Z;
    case doodle::KeyboardButtons::Space:
        return CS230::Input::Keys::Space;
    case doodle::KeyboardButtons::Enter:
        return CS230::Input::Keys::Enter;
    case doodle::KeyboardButtons::Left:
        return CS230::Input::Keys::Left;
    case doodle::KeyboardButtons::Up:
        return CS230::Input::Keys::Up;
    case doodle::KeyboardButtons::Right:
        return CS230::Input::Keys::Right;
    case doodle::KeyboardButtons::Down:
        return CS230::Input::Keys::Down;
    case doodle::KeyboardButtons::Tilde:
        return CS230::Input::Keys::Tilde;
    case doodle::KeyboardButtons::Tab:
        return CS230::Input::Keys::Tab;
    case doodle::KeyboardButtons::NumPad_1:
        return CS230::Input::Keys::NumPad_1;
    case doodle::KeyboardButtons::NumPad_2:
        return CS230::Input::Keys::NumPad_2;
    case doodle::KeyboardButtons::NumPad_3:
        return CS230::Input::Keys::NumPad_3;
    case doodle::KeyboardButtons::NumPad_4:
        return CS230::Input::Keys::NumPad_4;
    case doodle::KeyboardButtons::_0:
        return CS230::Input::Keys::_0;
    case doodle::KeyboardButtons::_1:
        return CS230::Input::Keys::_1;
    case doodle::KeyboardButtons::_2:
        return CS230::Input::Keys::_2;
    case doodle::KeyboardButtons::_3:
        return CS230::Input::Keys::_3;
    case doodle::KeyboardButtons::_4:
        return CS230::Input::Keys::_4;
    }

    return CS230::Input::Keys::Unknown;
}

void on_key_pressed(doodle::KeyboardButtons doodle_key) {
    CS230::Input::Keys key = convert_doodle_to_cs230(doodle_key);
    if (key != CS230::Input::Keys::Unknown) {
        Engine::GetLogger().LogDebug("Key Pressed");
        Engine::GetInput().SetKeyDown(key, true);
    }
}

void on_key_released(doodle::KeyboardButtons doodle_key) {
    CS230::Input::Keys key = convert_doodle_to_cs230(doodle_key);
    if (key != CS230::Input::Keys::Unknown) {
        Engine::GetLogger().LogDebug("Key Released");
        Engine::GetInput().SetKeyDown(key, false);
    }
}

bool CS230::Input::KeyDown(Keys key) {
    return keys_down[static_cast<int>(key)];
}

bool CS230::Input::KeyJustPressed(Keys key) {
    return keys_down[static_cast<int>(key)] == true && previous_keys_down[static_cast<int>(key)] == false;
}

bool CS230::Input::KeyJustReleased(Keys key) {
    return keys_down[static_cast<int>(key)] == false && previous_keys_down[static_cast<int>(key)] == true;
}