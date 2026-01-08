#pragma once
#include "Event.h"

class WindowCloseEvent : public Event
{

public:
    WindowCloseEvent() = default;

    static EventType GetStaticType()
    {
        return EventType::WindowClose;
    }

    EventType GetType() const override
    {
        return GetStaticType();
    }

    const char *GetName() const override
    {
        return "WindowCloseEvent";
    }
};
