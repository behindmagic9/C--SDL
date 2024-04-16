#ifndef COLLIDER_HPP
#define COLLIDER_HPP
#include <SDL2/SDL.h>
#include "Vector2d.hpp"
#include <iostream>

class ICollider2d
{
public:
    virtual void update() = 0;
    virtual void render() = 0;
};
class BoxCollider : public ICollider2d
{
public:
    BoxCollider()
    {
        m_collider = new SDL_Rect;
        m_collider->x = 0;
        m_collider->y = 0;
        m_collider->w = 0;
        m_collider->h = 0;
    }

    ~BoxCollider()
    {
        delete m_collider;
    }

    void update()
    {
    }

    void render()
    {
    }

    SDL_Rect &GetCollideBox()
    {
        return *m_collider;
    }

    SDL_bool IsColliding(BoxCollider &object)
    {
        if (m_collider == nullptr)
        {
            return SDL_FALSE;
        }
        const SDL_Rect *temp = object.m_collider;
        if (temp == nullptr)
        {
            return SDL_FALSE;
        }
        return SDL_HasIntersection(m_collider, temp);
    }

    void SetDimension(int w, int h)
    {
        m_collider->w = w;
        m_collider->h = h;
    }

    void SetPosition(int x, int y)
    {
        m_collider->x = x;
        m_collider->y = y;
    }

    // Special function to automatically set the bounding box
    // This function will look at a surface, and create
    // a bounding box tightly fit around the surfaces
    //  minimum and maximum x and y values.
    Vector2d SetoundsAutomatically(SDL_Surface *surfaces, Uint8 red, Uint8 green, Uint8 blue)
    {
        SDL_LockSurface(surfaces);
        int w = surfaces->w;
        int h = surfaces->h;
        int pitch = surfaces->pitch; // its the actual witdth of the image
        int colorChannel = pitch / w;
        Uint8* pixels = (Uint8*)surfaces->pixels;
        // std::cout << "w: " << w << std::endl;
        // std::cout << "h: " << h << std::endl;
        // std::cout << "pitch: " << pitch << std::endl;
        // std::cout << "colorchannels: " << colorChannel << std::endl;
        // std::cout << SDL_GetPixelFormatName(surfaces->format->format) << std::endl;
        SDL_UnlockSurface(surfaces);

        int xmin = w;
        int xmax = 0;
        int ymin = h;
        int ymax = 0;

        for (int y = 0; y < h; y++)
        {
            for (int x = 0; x < w * colorChannel; x += colorChannel)
            {
                if ((pixels[y * (w*colorChannel) + x] == blue) &&
                    (pixels[y * (w*colorChannel) + x+  1] == green )&&
                    (pixels[y * (w*colorChannel) + x+ 2] == red))
                {
                    // pixels must be transparent
                }
                else
                {
                    // update the smallest and largest
                    // values of non-transparent pixels
                    xmin = std::min(x, xmin);
                    ymin = std::min(y, ymin);

                    xmax = std::max(x,xmax);
                    ymax = std::max(y,ymax);
                }
            }
        }

        // updates out boudingbox
        // note that the max will always be greater than minimum value
        // for witdth , we need to deivide by the pitch of our object
        int scale = (1200 / 300);
        m_collider->w = ((xmax / colorChannel - xmin / colorChannel) / (scale));
        m_collider->h = (ymax - ymin) / scale;
        //    m_colliderRectangle->x = m_colliderRectangle->x;
        //    m_colliderRectangle->y = m_colliderRectangle->y;

        //    std::cout << "m_col.w: " << m_colliderRectangle->w << std::endl;
        //    std::cout << "m_col.h: " << m_colliderRectangle->h << std::endl;
        //    std::cout << "xmin: " << xmin << std::endl;
        //    std::cout << "xmax: " << xmax << std::endl;
        //    std::cout << "ymin: " << ymin << std::endl;
        //    std::cout << "ymax: " << ymax << std::endl;

        Vector2d result;
        result.x = xmin / (colorChannel * scale);
        result.y = ymin / scale;
        return result;
    }

private:
    SDL_Rect *m_collider;
    
};

#endif