#include <SDL2/SDL.h>
#include <string>
#include "../include/TextureRectangle.hpp"
#include "../include/ResourceManager.hpp"

TextureRectangle::TextureRectangle(SDL_Renderer *renderer, std::string filepath)
{
    SDL_Surface* surface = ResourceManager::GetInstance().GetSurface(filepath.c_str());
    if (surface != nullptr)
    {
        SDL_SetColorKey(surface,SDL_FALSE,SDL_MapRGB(surface->format ,m_red, m_blue , m_green));
        texture = SDL_CreateTextureFromSurface(renderer, surface);
    }
    else
    {
        std::cout << "Resuorce : " << filepath << "  not found" << std::endl;
    }
    InitDefaults();
}
TextureRectangle::TextureRectangle(SDL_Renderer *renderer, std::string filepath, Uint8 red, Uint8 blue , Uint8 green){
    SDL_Surface* surface = ResourceManager::GetInstance().GetSurface(filepath.c_str());
    if (surface != nullptr)
    {
        SDL_SetColorKey(surface,SDL_TRUE,SDL_MapRGB(surface->format ,red, blue , green));        
        texture = SDL_CreateTextureFromSurface(renderer, surface);
    }
    else
    {
        std::cout << "Resuorce : " << filepath << "  not found" << std::endl;
    }
    InitDefaults();

    m_red = red;
    m_green = green;
    m_blue = blue;

}
void TextureRectangle::InitDefaults(){
    
    rect.x = 0;
    rect.y = 0;
    rect.w = 32;
    rect.h = 32;

    m_red = 0xFF;
    m_blue = 0xFF;
    m_green = 0x00 ;
    
}

// void TextureRectangle::Draw(int x, int y, int w, int h)
// {
//     rect.x = x;
//     rect.y = y;
//     rect.w = w;
//     rect.h = h;
// }


void TextureRectangle::SetPosition(int x, int y)
{
    rect.x = x;
    rect.y = y;
}

void TextureRectangle::SetDimension(int w, int h)
{
    rect.w = w;
    rect.h = h;
}

SDL_Rect* TextureRectangle::GetSDLRectPtr(){
    return &rect;
}

SDL_Rect& TextureRectangle::GetSDLRect(){
    return rect;
}

SDL_Texture* TextureRectangle::GetSDLTexture(){
    return texture;
}

int TextureRectangle::GetPositionX(){
    return rect.x;
}
int TextureRectangle::GetPositionY(){
    return rect.y;

}
int TextureRectangle::GetWidth(){
    return rect.w;

}
int TextureRectangle::GetHeight(){
    return rect.h;

}

Uint8 TextureRectangle::GetRedColor(){
    return m_red;
}
Uint8 TextureRectangle::GetBlueColor(){
    return m_blue;
}
Uint8 TextureRectangle::GetGreenColor(){
    return m_green;
}
void TextureRectangle::update()
{
}

void TextureRectangle::Render(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

TextureRectangle::~TextureRectangle()
{
    SDL_DestroyTexture(texture);
}