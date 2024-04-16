#include <iostream>
#include <SDL2/SDL.h>
#include "../include/TextureRectangle.hpp"
#include "../include/GameEntity.hpp"
#include "../include/SDL_App.h"
#include "../include/Animated_sprite.hpp"
#include "../include/Vector2d.hpp"
#include "../include/ResourceManager.hpp"
#include <vector>
#include <string>
#include <memory>

SDLApp* app;

GameEntity* rect;
GameEntity* rect1;

// before was
// TextureRectangle* rect;
// TextureRectangle* rect1;


void HandleEvents()
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            app->StopAppLoop() ;
        }
        if (e.button.button == SDL_BUTTON_LEFT)
        {
            if (rect1->GetCollider(0).IsColliding(rect->GetCollider(0)))
            {
                std::cout << "IS colidding with hit box 1" << std::endl;
            }else{
                std::cout <<  " nOt colliding with hit box 1" << std::endl;
            }

            if(rect1->GetCollider(0).IsColliding(rect->GetCollider(1))){
                std::cout << "is colliding with hit box 2" << std::endl;
            }
            else
            {
                std::cout << "not colliding with hit box 2" << std::endl;
            }
        }
    }
}

void HandleRendering()
{

    rect->Render();
    rect1->Render();

}

void HandleUpdate(){
    rect->update();
    rect1->update();

    static bool up =true;
    static bool right = true;
    static int posX = 0;
    static int posY = 0;

    if(up){
        posY--;
    }else{
        posY++;
    }

    if(right){
        posX++;
    }else{
        posX--;
    }

    if(posX+100 > app->GetWindowWidth()){
        right = false;
    }else if(posX < 0){
        right = true;
    }

    if(posY+100 >= app->GetWindowHeight()){
        up = true;
    }else if(posY < 0 ){
        up = false;
    }

    rect1->SetPosition(posX,posY);
    rect1->SetDimension(100,100);

    rect->SetPosition(app->GetMouseX(),app->GetMouseY());
    rect->SetDimension(300,300);

    rect->GetCollider(1).SetDimension(rect->GetTextureRectangle().GetWidth(), rect->GetTextureRectangle().GetHeight()/2);

    Vector2d dims = rect->GetCollider(0).SetoundsAutomatically(ResourceManager::GetInstance().GetSurface("../Assets/kong.bmp"), 0xff,0x00,0xff);

    int newXpos = dims.x + app->GetMouseX();
    int newYpos = dims.y + app->GetMouseY();

    rect->GetCollider(0).SetPosition(newXpos,newYpos);
}

int main()
{
    const char* title = "New SDL2 Abstraction";
    app = new SDLApp(title, 10, 10, 640, 480);
    app->SetMaxFrameRate(8);

    rect = new GameEntity(app->GetRender()); // before was TextureRectange(app->GetRender(),....)
    rect->AddTextureRectangleConponent("../Assets/kong.bmp", 0xff,0x00,0xff);
    rect->AddCollider2D();
    rect->AddCollider2D();

    rect1 = new GameEntity(app->GetRender());
    rect1->AddTextureRectangleConponent( "../Assets/kong.bmp");
    rect1->AddCollider2D();


    app->SetEventCallback(HandleEvents);
    app->SetUpdateCallback(HandleUpdate);
    app->SetRenderCallback(HandleRendering);

    app->RunLoop();

    delete app;
    delete rect1;
    delete rect;

    return 0;
}
