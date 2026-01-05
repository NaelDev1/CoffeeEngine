#include "Renderer2D.h"
#include <SDL_image.h>
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
    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 0);
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

    int winW, winH;
    SDL_GetRendererOutputSize(m_Renderer, &winW, &winH);
    isoX += winW / 2;
    isoY += winH / 4;

    SDL_Point points[5];
    points[0] = {isoX, isoY + tileHeight / 2};             // topo
    points[1] = {isoX + tileWidth / 2, isoY};              // direita
    points[2] = {isoX + tileWidth, isoY + tileHeight / 2}; // base
    points[3] = {isoX + tileWidth / 2, isoY + tileHeight}; // esquerda
    points[4] = points[0];                                 // fecha polígono

    SDL_SetRenderDrawColor(m_Renderer, r, g, b, a);
    SDL_RenderDrawLines(m_Renderer, points, 5);
}

void Renderer2D::DrawIsometricSprite(SDL_Texture *spriteSheet, int mapX, int mapY, int tileWidth, int tileHeight, int spriteX, int spriteY, int spriteSize)
{

    if (!m_Renderer || !spriteSheet)
        return;

    int winW, winH;
    SDL_GetRendererOutputSize(m_Renderer, &winW, &winH);

    // converting the conrdenated to a isometric map
    int isoX = (mapX - mapY) * (tileWidth / 2) + winW / 2;
    int isoY = (mapX + mapY) * (tileHeight / 2) + winH / 4;

    SDL_Rect srcRect;
    srcRect.x = spriteX * spriteSize;
    srcRect.y = spriteY * spriteSize;
    srcRect.w = spriteSize;
    srcRect.h = spriteSize;

    SDL_Rect dstRect;
    dstRect.x = isoX;
    dstRect.y = isoY - tileHeight;
    dstRect.w = tileWidth;
    dstRect.h = tileHeight * 2;

    SDL_RenderCopy(m_Renderer, spriteSheet, &srcRect, &dstRect);
}

SDL_Texture *Renderer2D::LoadTexture(const char *path)
{
    SDL_Texture *texture = IMG_LoadTexture(m_Renderer, path);
    if (!texture)
    {
        std::cerr << "Failed to load: " << path << ": " << IMG_GetError() << "\n";
    }

    return texture;
}
