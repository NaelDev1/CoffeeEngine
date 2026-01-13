#pragma once
#include "Component.h"

struct TranformComponent : public Component
{
    float x = 0.0f, y = 0.0f;
    float rotation = 0.0f;
    float scaleX = 1.0f, scaleY = 1.0f;

    TranformComponent(float x = 0, float y = 0) : x(x), y(y) {}
};