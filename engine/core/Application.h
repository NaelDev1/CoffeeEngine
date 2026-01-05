#pragma once
#include <SDL2/SDL.h>
#include "render/Renderer2D.h"

class Application
{

public:
    Application();
    ~Application();

    void Run();

private:
    bool m_Running;
    SDL_Window *m_Window;
    Renderer2D *m_Renderer;
    void ShowSplashScreen();
};