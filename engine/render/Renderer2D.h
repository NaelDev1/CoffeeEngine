#pragma once
#include <SDL.h>

class Renderer2D
{

public:
    Renderer2D(SDL_Window *window);
    ~Renderer2D();

    void BeginFrame();
    void EndFrame();

    // new method
    void DrawRect(int x, int y, int width, int height, int r, int g, int b, int a);
    // new method to draw a isometric rec
    void DrawIsoRect(int mapX, int mapY, int tileWidth, int tileHeight, int r, int g, int b, int a);
    // new method to draw a isometric prite
    void DrawIsometricSprite(SDL_Texture *sprite, int mapX, int mapY, int tileWidth, int tileHeight);

    SDL_Renderer *GetSDLRenderer() const { return m_Renderer; }

private:
    SDL_Renderer *m_Renderer;
};