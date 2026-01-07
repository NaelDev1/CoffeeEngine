#pragma once
#include "Event.h"
#include "EventType.h"
#include "InputTypes.h"

class KeyPressEvent : public Event
{

public:
    explicit KeyPressEvent(Key key)
        : m_Key(key) {}

    static EventType GetStaticType()
    {
        return EventType::KeyPressed;
    }

    EventType GetType() const override
    {
        return GetStaticType();
    }

    Key GetKey() const
    {
        return m_Key;
    }

private:
    Key m_Key;
};
