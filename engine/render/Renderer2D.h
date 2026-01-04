#pragma once
#include <SDL.h>

class Renderer2D
{

public:
    Renderer2D(SDL_Window *window);
    ~Renderer2D();

    void BeginFrame();
    void EndFrame();

    // new funcion
    void DrawRect(int x, int y, int width, int height, int r, int g, int b, int a);

private:
    SDL_Renderer *m_Renderer;
};