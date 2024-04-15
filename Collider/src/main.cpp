#include <iostream>
#include <SDL2/SDL.h>
#include "../include/TextureRectangle.hpp"
#include "../include/GameEntity.hpp"
#include "../include/SDL_App.h"
#include "../include/Animated_sprite.hpp"
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
            if (rect1->GetCollider().isCollide(rect->GetCollider()))
            {
                std::cout << "IS colidding " << std::endl;
            }
         
            else
            {
                std::cout << "not colliding " << std::endl;
            }
        }
    }
}

void HandleRendering()
{

    rect->GetTextureRectangle().SetPosition(app->GetMouseX(),app->GetMouseY());
    rect->GetTextureRectangle().SetDimension(100,100);

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

    rect1->GetTextureRectangle().SetPosition(posX,posY);
    rect1->GetTextureRectangle().SetDimension(100,100);

    rect->Render();
    rect1->Render();

}

void HandleUpdate(){
    rect->update();
    rect1->update();
}

int main()
{
    const char* title = "New SDL2 Abstraction";
    app = new SDLApp(title, 10, 10, 640, 480);
    app->SetMaxFrameRate(8);

    rect = new GameEntity(app->GetRender(), "../Assets/load.bmp"); // before was TextureRectange(app->GetRender(),....)
    rect1 = new GameEntity(app->GetRender(), "../Assets/load.bmp");

    app->SetEventCallback(HandleEvents);
    app->SetUpdateCallback(HandleUpdate);
    app->SetRenderCallback(HandleRendering);

    app->RunLoop();

    delete rect;
    delete rect1;
    delete app;

    return 0;
}
