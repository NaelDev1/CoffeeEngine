#pragma once
#include "core/Camera.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Renderer2D
{

public:
    Renderer2D(SDL_Window *window);
    ~Renderer2D();

    void BeginFrame(const Camera *camera = nullptr);
    void EndFrame();

    void DrawRect(int x, int y, int width, int height, int r, int g, int b, int a);

    void DrawIsoRect(int mapX, int mapY, int tileWidth, int tileHeight, int r, int g, int b, int a);

    void DrawIsometricSprite(SDL_Texture *spriteSheet, int mapX, int mapY, int tileWidth, int tileHeight, int spriteX, int spriteY, int spriteSize);

    SDL_Renderer *GetSDLRenderer() const { return m_Renderer; }
    SDL_Texture *LoadTexture(const char *path);

    TTF_Font *LoadFont(const std::string &path, int fontSize);

    void DrawText(TTF_Font *font, const std::string &text, int x, int y, Uint8 r = 255, Uint8 g = 255, Uint8 b = 255, Uint8 a = 255, bool refWorld = false);

    void DrawDebugText(const std::string &text, int x = 10, int y = 10);

private:
    SDL_Renderer *m_Renderer;
    const Camera *m_CurrentCamera = nullptr;

    TTF_Font *m_DebugFont = nullptr;
    bool m_FontLoaded = false;
};