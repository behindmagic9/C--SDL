#ifndef TEXTURE_RECTANGLE_HPP
#define TEXTURE_RECTANGLE_HPP
#include<string>
#include<SDL2/SDL.h>

class TextureRectangle
{
public:
// constructor
    TextureRectangle(SDL_Renderer *renderer, std::string filepath);
    // render
    void Render(SDL_Renderer* renderer);
    // update
    void update();

    SDL_bool IsColiding(TextureRectangle& rect);

    void SetPosition(int x , int y );
    void SetDimension(int w, int h );
 
    int GetPositionX();
    int GetPositionY();
    int GetWidth();
    int GetHeight();

// Destructor
    ~TextureRectangle();

private:
    SDL_Rect rect;
    inline SDL_Rect GetRectangle() const { return rect ;} 
    SDL_Texture *texture = nullptr; 
};

#endif