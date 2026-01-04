#pragma once
#include <SDL.h>

class Renderer2D
{

public:
    Renderer2D(SDL_Window *window);
    ~Renderer2D();

    void BeginFrame();
    void EndFrame();

private:
    SDL_Renderer *m_Renderer;
};