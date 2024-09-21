#ifndef FONT_HPP
#define FONT_HPP

#include <SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<string>
#include<iostream>

class Font{
    public:
        Font(SDL_Renderer* render) : m_render(render), m_font(nullptr){ }

        ~Font(){
            if(m_font){
                TTF_CloseFont(m_font);
            }
        }

        bool LoadFont(const std::string &path , int fontSize){
            m_font = TTF_OpenFont(path.c_str(),fontSize);
            if(m_font == nullptr){
                std::cout << "failed to load the font" << TTF_GetError() << std::endl;
                return false;
            }
            return true;
        }

        void RenderText(const std::string& message, int x, int y ,SDL_Color color){
            if(!m_font){
                std::cout << "font not loaded" << std::endl;
                return;
            }

            SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, message.c_str(), color);
            if(!textSurface){
                std::cout << "Failed to redner the text sruface" << TTF_GetError() << std::endl;
                return;
            }

            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(m_render, textSurface);
            if(!textTexture){
                std::cout << "Failed to create the texture from  text sruface" << TTF_GetError() << std::endl;
                return; 
            }

            SDL_Rect textRect = {x,y,textSurface->w, textSurface->h};

            SDL_RenderCopy(m_render, textTexture, nullptr , &textRect);

            SDL_DestroyTexture(textTexture);
            SDL_FreeSurface(textSurface);
        }


    private:
        SDL_Renderer* m_render;
        TTF_Font* m_font;
};

#endif 