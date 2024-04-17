#include<SDL2/SDL.h>
#include<string>
#include "../include/TextureRectangle.hpp"
#include "../include/ResourceManager.hpp"

TextureRectangle::TextureRectangle(SDL_Renderer *renderer, std::string filepath)
{
    SDL_Surface* surface  = ResourceManager::GetInstance().GetSurface(filepath.c_str());
    if(surface){
        texture = SDL_CreateTextureFromSurface(renderer, surface);
    }else{
        std::cout << "Resuorce : " <<  filepath << "  not found" << std::endl;
    }
    rect.x = 0;
    rect.y = 0;
    rect.w = 32;
    rect.h = 32;
}

// void TextureRectangle::Draw(int x, int y, int w, int h)
// {
//     rect.x = x;
//     rect.y = y;
//     rect.w = w;
//     rect.h = h;
// }

void TextureRectangle::SetPosition(int x , int y ){
    rect.x = x;
    rect.y = y;
}

void TextureRectangle::SetDimension(int w , int h ){
    rect.w = w;
    rect.h = h;
}

SDL_bool TextureRectangle::IsColiding(TextureRectangle& rect1){
    const SDL_Rect temp = rect1.GetRectangle();
    return SDL_HasIntersection(&rect , &temp);
}

void TextureRectangle::update(){
    
}

void TextureRectangle::Render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer,texture,NULL,&rect);
}

TextureRectangle::~TextureRectangle()
{   
    SDL_DestroyTexture(texture);
}