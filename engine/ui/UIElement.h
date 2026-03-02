#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <functional>
#include "../render/Renderer2D.h"
#include "../events/Event.h"



enum class UIState {
    Normal,
    Hovered,
    Pressed,
    Disabled
};

class UIElement {
    public: 
        UIElement(int x, int y, int width, int height) 
        : m_X(x), m_Y(y), m_Width(width), m_Height(height) {}

    virtual ~UIElement() = default;

    virtual void OnUpdate(float dt){}
    virtual void OnRender(Renderer2D* renderer) = 0;
    virtual void OnEvent(SDL_Event& event) {}

    virtual void SetPosition(int x , int y) {m_X = x; m_Y = y;}
    virtual void SetSize(int width, int height) {m_Width = width; m_Height = height;}




    protected:
        int m_X, m_Y, m_Width, m_Height;
        bool m_Visible = true;
        bool m_Enabled = true;
        UIState m_State = UIState::Normal;
        std::string m_ID;
};

