#pragma once
#include <SDL2/SDL.h>

class Application
{

public:
    Application();
    ~Application();

    void Run();

private:
    bool m_Running;
    SDL_Window *m_Window;
};