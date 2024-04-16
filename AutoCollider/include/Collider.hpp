#ifndef COLLIDER_HPP
#define COLLIDER_HPP
#include <SDL2/SDL.h>

class Collider
{
public:
    Collider();

    SDL_bool isCollide(Collider &obj1);

    ~Collider();

    void SetPosition(int x, int y);

    SDL_Rect& GetRectangle();

    void SetDimension(int w, int h);
    
// not really needed 
    // void update() ;  
    // void render(); 

    // void Render(SDL_Renderer* rend){

    // }

private:
    // SDL_Rect m_rect; // we have to make it dynamic that isa poniter to make it more texture out from this 
    // or say dynamically creating more textures
    SDL_Rect* m_rect;
    // SDL_Renderer* renderer;
};

#endif