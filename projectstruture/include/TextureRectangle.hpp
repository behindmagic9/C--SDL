#ifndef TEXTURE_RECTANGLE_HPP
#define TEXTURE_RECTANGLE_HPP
#include<iostream>
#include<SDL2/SDL.h>

class TextureRectangle
{
public:
// constructor
    TextureRectangle(SDL_Renderer *&renderer, std::string filepath);
// set Rectangle
    void SetRectangle(int x, int y, int w, int h);
    // render
    void render(SDL_Renderer*& renderer);
    // update
    void update();

// Destructor
    ~TextureRectangle();

private:
    SDL_Rect rect;
    SDL_Texture *texture = nullptr;
};

#endif