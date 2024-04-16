#ifndef TEXTURE_RECTANGLE_HPP
#define TEXTURE_RECTANGLE_HPP
#include<string>
#include<SDL2/SDL.h>

class TextureRectangle
{
public:
// constructor
    TextureRectangle(SDL_Renderer *renderer, std::string filepath);

    TextureRectangle(SDL_Renderer *renderer, std::string filepath, Uint8 red, Uint8 blue , Uint8 green);
    // render
    void Render(SDL_Renderer* renderer);
    // update
    void update();


    void InitDefaults();

    void SetPosition(int x , int y );
    void SetDimension(int w, int h );
 
    int GetPositionX();
    int GetPositionY();
    int GetWidth();
    int GetHeight();
    Uint8 GetRedColor();
    Uint8 GetGreenColor();
    Uint8 GetBlueColor();


    SDL_Texture* GetSDLTexture();
    SDL_Rect& GetSDLRect();
    SDL_Rect* GetSDLRectPtr();

// Destructor
    ~TextureRectangle();

private:
    SDL_Rect rect;
    inline SDL_Rect GetRectangle() const { return rect ;} 
    SDL_Texture *texture = nullptr; 
    SDL_Surface* surface = nullptr;

    Uint8 m_red ;
    Uint8 m_blue ;
    Uint8 m_green ;
};

#endif