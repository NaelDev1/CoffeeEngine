#pragma once
#include <string>
#include "events/Event.h"

class Layer
{

public:
    explicit Layer(const char *name = "Layer")
        : m_Name(name) {}

    virtual ~Layer() = default;

    virtual void OnAttach() {}
    virtual void OnDetach() {}

    virtual void OnUpdate(float deltaTime) {}
    virtual void OnEvent(Event &event) {}

    virtual void OnRender() {}

    const std::string &GetName() const { return m_Name; }

protected:
    std::string m_Name;
};
