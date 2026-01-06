#pragma once
#include <unordered_map>
#include "input/InputTypes.h"

class InputSystem
{

public:
    static void Init();
    static void Update();
    static void Shutdown();

    static bool IsPressed(Key key);
    static bool IsHeld(Key key);
    static bool IsReleased(Key key);

private:
    static std::unordered_map<Key, KeyState> keys;
};