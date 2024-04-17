#include "../include/TextureRectangle.hpp"
#include "../include/ResourceManager.hpp"

TextureRectangle::TextureRectangle(SDL_Renderer *renderer, std::string filepath)
{
    SDL_Surface* surface  = ResourceManager::GetInstance().GetSurface(filepath.c_str());
    if(surface != nullptr){
        texture = SDL_CreateTextureFromSurface(renderer, surface);
    }
    // cant delete the surcae here cause the pointer it conatin it is same as the one in maper so deleting it will corrupt the mapper 
    // so let the resource manager handle that itself
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

void TextureRectangle::render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer,texture,NULL,&rect);
}

TextureRectangle::~TextureRectangle()
{   
    SDL_DestroyTexture(texture);
}