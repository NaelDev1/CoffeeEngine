#pragma once
#include "input/InputTypes.h"
#include "Event.h"

class KeyReleasedEvent : public Event
{

public:
    explicit KeyReleasedEvent(Key key)
        : m_Key(key) {}

    static EventType GetStaticType()
    {
        return EventType::KeyReleased;
    }

    EventType GetType() const override
    {
        return GetStaticType();
    }

    const char *GetName() const override
    {
        return "KeyReleasedEvet";
    }
    Key GetKey() const
    {
        return m_Key;
    }

private:
    Key m_Key;
};