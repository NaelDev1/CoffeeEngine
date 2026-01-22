#include "Renderer2D.h"
#include <SDL_image.h>
#include <iostream>
#include "core/Log.h"

Renderer2D::Renderer2D(SDL_Window *window)
{
    m_Renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!m_Renderer)
    {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << "\n";
    }
}

Renderer2D::~Renderer2D()
{
    if (m_DebugFont)
    {
        TTF_CloseFont(m_DebugFont);
        m_DebugFont = nullptr;
    }

    if (m_Renderer)
    {
        SDL_DestroyRenderer(m_Renderer);
    }
}

void Renderer2D::BeginFrame(const Camera *camera)
{
    m_CurrentCamera = camera;

    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 0);
    SDL_RenderClear(m_Renderer);
}

void Renderer2D::EndFrame()
{

    SDL_RenderPresent(m_Renderer);
}

void Renderer2D::DrawRect(int x, int y, int width, int height, int r, int g, int b, int a)
{

    if (!m_Renderer)
        return;

    SDL_Rect rect;

    if (m_CurrentCamera)
    {

        // Convert world -> screen
        float screenX, screenY;
        m_CurrentCamera->WorldToScreen((float)x, (float)y, screenX, screenY);

        // Appling the size of zoom
        int scaledW = (int)(width * m_CurrentCamera->GetZoom());
        int scaleH = (int)(height * m_CurrentCamera->GetZoom());

        rect = {(int)screenX, (int)screenY, scaledW, scaleH};
    }
    else
    {
        // widthout camera = cordenates
        rect = {x, y, width, height};
    }

    SDL_SetRenderDrawColor(m_Renderer, r, g, b, a);
    SDL_RenderFillRect(m_Renderer, &rect);
}

void Renderer2D::DrawIsoRect(int worldX, int worldY, int tileWidth, int tileHeight, int r, int g, int b, int a)
{
    if (!m_Renderer)
        return;

    if (m_CurrentCamera)
    {
        float screenX, screenY;
        m_CurrentCamera->WorldToScreen((float)worldX, (float)worldY, screenX, screenY);
        worldX = (int)screenX;
        worldY = (int)screenY;

        tileWidth = (int)(tileWidth * m_CurrentCamera->GetZoom());
        tileHeight = (int)(tileHeight * m_CurrentCamera->GetZoom());
    }

    SDL_Point points[5];
    points[0] = {worldX, worldY + tileHeight / 2};
    points[1] = {worldX + tileWidth / 2, worldY};
    points[2] = {worldX + tileWidth, worldY + tileHeight / 2};
    points[3] = {worldX + tileWidth / 2, worldY + tileHeight};
    points[4] = points[0];

    SDL_SetRenderDrawColor(m_Renderer, r, g, b, a);
    SDL_RenderDrawLines(m_Renderer, points, 5);
}

void Renderer2D::DrawIsometricSprite(SDL_Texture *spriteSheet, int worldX, int worldY, int tileWidth, int tileHeight, int spriteX, int spriteY, int spriteSize)
{
    if (!m_Renderer || !spriteSheet)
        return;

    if (m_CurrentCamera)
    {
        float screenX, screenY;
        m_CurrentCamera->WorldToScreen((float)worldX, (float)worldY, screenX, screenY);
        worldX = (int)screenX;
        worldY = (int)screenY;

        tileWidth = (int)(tileWidth * m_CurrentCamera->GetZoom());
        tileHeight = (int)(tileHeight * m_CurrentCamera->GetZoom());
    }

    SDL_Rect srcRect = {
        spriteX * spriteSize,
        spriteY * spriteSize,
        spriteSize,
        spriteSize};

    SDL_Rect dstRect = {
        worldX,
        worldY - tileHeight,
        tileWidth,
        tileHeight * 2};

    SDL_RenderCopy(m_Renderer, spriteSheet, &srcRect, &dstRect);
}

SDL_Texture *Renderer2D::LoadTexture(const char *path)
{
    SDL_Texture *texture = IMG_LoadTexture(m_Renderer, path);
    if (!texture)
    {
        std::cerr << "Failed to load: " << path << ": " << IMG_GetError() << "\n";
    }

    return texture;
}

TTF_Font *Renderer2D::LoadFont(const std::string &path, int fontSize)
{
    // try to load the font file
    TTF_Font *font = TTF_OpenFont(path.c_str(), fontSize);
    if (!font)
    {
        LOG_ERROR("Failed to load font", path, "Error:", TTF_GetError());
        return nullptr;
    }

    LOG_INFO("Font loaded successfully: ", path, "Size: ", fontSize);
    return font;
}

void Renderer2D::DrawText(TTF_Font *font, const std::string &text, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool refWorld)
{
    if (!m_Renderer || !font || text.empty())
        return;

    // create surface with text
    SDL_Color color = {r, g, b, a};
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);

    if (!surface)
    {
        LOG_ERROR("Failed to create text surface: ", TTF_GetError());
        return;
    }

    // convert surfece to texture
    SDL_Texture *texture = SDL_CreateTextureFromSurface(m_Renderer, surface);

    if (!texture)
    {
        LOG_ERROR("Failed to create a texture", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    // Get texture dimensions
    int textWidth = surface->w;
    int textHeight = surface->h;

    // apply camera tranformation if available
    if (m_CurrentCamera && refWorld)
    {
        float screenX, screenY;
        m_CurrentCamera->WorldToScreen((float)x, (float)y, screenX, screenY);
        x = (int)screenX;
        y = (int)screenY;

        // textWidth = (int)(textWidth * m_CurrentCamera->GetZoom());
        // textHeight = (int)(textWidth)*m_CurrentCamera->GetZoom();
    }

    // Set up destination rectangle
    SDL_Rect destRect = {x,
                         y,
                         textWidth,
                         textHeight};
    // render the texture
    SDL_RenderCopy(m_Renderer, texture, nullptr, &destRect);

    // clean up
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}
