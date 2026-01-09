#include "Timer.h"

Timer::Timer()
{
    m_StartTime = m_LastTime = std::chrono::high_resolution_clock::now();
}

void Timer::Tick()
{
    auto now = std::chrono::high_resolution_clock::now();

    // DeltaTime in seconds
    m_DeltaTime = std::chrono::duration<float>(now - m_LastTime).count();
    m_LastTime = now;

    // Calculate FPS (Update each second)
    m_FPSTimer += m_DeltaTime;
    m_FPSCount++;

    if (m_FPSTimer >= 1.0f)
    {
        m_FPS = m_FPSCount / m_FPSTimer; // frame per seconds
        m_FPSTimer = 0.0f;
        m_FPSCount = 0;
    }
}