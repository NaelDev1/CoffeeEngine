#pragma once

enum class EventType
{
    None = 0,

    // Input
    KeyPressed,
    KeyReleased,

    // Window
    WindowClose,
    WindowResize
};