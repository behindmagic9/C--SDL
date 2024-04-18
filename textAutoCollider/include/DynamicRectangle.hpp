#ifndef DYNAMIC_RECTANGLE_HPP
#define DYNAMIC_RECTANGLE_HPP


/*!
	DynamicText objects can change, but they are more expensive
	to use, because the textures are constantly recreated each frame.
*/

#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<string>

class DynamicText{
    public:
        DynamicText(std::string filepath, size_t fontsize) ;

        ~DynamicText() ;

        void DrawText(SDL_Renderer* srender ,std::string text , int x , int y , int w, int h );


    private:
        SDL_Rect m_rectangle;
        SDL_Texture* m_texture= nullptr;
        SDL_Surface* m_surface = nullptr;

        TTF_Font* m_font = nullptr;

        static bool s_ttfinitialised;
        
};

#endif
