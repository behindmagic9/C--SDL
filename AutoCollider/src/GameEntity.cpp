#include "../include/GameEntity.hpp"
#include "../include/Collider.hpp"


GameEntity::GameEntity (){
    m_rect = nullptr;
    // m_collider = nullptr;
}

GameEntity::GameEntity(SDL_Renderer* renderer)
{
    m_renderer = renderer;
    m_rect = nullptr;
    // for(auto & i : m_collider)
    //     i = nullptr;
}



GameEntity::~GameEntity()
{
    std::cout << "Game Entity freed" << std::endl;
    if(nullptr != m_rect)
        delete m_rect;

    for(int i =0; i < m_collider.size();i++){
            delete m_collider[i];
    }
}

void GameEntity::update()
{
    // upadte the position as of the collider to be same as of the postion of the srite or m_ rect  
    // if(nullptr != m_rect){
    //     int x = m_rect->GetPositionX();
    //     int y = m_rect->GetPositionY();
    //     int w = m_rect->GetWidth();
    //     int h = m_rect->GetHeight();
    //     if(nullptr != m_collider){
    //         m_collider->SetPosition(x,y);
    //         m_collider->SetDimension(w,h);
    //     }
    // }
}

void GameEntity::Render()
{
    if (nullptr != m_rect)
    {
        m_rect->Render(m_renderer);
    }
    for(auto & i : m_collider){
        if(nullptr != i){
            // m_collider->Render(m_renderer);
            SDL_SetRenderDrawColor(m_renderer,0xFF,0,0xFF,SDL_ALPHA_OPAQUE);
            SDL_RenderDrawRect(m_renderer,&i->GetRectangle());
        }
    }

}

TextureRectangle &GameEntity::GetTextureRectangle()
{
    return *m_rect;
}

Collider& GameEntity::GetCollider(size_t index){
    return *m_collider[index];
}

void GameEntity::AddCollider2D(){
    m_collider.push_back(new Collider());
}



void GameEntity::AddTextureRectangleConponent(std::string filepath){
    m_rect = new TextureRectangle(m_renderer, filepath);
}

void GameEntity::AddTextureRectangleConponent(std::string filepath , Uint8 red, Uint8 green , Uint8 blue){
    m_rect = new TextureRectangle(m_renderer, filepath,red , green , blue);
}