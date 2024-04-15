#ifndef GAME_ENTITY_HPP
#define GAME_ENTITY_HPP
#include<SDL2/SDL.h>
#include<string>
#include<iostream>
#include "TextureRectangle.hpp"
#include "Collider.hpp"

class GameEntity{
public:
    GameEntity();

    GameEntity(SDL_Renderer* renderer,std::string filepath);

    ~GameEntity();

    void update();

    void Render();

    TextureRectangle& GetTextureRectangle();

    Collider& GetCollider();

private:
    TextureRectangle* m_rect;
    SDL_Renderer* m_renderer;
    Collider* m_collider;
};



#endif