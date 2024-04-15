#include "../include/GameEntity.hpp"
#include "../include/Collider.hpp"

GameEntity::GameEntity()
{
    m_rect = nullptr;
}
 
GameEntity::GameEntity(SDL_Renderer *renderer, std::string filepath)
{ 
    m_renderer = renderer;
    m_rect = new TextureRectangle(m_renderer, filepath);
    m_collider = new Collider();
}

GameEntity::~GameEntity()
{
    std::cout << "Game Entity freed" << std::endl;
    // delete m_renderer;
    if(nullptr != m_rect)
        delete m_rect;

    if(nullptr != m_collider){
        delete m_collider;
    }
    // delete m_renderer;
    // SDL_DestroyRenderer(m_renderer);
}

void GameEntity::update()
{
    // upadte the position as of the collider to be same as of the postion of the srite or m_ rect  
    if(nullptr != m_rect){
        int x = m_rect->GetPositionX();
        int y = m_rect->GetPositionY();
        int w = m_rect->GetWidth();
        int h = m_rect->GetHeight();
        if(nullptr != m_collider){
            m_collider->SetPosition(x,y);
            m_collider->SetDimension(w,h);
        }
    }


}

void GameEntity::Render()
{
    if (nullptr != m_rect)
    {
        m_rect->Render(m_renderer);
    }

    if(nullptr != m_collider){
        // m_collider->Render(m_renderer);
        SDL_SetRenderDrawColor(m_renderer,255,0,255,SDL_ALPHA_OPAQUE);
        SDL_RenderDrawRect(m_renderer,&m_collider->GetRectangle());
    }
}

TextureRectangle &GameEntity::GetTextureRectangle()
{
    return *m_rect;
}

Collider& GameEntity::GetCollider(){
    return *m_collider;
}
