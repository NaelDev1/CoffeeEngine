#pragma once
#include <SDL2/SDL.h>
#include "render/Renderer2D.h"
#include "events/Event.h"

class Application
{

public:
    Application();
    ~Application();

    void Run();
    void OnEvent(Event &event);

private:
    bool m_Running;
    SDL_Window *m_Window;
    Renderer2D *m_Renderer;
    void ShowSplashScreen();
};