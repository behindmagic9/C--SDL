#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

int main(){

    SDL_Window* window = nullptr;
    window = SDL_CreateWindow("c++ program " , 10,10,640,480,SDL_WINDOW_SHOWN);
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL not initlaised " << std::endl;
    }
    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);


    int flags = IMG_INIT_PNG;
    int initStatus = IMG_Init(flags);
    if((initStatus & flags) != flags){
        std::cout << "SDL image format not found" << std::endl;
    }


    SDL_Surface* surface = IMG_Load("../images/mario.png");
    if(surface == nullptr){
        std::cout << "image not found" << std::endl;
    }

    SDL_Texture* texture = nullptr;
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

    bool isGamerunning = true;
    while(isGamerunning){
        SDL_Event e;
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                isGamerunning = false;
            }
        }

        // create a clear canvas
        SDL_SetRenderDrawColor(renderer,0,0,0xff,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer,texture,NULL,NULL);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}