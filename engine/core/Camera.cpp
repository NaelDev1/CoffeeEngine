#include "Camera.h"

Camera::Camera() = default;

void Camera::SetPosition(float x, float y)
{
    m_X = x;
    m_Y = y;
}

void Camera::Move(float dx, float dy)
{
    m_X += dx;
    m_Y += dy;
}

void Camera::Zoom(float factor)
{
    SetZoom(m_Zoom * factor);
}

void Camera::WorldToScreen(float worldX, float worldY, float &screenX, float &screenY) const
{
    screenX = (worldX - m_X) * m_Zoom;
    screenY = (worldY - m_Y) * m_Zoom;
}

void Camera::ScreenToWorld(float screenX, float screenY, float &worldX, float &worldY) const
{
    worldX = (screenX / m_Zoom) + m_X;
    worldY = (screenY / m_Zoom) + m_Y;
}
void Camera::SetZoom(float zoom)
{
    if (zoom < 0.1f)
        zoom = 0.1f;
    if (zoom > 10.0f)
        zoom = 10.0f;
    m_Zoom = zoom;
}