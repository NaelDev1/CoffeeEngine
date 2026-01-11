#pragma once

class Camera
{
public:
    Camera();

    void SetPosition(float x, float y);
    void Move(float dx, float dy);

    void SetZoom(float zoom);
    void Zoom(float factor);

    float GetX() const { return m_X; }
    float GetY() const { return m_Y; }
    float GetZoom() const { return m_Zoom; }

    void WorldToScreen(float worldX, float WorldY, float &screenX, float &screenY) const;
    void ScreenToWorld(float screenX, float screenY, float &worldX, float &worldY) const;

private:
    float m_X = 0.0f;
    float m_Y = 0.0f;
    float m_Zoom = 1.0f;
};