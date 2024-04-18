#include <iostream>
#include <SDL2/SDL.h>
#include "../include/TextureRectangle.hpp"
#include "../include/GameEntity.hpp"
#include "../include/SDL_App.h"
#include "../include/Animated_sprite.hpp"
#include "../include/Vector2d.hpp"
#include "../include/ResourceManager.hpp"
#include "../include/Sound.hpp"
#include <vector>
#include <string>
#include <memory>

SDLApp* app;

GameEntity* obj1; // game entioyt type containing its vector of collider like set fo more rectangles of that object type
GameEntity* obj2;

Sound* CollisionSound;

// before was
// TextureRectangle* obj1;
// TextureRectangle* obj2;


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
            // checking object of obj2 's vector in which of its set of entity like "arrow" is stricking the other entity of type obj1 , in thats set of object particular 0 index object is colldign or not  with obj2's  index object 

            if (obj2->GetCollider(0).IsColliding(obj1->GetCollider(0)))
            {
                std::cout << "IS colidding with hit box 1" << std::endl;
                CollisionSound->PlaySound();
            }else{
                std::cout <<  " nOt colliding with hit box 1" << std::endl;
            }

            if(obj2->GetCollider(0).IsColliding(obj1->GetCollider(1))){
                std::cout << "is colliding with hit box 2" << std::endl;
                CollisionSound->PlaySound();
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

    obj1->Render();
    obj2->Render();

}

void HandleUpdate(){
    obj1->update();
    obj2->update();

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
    // object which is moving all around the screen by itself
    obj2->SetPosition(posX,posY);
    obj2->SetDimension(100,100);

    obj1->SetPosition(app->GetMouseX(),app->GetMouseY());
    obj1->SetDimension(300,300);

// its givng the object 1 ehcih is moving with mouse the boadries like setting its dimension  adn its postionj is as set to the mosue poisiton , but boundaries are given now,
// setting width of that too the wholeoriginal surface of kong without the SDL_St colorKey how look like ,  by GetTextureRectangle().GetWidth() and height of original surface divide by 2
    obj1->GetCollider(1).SetDimension(obj1->GetTextureRectangle().GetWidth(), obj1->GetTextureRectangle().GetHeight()/2);

// this be set the boundaries of the second boaundaries to the kong auto setting the boundaries especailly by a n algorithm
    Vector2d dims = obj1->GetCollider(0).SetoundsAutomatically(ResourceManager::GetInstance().GetSurface("../Assets/kong.bmp"), 0xff,0x00,0xff);
// then storing those dimesions of x and y to the vector2d of x and y mamber variables..
    int newXpos = dims.x + app->GetMouseX();
    int newYpos = dims.y + app->GetMouseY();

    // so updated position  be like is dims.x + mousex coordinates
    // same for y coordinates

    // then setting the obj1 which is moving by mouse to the updates posx and posy of the rectangel of obj1's index 0 enity 's rectangle boundaries positon.
    obj1->GetCollider(0).SetPosition(newXpos,newYpos);
}

int main()
{
    const char* title = "New SDL2 Abstraction";
    // with this bit wise or operator we are passing bith subsystem to the SDL to initialise them
    app = new SDLApp(SDL_INIT_AUDIO | SDL_INIT_VIDEO,title, 10, 10, 640, 480);
    app->SetMaxFrameRate(8);

    obj1 = new GameEntity(app->GetRender()); // before was TextureRectange(app->GetRender(),....)
    obj1->AddTextureRectangleConponent("../Assets/kong.bmp", 0xff,0x00,0xff);
    obj1->AddCollider2D();
    obj1->AddCollider2D();

    obj2 = new GameEntity(app->GetRender());
    obj2->AddTextureRectangleConponent( "../Assets/kong.bmp"); // not given color key son not be transparent
    obj2->AddCollider2D();

    CollisionSound = new Sound("../Assets/Sound/Colide.wav");
    CollisionSound->SetUpDevice();

    app->SetEventCallback(HandleEvents);
    app->SetUpdateCallback(HandleUpdate);
    app->SetRenderCallback(HandleRendering);

    app->RunLoop();

    delete app;
    delete obj1;
    delete obj2;

    return 0;
}
