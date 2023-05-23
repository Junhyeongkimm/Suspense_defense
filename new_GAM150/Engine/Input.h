#pragma once
#include <vector>



namespace CS230 {
    class Input {
    public:
        std::vector<bool> keys_down;
        std::vector<bool> previous_keys_down;

        enum class Keys {
            A, B, C, D, E, F, G, H, I, J, K, L, M, N,
            O, P, Q, R, S, T, U, V, W, X, Y, Z,
            Space, Enter, Left, Up, Right, Down,
            Tilde, Tab, Unknown
        };

        Input();
        void Update();
        void SetKeyDown(Keys key, bool value);
        bool KeyDown(Keys key);
        bool KeyJustPressed(Keys key);
        bool KeyJustReleased(Keys key);
    };
}
