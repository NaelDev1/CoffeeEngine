#include "InputSystem.h"

std::unordered_map<Key, KeyState> InputSystem::keys;

void InputSystem::Init()
{
    keys.clear();
}

void InputSystem::Update()
{
}

void InputSystem::Shutdown()
{
    keys.clear();
}

bool InputSystem::IsPressed(Key key)
{
    return false;
}

bool InputSystem::IsHeld(Key key)
{
    return false;
}

bool InputSystem::IsReleased(Key key)
{
    return false;
}