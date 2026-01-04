#include "Renderer2D.h"
#include <iostream>

Renderer2D::Renderer2D(SDL_Window *window)
{
    m_Renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!m_Renderer)
    {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << "\n";
    }
}

Renderer2D::~Renderer2D()
{

    if (m_Renderer)
    {
        SDL_DestroyRenderer(m_Renderer);
    }
}

void Renderer2D::BeginFrame()
{
    // Cor de fundo (cinza escuro)
    SDL_SetRenderDrawColor(m_Renderer, 80, 80, 80, 255);
    SDL_RenderClear(m_Renderer);
}

void Renderer2D::EndFrame()
{

    SDL_RenderPresent(m_Renderer);
}

void Renderer2D::DrawRect(int x, int y, int width, int height, int r, int g, int b, int a)
{

    if (!m_Renderer)
        return;

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;

    SDL_SetRenderDrawColor(m_Renderer, r, g, b, a);
    SDL_RenderFillRect(m_Renderer, &rect);
}

void Renderer2D::DrawIsoRect(int mapX, int mapY, int tileWidth, int tileHeight, int r, int g, int b, int a)
{
    if (!m_Renderer)
        return;

    // isometric conversor
    int isoX = (mapX - mapY) * tileWidth / 2;
    int isoY = (mapX + mapY) * tileHeight / 2;

    SDL_Rect rect;
    rect.x = isoX;
    rect.y = isoY;
    rect.w = tileWidth;
    rect.h = tileHeight;

    SDL_SetRenderDrawColor(m_Renderer, r, g, b, a);
    SDL_RenderFillRect(m_Renderer, &rect);
}

void Renderer2D::DrawIsometricSprite(SDL_Texture *sprite, int mapX, int mapY, int tileWidth, int tileHeight)
{

    if (!m_Renderer || !sprite)
        return;

    // converting the conrdenated to a isometric map
    int isoX = (mapX - mapY) * (tileWidth / 2);
    int isoY = (mapX + mapY) * (tileHeight / 2);

    // query sprite to cat the real size
    int w, h;
    SDL_QueryTexture(sprite, nullptr, nullptr, &w, &h);

    SDL_Rect dstRect;
    dstRect.x = isoX;
    dstRect.y = isoY - h + tileHeight;
    dstRect.w = w;
    dstRect.h = h;

    SDL_RenderCopy(m_Renderer, sprite, nullptr, &dstRect);
}
