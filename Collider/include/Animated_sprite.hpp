#ifndef ANIMATED_SPRITE_HPP
#define ANIMATED_SPRITE_HPP
#include<iostream>
#include<SDL2/SDL.h>

class Animated_Sprite
{
public:
// constructor
    Animated_Sprite(SDL_Renderer *&renderer, std::string filepath);
// set Rectangle
    void Draw(int x, int y, int w, int h);

    void PlayFrame(int x, int y, int w, int h, int frame);

    // render
    void render(SDL_Renderer*& renderer);
    // update
    void update();

// Destructor
    ~Animated_Sprite();

private:
    SDL_Rect dest ;
    SDL_Rect src;
    SDL_Texture *texture = nullptr;
    SDL_Surface *surface = nullptr;
};

#endif