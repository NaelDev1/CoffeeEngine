#include "InputSystem.h"
#include "events/KeyPressedEvent.h"
#include "events/KeyReleasedEvent.h"
#include <iostream>

std::unordered_map<Key, KeyState> InputSystem::keys;
InputSystem::EventCallbackFn InputSystem::s_EventCallback;

void InputSystem::SetEventCallback(const EventCallbackFn &callback)
{
    s_EventCallback = callback;
}

void InputSystem::Init()
{
    keys.clear();
}

void InputSystem::Shutdown()
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

void InputSystem::ProcessSDLEvent(const SDL_Event &event)
{

    switch (event.type)
    {
    case SDL_KEYDOWN:
    {
        if (event.key.repeat == 0)
        {
            Key key = SDLKeyToKey(event.key.keysym.sym);

            std::cout << "[InputSystem] Tecla pressionada: SDL=" << event.key.keysym.sym
                      << " (" << SDL_GetKeyName(event.key.keysym.sym) << ")"
                      << " -> Key=" << (int)key << std::endl;

            OnKeyDown(key);
        }
        break;
    }
    case SDL_KEYUP:
    {
        Key key = SDLKeyToKey(event.key.keysym.sym);
        OnKeyUp(key);

        if (s_EventCallback)
        {
            KeyReleasedEvent e(key);
            s_EventCallback(e);
        }
        break;
    }
    }
}

bool InputSystem::IsPressed(Key key)
{
    auto it = keys.find(key);

    return it != keys.end() && it->second == KeyState::Pressed;
}

bool InputSystem::IsHeld(Key key)
{
    auto it = keys.find(key);

    return it != keys.end() && it->second == KeyState::Held;
}

bool InputSystem::IsReleased(Key key)
{
    auto it = keys.find(key);
    return it != keys.end() && it->second == KeyState::Released;
}

void InputSystem::OnKeyDown(Key key)
{

    auto &state = keys[key];
    if (state == KeyState::Up || state == KeyState::Released)
        state = KeyState::Pressed;
}

void InputSystem::OnKeyUp(Key key)
{
    auto &state = keys[key];
    if (state == KeyState::Held || state == KeyState::Pressed)
        keys[key] = KeyState::Released;
}

Key InputSystem::SDLKeyToKey(SDL_Keycode key)
{

    switch (key)
    {
    case SDLK_a:
        return Key::A;
    case SDLK_b:
        return Key::B;
    case SDLK_c:
        return Key::C;
    case SDLK_d:
        return Key::D;
    case SDLK_e:
        return Key::E;
    case SDLK_f:
        return Key::F;
    case SDLK_g:
        return Key::G;
    case SDLK_h:
        return Key::H;
    case SDLK_i:
        return Key::I;
    case SDLK_j:
        return Key::J;
    case SDLK_k:
        return Key::K;
    case SDLK_l:
        return Key::L;
    case SDLK_m:
        return Key::M;
    case SDLK_n:
        return Key::N;
    case SDLK_o:
        return Key::O;
    case SDLK_p:
        return Key::P;
    case SDLK_q:
        return Key::Q;
    case SDLK_r:
        return Key::R;
    case SDLK_s:
        return Key::S;
    case SDLK_t:
        return Key::T;
    case SDLK_u:
        return Key::U;
    case SDLK_v:
        return Key::V;
    case SDLK_w:
        return Key::W;
    case SDLK_x:
        return Key::X;
    case SDLK_y:
        return Key::Y;
    case SDLK_z:
        return Key::Z;
    case SDLK_0:
        return Key::Num0;
    case SDLK_1:
        return Key::Num1;
    case SDLK_2:
        return Key::Num2;
    case SDLK_3:
        return Key::Num3;
    case SDLK_4:
        return Key::Num4;
    case SDLK_5:
        return Key::Num5;
    case SDLK_6:
        return Key::Num6;
    case SDLK_7:
        return Key::Num7;
    case SDLK_8:
        return Key::Num8;
    case SDLK_9:
        return Key::Num9;
    case SDLK_KP_1:
        return Key::Num1;
    case SDLK_KP_2:
        return Key::Num2;
    case SDLK_KP_3:
        return Key::Num3;
    case SDLK_KP_4:
        return Key::Num4;
    case SDLK_KP_5:
        return Key::Num5;
    case SDLK_KP_6:
        return Key::Num6;
    case SDLK_KP_7:
        return Key::Num7;
    case SDLK_KP_8:
        return Key::Num8;
    case SDLK_KP_9:
        return Key::Num9;
    case SDLK_KP_0:
        return Key::Num0;

    case SDLK_SPACE:
        return Key::Space;
    case SDLK_KP_ENTER:
        return Key::Enter;
    case SDLK_ESCAPE:
        return Key::Escape;
    case SDLK_TAB:
        return Key::Tab;
    case SDLK_BACKSPACE:
        return Key::Backscape;
    case SDLK_LEFT:
        return Key::Left;
    case SDLK_RIGHT:
        return Key::Right;
    case SDLK_UP:
        return Key::Up;
    case SDLK_DOWN:
        return Key::Down;

    default:
        return Key::Unknown;
    }
}