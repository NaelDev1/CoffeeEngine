#pragma once
#include "Layer.h"
#include <iostream>
#include "events/KeyPressedEvent.h"

class TestLayer : public Layer
{

public:
    void OnUpdate(float dt) override
    {
        // std::cout << "Upadate: " << dt << "| FPS: " << (1.0f / dt) << std::endl;
    }

    void OnEvent(Event &e) override
    {
        if (e.GetType() == KeyPressedEvent::GetStaticType())
            std::cout << "Tecla!" << std::endl;
    }
};
