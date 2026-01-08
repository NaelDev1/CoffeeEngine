#pragma once
#include <unordered_map>
#include "input/InputTypes.h"
#include <SDL.h>
#include <functional>
#include "events/Event.h"

class InputSystem
{

public:
    using EventCallbackFn = std::function<void(Event &)>;
    static void Init();
    static void Update();
    static void Shutdown();

    static void ProcessSDLEvent(const SDL_Event &event);

    static bool IsPressed(Key key);
    static bool IsHeld(Key key);
    static bool IsReleased(Key key);

    static void SetEventCallback(const EventCallbackFn &callback);

private:
    static void OnKeyDown(Key key);
    static void OnKeyUp(Key key);

    static Key SDLKeyToKey(SDL_Keycode key);

private:
    static std::unordered_map<Key, KeyState> keys;
    static EventCallbackFn s_EventCallback;
};