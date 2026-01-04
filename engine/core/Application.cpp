#include "Application.h"
#include <SDL.h>
#include <iostream>

Application::Application()
    : m_Running(true), m_Window(nullptr), m_Renderer(nullptr)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL init failed\n";
        m_Running = false;
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
    }
}

Application::~Application()
{
    delete m_Renderer;
    if (m_Window)
    {
        SDL_DestroyWindow(m_Window);
    }
    SDL_Quit();
}

void Application::Run()
{

    while (m_Running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                m_Running = false;
            }
        }

        if (m_Renderer)
        {

            m_Renderer->BeginFrame();
            m_Renderer->EndFrame();
        }
    }
}
