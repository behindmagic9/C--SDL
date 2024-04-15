#ifndef GAME_ENTITY_HPP
#define GAME_ENTITY_HPP
#include<SDL2/SDL.h>
#include<string>
#include "TextureRectangle.hpp"

class GameEntity{
public:
    GameEntity(){
        m_rect = nullptr;
    }

    GameEntity(SDL_Renderer* renderer,std::string filepath){
        m_renderer = renderer;
        m_rect = new TextureRectangle(m_renderer,filepath);
    }

    ~GameEntity(){
        std::cout << "Game Entity freed" << std::endl;
        // delete m_renderer;
        delete m_rect;
        // delete m_renderer;
        SDL_DestroyRenderer(m_renderer);
    }

    void update(){

    }

    void Render(){
        if(nullptr != m_rect){
            m_rect->Render(m_renderer);
        }
    }

    TextureRectangle& GetTextureRectangle(){
        return *m_rect;
    }

private:
    TextureRectangle* m_rect;
    SDL_Renderer* m_renderer;
};



#endif