#include <iostream>
#include <SDL2/SDL.h>
#include "../include/TextureRectangle.hpp"
#include <vector>
#include<string>
#include <memory>

int main()
{

    SDL_Window *window = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL not initliased" << std::endl;
    }

    window = SDL_CreateWindow("c++", 20, 20, 640, 480, SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = nullptr;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    TextureRectangle rect(renderer, "../Assets/load.bmp");
    TextureRectangle rect1(renderer, "../Assets/load.bmp");

   
    // SDL_SetColorKey(surface,SDL_TRUE,SDL_MapRGB(surface->format,0xFF,0,0xFF));

    bool isGameRunning = true;
    while (isGameRunning)
    {
        SDL_Event e;

        int mousex;
        int mousey;
        Uint32 buttons;
        buttons = SDL_GetMouseState(&mousex,&mousey);

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                std::cout << "SDL QUIT" << std::endl;
                isGameRunning = false;
            }
            if(e.button.button == SDL_BUTTON_LEFT){
                if(rect1.IsColiding(rect)){
                    std::cout << "IS colidding " << std::endl;
                }else{
                    std::cout << "not colliding " << std::endl;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        rect.Draw(50,50,100,100);
        rect1.Draw(mousex,mousey,100,100);

        rect.render(renderer);
        rect1.render(renderer);
        
        SDL_RenderPresent(renderer);
        
    }

    SDL_DestroyWindow(window);

    return 0;
}