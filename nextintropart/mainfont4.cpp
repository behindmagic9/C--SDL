#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>

int main(){

    SDL_Window* window = nullptr;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL not initialised" << std::endl;
    }

    window = SDL_CreateWindow("C++ window",10,10,640,480,SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    if(TTF_Init() == -1){
        std::cout << "ttf could not be initialised " << std::endl;
    }

    TTF_Font* font  = TTF_OpenFont("../images/font.ttf",40);

    if(font == nullptr){
        std::cout << "Font not laoded " << std::endl;
        exit(1);
    }

    // SDL_Surface* surface = TTF_RenderText_Solid(font,"SDL program " , {255,255,255}); // for only fg
    SDL_Surface* surface = TTF_RenderText_Shaded(font,"SDL program " ,{0,0,0} ,{255,255,255}); // for only fg and bg both 

    SDL_Texture* texture  = SDL_CreateTextureFromSurface(renderer,surface);

    SDL_FreeSurface(surface);

    SDL_Rect rectangle;
    rectangle.x = 10;
    rectangle.y = 10;
    rectangle.w = 400;
    rectangle.h = 100;

    bool isGameRunning = true;
    while(isGameRunning){
        SDL_Event e;
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                isGameRunning=false;
            }
        }

        SDL_SetRenderDrawColor(renderer,0,0,0xff,SDL_WINDOW_SHOWN);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer,texture , NULL,&rectangle);

        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}