#include<iostream>
#include<SDL2/SDL.h>

int main(){

    SDL_Window* window = nullptr;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL not initliased" << std::endl;
    }

    window = SDL_CreateWindow("c++" , 20,20,640,480 , SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    SDL_Surface* surface = SDL_LoadBMP("../images/kong.bmp");
    if(surface == nullptr){
        std::cout << "image not load" << std::endl;
    }
    
    SDL_SetColorKey(surface,SDL_TRUE,SDL_MapRGB(surface->format,0xFF,0,0xFF));
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    
    SDL_Rect Rectangle;
    Rectangle.x = 50;
    Rectangle.y = 50;
    Rectangle.w = 100;
    Rectangle.h = 100;

    bool isGameRunning = true;
    while(isGameRunning){
        SDL_Event e;

        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                std::cout << "SDL QUIT" << std::endl;
                isGameRunning = false;
            }
        }

        // SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);
        // SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255,255,255 , SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(renderer,50,50,100,125);

        // SDL_RenderDrawRect(renderer,&Rectangle);
        SDL_RenderCopy(renderer,texture,NULL,&Rectangle);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);

    SDL_DestroyWindow(window);

    return 0 ;
}