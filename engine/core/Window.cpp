#include "Window.h"
#include "input/InputSystem.h"
#include <iostream>
#include "input/InputSystem.h"

Window::Window(const std::string &title, int width, int height)
    : m_Title(title), m_Width(width), m_Height(height)
{
    m_Window = SDL_CreateWindow(title.c_str(),
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                width,
                                height,
                                SDL_WINDOW_SHOWN);

    if (!m_Window)
    {
        std::cerr << "Window creation failed: " << SDL_GetError() << "\n";
    }
};

Window::~Window()
{
    if (m_Window)
    {
        SDL_DestroyWindow(m_Window);
    }
}

void Window::PollEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            if (m_CloseCallback)
            {
                // notify the application
                m_CloseCallback();
            }
        }

        InputSystem::ProcessSDLEvent(event);
    }
}

void Window::SwapBuffers()
{
}
