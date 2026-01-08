#pragma once
#include "EventType.h"

class Event
{

public:
    bool Handled = false;

    virtual ~Event() = default;
    virtual EventType GetType() const = 0;
    virtual const char *GetName() const = 0;
};