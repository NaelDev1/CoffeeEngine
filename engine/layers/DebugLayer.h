#pragma once
#include "../render/Renderer2D.h"
#include "core/Layer.h"
#include "core/Timer.h"
#include <string>
#include <format>

class DebugLayer : public Layer
{
public:
    DebugLayer(Renderer2D *renderer, Timer *timer)
        : m_Renderer(renderer), m_Timer(timer) {}

    virtual void OnUpdate(float deltaTime) override {}

    void virtual OnRender() override
    {
        // Draw UI elements in screen space
        std::string fpsText = std::format("FPS {:.0f}", m_Timer->GetFps());
        auto font = m_Renderer->LoadFont("assets/fonts/toxigenesis.otf", 18);

        m_Renderer->DrawText(font, fpsText, 0, 0, 255, 255, 255, 255, false);
    }

private:
    Renderer2D *m_Renderer;
    Timer *m_Timer;
};