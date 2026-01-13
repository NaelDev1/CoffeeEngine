#pragma once
#include "Component.h"
#include <string>

struct SDL_Texture;
struct SDL_Rect;
struct SpriteComponent : public Component
{
    std::string texturePath;
    int width = 0, height = 0;
    SDL_Texture *texture = nullptr;
    SDL_Rect srcRect = {0, 0, 0, 0};

    SpriteComponent(const std::string &path) : texturePath(path) {}
};