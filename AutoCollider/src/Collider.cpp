#include "../include/Collider.hpp" 

Collider::Collider()
{
    m_rect = new SDL_Rect;
    m_rect->x = 0;
    m_rect->y = 0;
    m_rect->w = 0;
    m_rect->h = 0;
}

SDL_bool Collider::isCollide(Collider &obj1)
{
    if (m_rect == nullptr)
    {
        return SDL_FALSE;
    }
    const SDL_Rect *temp = obj1.m_rect;
    if (temp == nullptr)
    {
        return SDL_FALSE;
    }
    return SDL_HasIntersection(m_rect, temp);
}

Collider::~Collider()
{
    delete m_rect;
}

void Collider::SetPosition(int x, int y)
{
    m_rect->x = x;
    m_rect->y = y;
}

SDL_Rect &Collider::GetRectangle()
{
    return *m_rect;
}

void Collider::SetDimension(int w, int h)
{
    m_rect->w = w;
    m_rect->h = h;
}