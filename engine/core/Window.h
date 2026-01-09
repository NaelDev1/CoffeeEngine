#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <functional>

class Window
{

public:
    using EventCallbackFn = std::function<void()>;

    Window(const std::string &title, int width, int height);
    ~Window();

    void PollEvents();
    void SwapBuffers();

    void SetCloseCallback(const EventCallbackFn &callback)
    {
        m_CloseCallback = callback;
    }

    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Height; }

    SDL_Window *GetSDLWindow() { return m_Window; }

private:
    SDL_Window *m_Window = nullptr;
    int m_Width = 0;
    int m_Height = 0;
    std::string m_Title;
    EventCallbackFn m_CloseCallback;
};
