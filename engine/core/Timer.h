#pragma once
#include <chrono>

class Timer
{
public:
    Timer();

    void Tick();

    float GetDeltaTime() const { return m_DeltaTime; }

    float GetFps() const { return m_FPS; }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_LastTime;

    float m_DeltaTime = 0.0f;
    float m_FPS = 0.0f;

    float m_FPSTimer = 0.0f;
    int m_FPSCount = 0;
};