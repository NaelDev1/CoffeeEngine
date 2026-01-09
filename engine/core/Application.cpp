#include "Application.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "input/InputSystem.h"
#include "Log.h"
#include "events/EventDispatcher.h"
#include "events/WindowCloseEvent.h"
#include "TestLayer.h"

Application::Application()
    : m_Running(true), m_Window(nullptr), m_Renderer(nullptr)
{

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL init failed\n";
        m_Running = false;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        std::cerr << "IMG_Init failed: " << IMG_GetError() << std::endl;
        m_Running = false;
        return;
    }
    m_Window = std::make_unique<Window>("CoffeeEngine ☕", 1280, 720);

    if (!m_Window->GetSDLWindow())
    {
        std::cerr << "Window creation failed: " << SDL_GetError() << "\n";
        m_Running = false;
    }
    if (m_Window->GetSDLWindow())
    {
        InputSystem::Init();

        InputSystem::SetEventCallback([this](Event &e)
                                      { OnEvent(e); });

        m_Window->SetCloseCallback([this]()
                                   {
            WindowCloseEvent e;
            OnEvent(e); });
        m_Renderer = new Renderer2D(m_Window->GetSDLWindow());
        ShowSplashScreen();
    }
}

Application::~Application()
{

    delete m_Renderer;
    InputSystem::Shutdown();
    IMG_Quit();
    SDL_Quit();
}

void Application::PushLayer(Layer *layer)
{
    m_LayerStack.PushLayer(layer);
}

void Application::PushOverlay(Layer *overlay)
{
    m_LayerStack.PushOverlay(overlay);
}

void Application::Run()
{

    LOG_INFO("Wellcome into CoffeeEngine!");

    PushLayer(new TestLayer());

    while (m_Running)
    {
        m_Timer.Tick();
        float deltaTime = m_Timer.GetDeltaTime();
        m_Window->PollEvents();
        InputSystem::Update();

        for (Layer *layer : m_LayerStack)
        {
            layer->OnUpdate(deltaTime);
        }

        if (m_Renderer)
        {
            m_Renderer->BeginFrame();

            // drawing a rectangle
            // m_Renderer->DrawRect(100, 100, 200, 150, 0, 255, 0, 255); // a green rect

            // drawing a isometric map tiles
            int tileW = 64;
            int tileH = 32;
            int mapSize = 15;
            for (int y = 0; y < mapSize; ++y)
            {
                for (int x = 0; x < mapSize; ++x)
                {
                    m_Renderer->DrawIsoRect(x, y, tileW, tileH, 53, 117, 143, 100);
                }
            }

            static SDL_Texture *tileSet = m_Renderer->LoadTexture("assets/sprites/houses.png");

            for (int y = 0; y < mapSize; ++y)
            {
                for (int x = 0; x < mapSize; ++x)
                {
                    int tileIndexX = x % 4;
                    int tileIndexY = y % 4;

                    m_Renderer->DrawIsometricSprite(tileSet, x, y, 64, 32, tileIndexX, tileIndexY, 512);
                }
            }

            m_Renderer->EndFrame();
        }
    }
}

void Application::OnEvent(Event &event)
{
    EventDispatcher dispatcher(event);

    dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent &)
                                          {
        m_Running = false;
        return true; });

    for (auto it = m_LayerStack.begin(); it != m_LayerStack.end(); ++it)
    {
        if (event.Handled)
            break;
        (*it)->OnEvent(event);
    }
}

void Application::ShowSplashScreen()
{
    SDL_Texture *logo = m_Renderer->LoadTexture("engine/util/logo.png");
    if (!logo)
        return;

    Uint32 startTime = SDL_GetTicks();
    float alpha = 0;
    bool fadingIn = true;

    while (m_Running && fadingIn)
    {
        m_Window->PollEvents();
        // Calcula fade
        Uint32 currentTime = SDL_GetTicks();
        float elapsed = (currentTime - startTime) / 1000.0f;

        if (elapsed < 2.0f)
        {
            alpha = (elapsed / 2.0f) * 255; // Fade in 2 segundos
        }
        else
        {
            alpha = 255;
            if (elapsed > 4.0f)
                fadingIn = false; // Mostra por 2 segundos
        }

        // Renderiza logo
        m_Renderer->BeginFrame();
        SDL_SetTextureAlphaMod(logo, (Uint8)alpha);

        int winW, winH;
        SDL_GetWindowSize(m_Window->GetSDLWindow(), &winW, &winH);
        SDL_Rect dst = {winW / 2 - 256, winH / 2 - 256, 512, 512};
        SDL_RenderCopy(m_Renderer->GetSDLRenderer(), logo, nullptr, &dst);

        m_Renderer->EndFrame();
    }

    SDL_DestroyTexture(logo);
}
