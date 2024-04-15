#ifndef COLLIDER_HPP
#define COLLIDER_HPP
#include <SDL2/SDL.h>

class Collider
{
public:
    Collider()
    {
        m_rect.x = 0;
        m_rect.y = 0;
        m_rect.w = 0;
        m_rect.h = 0;
    }

    SDL_bool isCollide(Collider &obj1)
    {
        const SDL_Rect temp = obj1.m_rect;
        return SDL_HasIntersection(&m_rect, &temp);
    }

    ~Collider()
    {
    }

    void SetPosition(int x, int y)
    {
        m_rect.x = x;
        m_rect.y = y;
    }

    SDL_Rect& GetRectangle() {
        return m_rect;
    }

    void SetDimension(int w, int h)
    {
        m_rect.w = w;
        m_rect.h = h;
    }

    // void Render(SDL_Renderer* rend){

    // }

private:
    SDL_Rect m_rect;
    // SDL_Renderer* renderer;
};

#endif