#include "../include/TextureRectangle.hpp"
#include "../include/ResourceManager.hpp"

TextureRectangle::TextureRectangle(SDL_Renderer *&renderer, std::string filepath)
{
    surface  = ResourceManager::GetInstance().GetSurface(filepath.c_str());
    if(surface){
        texture = SDL_CreateTextureFromSurface(renderer, surface);
    }else{
        std::cout << "Resuorce : " <<  filepath << "  not found" << std::endl;
    }
}

void TextureRectangle::Draw(int x, int y, int w, int h)
{
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}


SDL_bool TextureRectangle::IsColiding(TextureRectangle& rect1){
    const SDL_Rect temp = rect1.GetRectangle();
    return SDL_HasIntersection(&rect , &temp);
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
    SDL_FreeSurface(surface);
}