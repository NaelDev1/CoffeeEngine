#pragma once
#include <string>
#include "events/Event.h"

class Layer
{

public:
    explicit Layer(const std::string &name = "Layer")
        : m_Name(name) {}

    virtual ~Layer() = default;

    virtual void OnAttach() {}
    virtual void OnDetach() {}

    virtual void OnUpdate(float deltaTime) {}
    virtual void OnEvent(Event &event) {}

    const std::string &GetName() const { return m_Name; }

protected:
    std::string m_Name;
};
