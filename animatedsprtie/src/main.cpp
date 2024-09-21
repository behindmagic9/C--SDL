#include <iostream>
#include <SDL2/SDL.h>
#include "../include/Animated_sprite.hpp"
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

    Animated_Sprite animate(renderer,"../Assets/edited.bmp");
    
    animate.Draw(200,200,150,150);

    bool isGameRunning = true;
    while (isGameRunning)
    {
        SDL_Event e;

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                std::cout << "SDL QUIT" << std::endl;
                isGameRunning = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255,255, 255, SDL_ALPHA_OPAQUE);
        static int frame = 0;
        animate.PlayFrame(0,0,170,110,frame);
        animate.render(renderer);
        frame++;
        if(frame>6){
            frame = 0;
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(100);
    }

    SDL_DestroyWindow(window);

    return 0;
}