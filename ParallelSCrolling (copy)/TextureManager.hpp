#ifndef TEXTURE_MANAGER
#define TEXTURE_MANAGER
#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include "ResourceManager.hpp"
#include <unordered_map>

class Texture
{

public:
    Texture(SDL_Renderer *render) : texture(nullptr), render(render) {}

    bool Load( std::string filepath)
    {
        SDL_Surface *surface = ResourceManager::GetInstance().GetSurface(filepath.c_str());
        if (surface == nullptr)
        {
            std::cout << "error in loading the surface" << std::endl;
        }
        texture = SDL_CreateTextureFromSurface(render, surface);
        if (!texture)
        {
            std::cout << "Failed to create the texture" << std::endl;
            return false;
        }
        return true;
    }

    bool LoadWithColorKey( std::string filepath, int r, int g, int b)
    {
        SDL_Surface *surface = ResourceManager::GetInstance().GetSurface(filepath.c_str());
        if (surface == nullptr)
        {
            std::cout << "error in loading the surface" << std::endl;
        }
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, r, g, b));
        texture = SDL_CreateTextureFromSurface(render, surface);
        if (!texture)
        {
            std::cout << "Failed to create the texture" << std::endl;
            return false;
        }
        return true;
    }

    ~Texture()
    {
        if (texture)
        {
            SDL_DestroyTexture(texture);
        }
    }

    void Render(SDL_Rect *rect)
    {
        SDL_RenderCopy(render, texture, NULL, rect);
    }


    void Render(SDL_Rect *rect, float angle , SDL_RendererFlip flip)
    {
        SDL_RenderCopyEx(render, texture, NULL, rect,angle , NULL , flip);
    }
    void update();

private:
    SDL_Texture *texture;
    SDL_Renderer *render;
};
#endif