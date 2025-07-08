#ifndef SPRITE_TEXTURE
#define SPRITE_TEXTURE
#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include "ResourceManager.hpp"

class SpriteTexture
{
public:
    SpriteTexture(SDL_Renderer *render) : texture(nullptr), render(render) {}

    bool LoadSprite(std::string filepath)
    {
        SDL_Surface *surface = ResourceManager::GetInstance().GetSurface(filepath.c_str());
        if (surface == nullptr)
        {
            std::cout << "error in loading the surface" << std::endl;
        }
        // SDL_SetColorKey(surface, SDL_TRUE , SDL_MapRGB(surface->format, ))
        texture = SDL_CreateTextureFromSurface(render, surface);
        if(!texture){
            std::cout << "not bale to laod the texture sprite " << std::endl;
            return false;
        }
        return true;
    }

    ~SpriteTexture()
    {
        if (texture)
        {
            SDL_DestroyTexture(texture);
        }
    }

    void Render( SDL_Rect *src, SDL_Rect *dst)
    {
        SDL_RenderCopy(render, texture, src, dst);
    }

    void update() {};

private:
    SDL_Renderer *render;
    SDL_Texture *texture;
};
#endif