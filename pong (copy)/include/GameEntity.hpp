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

    // Retrieve Components
    TextureRectangle& GetTextureRectangle();

    BoxCollider& GetCollider(size_t index);

    // Update
    // Note: Sets the position of our game entity
    //       This operates by moving all of the
    //       Components position as well so they are
    //       updated.   
    void SetPosition(int x , int y);
    // Sets all of the components to a specified dimension
    void SetDimension(int w , int h);

    void AddTextureRectangleConponent(std::string filepath);
    
    void AddTextureRectangleConponent(std::string filepath , Uint8 red, Uint8 green , Uint8 blue);
    
    // Add another box collider to our object.
    void AddCollider2D() ; 

private:
    TextureRectangle* m_rect;
    SDL_Renderer* m_renderer;
    std::vector<BoxCollider*>  m_collider;
};

#endif