#pragma once
#include "Event.h"
#include "EventType.h"
#include "input/InputTypes.h"

class KeyPressedEvent : public Event
{
public:
    explicit KeyPressedEvent(Key key)
        : m_Key(key) {}

    static EventType GetStaticType()
    {
        return EventType::KeyPressed;
    }

    EventType GetType() const override
    {
        return GetStaticType();
    }
    const char *GetName() const override
    {
        return "KeyPressedEvent";
    }

    Key GetKey() const
    {
        return m_Key;
    }

private:
    Key m_Key;
};
