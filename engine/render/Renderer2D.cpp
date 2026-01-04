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
