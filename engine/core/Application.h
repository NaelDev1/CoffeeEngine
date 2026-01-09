#pragma once
#include <SDL2/SDL.h>
#include "render/Renderer2D.h"
#include "events/Event.h"
#include "Layer.h"
#include "LayerStack.h"
#include "Timer.h"
#include "Window.h"

class Application
{

public:
    Application();
    ~Application();

    void Run();
    void OnEvent(Event &event);

    void PushLayer(Layer *layer);
    void PushOverlay(Layer *overlay);

private:
    Timer m_Timer;
    bool m_Running;
    std::unique_ptr<Window> m_Window;
    Renderer2D *m_Renderer;
    void ShowSplashScreen();
    LayerStack m_LayerStack;
};