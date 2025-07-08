#include "../include/GameEntity.hpp"
#include "../include/Collider.hpp"

GameEntity::GameEntity()
{
    m_rect = nullptr;
    // m_collider = nullptr;
}

GameEntity::GameEntity(SDL_Renderer *renderer)
{
    m_renderer = renderer;
    m_rect = nullptr;
}

GameEntity::~GameEntity()
{
    std::cout << "Game Entity freed" << std::endl;
    if (nullptr != m_rect)
        delete m_rect;

    for (int i = 0; i < m_collider.size(); i++)
    {
        if (nullptr != m_collider[i]){
            delete m_collider[i];
        }
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
    for (int i = 0; i<m_collider.size(); i++)
    {
        if (nullptr != m_collider[i])
        {
            // m_collider->Render(m_renderer);
            // its just giginvg color to the rectangle bpox around that 
            SDL_SetRenderDrawColor(m_renderer, 0xFF, 0, 0xFF, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawRect(m_renderer, &m_collider[i]->GetCollideBox());// give the rect to that Collider object
        }
    }
}

TextureRectangle &GameEntity::GetTextureRectangle()
{
    return *m_rect;
}

BoxCollider &GameEntity::GetCollider(size_t index)
{
    return *m_collider[index];
}

void GameEntity::AddCollider2D()
{
    m_collider.push_back(new BoxCollider());
}

void GameEntity::AddTextureRectangleConponent(std::string filepath)
{
    m_rect = new TextureRectangle(m_renderer, filepath);
}

void GameEntity::AddTextureRectangleConponent(std::string filepath, Uint8 red, Uint8 green, Uint8 blue)
{
    m_rect = new TextureRectangle(m_renderer, filepath, red, green, blue);
}

void GameEntity::SetPosition(int x, int y)
{
    if (nullptr != m_rect)
    {
        m_rect->SetPosition(x, y);
    }
    for (int i = 0; i < m_collider.size(); i++)
    {
        if (nullptr != m_collider[i])
        {
            m_collider[i]->SetPosition(x, y);
        }
    }
}

void GameEntity::SetDimension(int w , int h){
    if(nullptr != m_rect){
        m_rect->SetDimension(w,h);
    }
    for (int i = 0; i < m_collider.size(); i++)
    {
        if (nullptr != m_collider[i])
        {
            m_collider[i]->SetDimension(w, h);
        }
    }
}