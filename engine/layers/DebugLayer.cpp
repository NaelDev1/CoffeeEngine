#include "core/Layer.h"
#include "render/Renderer2D.h"
#include "core/Timer.h"

class DebugLayer : public Layer
{
public:
    DebugLayer(Renderer2D *renderer, Timer *timer)
        : m_Renderer(renderer), m_Timer(timer) {}

    virtual void OnUpdate(float deltaTime) override {}

    void virtual OnRender() override
    {
    }

private:
    Renderer2D *m_Renderer;
    Timer *m_Timer;
};