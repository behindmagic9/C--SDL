

#include <iostream>
#include "../include/DynamicRectangle.hpp"

DynamicText::DynamicText(std::string filepath, size_t fontsize)
{
    if (!s_ttfinitialised && TTF_Init() == -1)
    {
        std::cout << "could not initialised the SDL2 tff error" << TTF_GetError() << std::endl;
    }
    else if(!s_ttfinitialised)
    {
        // decalre static so only once  be intiliase , even if have multiple font objects
        s_ttfinitialised = true;
    }
    m_font = TTF_OpenFont(filepath.c_str(), fontsize);

    if (m_font == nullptr)
    {
        std::cout << "Could not load the font " << std::endl;
        exit(1);
    }
}

DynamicText::~DynamicText()
{
    SDL_DestroyTexture(m_texture);
    TTF_CloseFont(m_font);
}

void DynamicText::DrawText(SDL_Renderer *render, std::string text, int x, int y, int w, int h)
{
    m_surface = TTF_RenderText_Shaded(m_font, text.c_str(),{0,120,65} ,{0, 0, 255});

    m_texture = SDL_CreateTextureFromSurface(render, m_surface);
    SDL_FreeSurface(m_surface);

    // inititalising the rectangle for text
    m_rectangle.x = x;
    m_rectangle.y = y;
    m_rectangle.w = w;
    m_rectangle.h = h;

    // rendereing the text inside the rectagnel
    SDL_RenderCopy(render, m_texture, NULL, &m_rectangle);
    if (m_texture != nullptr)
    {
        // destroy texture
        SDL_DestroyTexture(m_texture);
    }
}

bool DynamicText::s_ttfinitialised = false;



