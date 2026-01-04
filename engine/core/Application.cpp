#include "Application.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

Application::Application()
    : m_Running(true), m_Window(nullptr), m_Renderer(nullptr), m_HouseTexture(nullptr)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL init failed\n";
        m_Running = false;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        std::cerr << "SDL_image init failed: " << IMG_GetError() << "\n";
        m_Running = false;
        return;
    }

    m_Window = SDL_CreateWindow(
        "CoffeeEngine ☕",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        SDL_WINDOW_SHOWN);

    if (!m_Window)
    {
        std::cerr << "Window creation failed: " << SDL_GetError() << "\n";
        m_Running = false;
    }
    if (m_Window)
    {

        m_Renderer = new Renderer2D(m_Window);

        // loading the house sprite
        SDL_Surface *surface = IMG_Load("assets/sprites/houses.png");

        if (!surface)
        {
            std::cerr << "Failed to load house.png: " << IMG_GetError() << "\n";
            m_Running = false;
            return;
        }

        m_HouseTexture = SDL_CreateTextureFromSurface(m_Renderer->GetSDLRenderer(), surface);
        SDL_FreeSurface(surface);
        if (!m_HouseTexture)
        {
            std::cerr << "Failed to create texture: " << SDL_GetError() << "\n";
            m_Running = false;
            return;
        }
    }
}

Application::~Application()
{
    if (m_HouseTexture)
        SDL_DestroyTexture(m_HouseTexture);
    delete m_Renderer;
    if (m_Window)
    {
        SDL_DestroyWindow(m_Window);
    }
    IMG_Quit();
    SDL_Quit();
}

void Application::Run()
{

    int tileW = 512;
    int tileH = 256;

    while (m_Running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                m_Running = false;
        }

        if (m_Renderer)
        {

            m_Renderer->BeginFrame();

            // drawing a rectangle
            // m_Renderer->DrawRect(100, 100, 200, 150, 0, 255, 0, 255); // a green rect

            // drawing a isometric map tiles
            // int tileW = 64;
            // int tileH = 32;
            // for (int y = 0; y < 4; ++y)
            // {
            //     for (int x = 0; x < 4; ++x)
            //     {
            //         m_Renderer->DrawIsoRect(x, y, tileW, tileH, 0, 255, 0, 255);
            //     }
            // }

            // drawining 4x4 houses;
            for (int y = 0; y < 4; ++y)
            {
                for (int x = 0; x < 4; ++x)
                {
                    m_Renderer->DrawIsometricSprite(m_HouseTexture, x, y, tileW, tileH);
                }
            }

            m_Renderer->EndFrame();
        }
    }
}
