#include "TextureRectangle.hpp"

TextureRectangle::TextureRectangle(SDL_Renderer *&renderer, std::string filepath)
{
    SDL_Surface *surface = SDL_LoadBMP(filepath.c_str());
    if (surface == nullptr)
    {
        std::cout << "image not load" << std::endl;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}
void TextureRectangle::SetRectangle(int x, int y, int w, int h)
{
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

void TextureRectangle::update(){
    
}

void TextureRectangle::render(SDL_Renderer*& renderer)
{
    SDL_RenderCopy(renderer,texture,NULL,&rect);
}

TextureRectangle::~TextureRectangle()
{
    SDL_DestroyTexture(texture);
}