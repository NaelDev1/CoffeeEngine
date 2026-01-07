#include "InputSystem.h"

std::unordered_map<Key, KeyState> InputSystem::keys;

void InputSystem::Init()
{
    keys.clear();
}

void InputSystem::Update()
{
    for (auto &[key, state] : keys)
    {
        if (state == KeyState::Pressed)
            state = KeyState::Held;
        else if (state == KeyState::Released)
        {
            state = KeyState::Up;
        }
    }
}

void InputSystem::Shutdown()
{
    keys.clear();
}

bool InputSystem::IsPressed(Key key)
{
    return keys[key] == KeyState::Pressed;
}

bool InputSystem::IsHeld(Key key)
{
    return keys[key] == KeyState::Held;
}

bool InputSystem::IsReleased(Key key)
{
    return false;
}