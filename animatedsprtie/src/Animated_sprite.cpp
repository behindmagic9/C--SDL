#include "../include/Animated_sprite.hpp"
#include "../include/ResourceManager.hpp"

Animated_Sprite::Animated_Sprite(SDL_Renderer *&renderer, std::string filepath)
{
    SDL_Surface *surface = ResourceManager::GetInstance().GetSurface(filepath);
    if(surface == nullptr){
        std::cout << "not found " << std::endl;
    } 
    SDL_SetColorKey(surface,SDL_TRUE,SDL_MapRGB(surface->format,241,216,98));
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}
void Animated_Sprite::Draw(int x, int y, int w, int h)
{
    dest.x = x;
    dest.y = y;
    dest.w = w;
    dest.h = h;
}

void Animated_Sprite::PlayFrame(int x, int y,int w , int h , int frame){
    src.x = x+frame*w;
    src.y = y;
    src.w = w;
    src.h = h;

}

void Animated_Sprite::update(){
    
}

void Animated_Sprite::render(SDL_Renderer*& renderer)
{
    SDL_RenderCopy(renderer,texture,&src,&dest);
}

Animated_Sprite::~Animated_Sprite()
{
    SDL_DestroyTexture(texture);
}