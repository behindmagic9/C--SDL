#ifndef GAME_ENTITY_HPP
#define GAME_ENTITY_HPP
#include<SDL2/SDL.h>
#include<string>
#include<iostream>
#include<vector>
#include "TextureRectangle.hpp"
#include "Collider.hpp"

class GameEntity{
public:
    GameEntity();

    GameEntity(SDL_Renderer* renderer);

    ~GameEntity();

    void update();

    void Render();

    TextureRectangle& GetTextureRectangle();

    Collider& GetCollider(size_t index);
    void AddCollider2D() ; 

    void AddTextureRectangleConponent(std::string filepath);
    void AddTextureRectangleConponent(std::string filepath , Uint8 red, Uint8 green , Uint8 blue);

private:
    TextureRectangle* m_rect;
    SDL_Renderer* m_renderer;
    std::vector<Collider*>  m_collider;
};

#endif