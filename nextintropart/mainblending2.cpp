#include <iostream>
#include <SDL2/SDL.h>
// #include <SDL2/SDL.h>/

int main()
{

    SDL_Window *window = nullptr;



    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL not initilised" << std::endl;
    } 

    window = SDL_CreateWindow("c++", 20,20,640,480,SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    SDL_Surface* surface = SDL_LoadBMP("../images/kong.bmp");
    SDL_SetColorKey(surface,SDL_TRUE,SDL_MapRGB(surface->format,0xFF,0,0xFF));

    SDL_Texture* texture =  SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);


    SDL_Rect Rectangle;
    Rectangle.x = 50;
    Rectangle.y = 50;
    Rectangle.w = 200;
    Rectangle.h = 200;
    
    SDL_Rect Rectangle2;
    Rectangle2.x = 50;
    Rectangle2.y = 50;
    Rectangle2.w = 200;
    Rectangle2.h = 200;


    bool isGameRunning = true;
    while(isGameRunning){
        SDL_Event e;
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                std::cout << "SDL Quit" << std::endl;
                isGameRunning = false;
            }
            if(e.type == SDL_MOUSEMOTION){
                Rectangle2.x = e.motion.x;
                Rectangle2.y = e.motion.y;
            }
            if(e.type == SDL_MOUSEBUTTONDOWN){
                if(e.button.button == SDL_BUTTON_LEFT){
                    SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_ADD);
                }else if(e.button.button == SDL_BUTTON_MIDDLE){
                    SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_BLEND);
                }else if(e.button.button == SDL_BUTTON_RIGHT){
                    SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_MOD);
                }
            }else{
                SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_NONE);
            }
        }
    // making a clear canvas 
        SDL_SetRenderDrawColor(renderer,0,0,0xFF,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer,0,0,255,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer,texture,NULL,&Rectangle);
        SDL_RenderCopy(renderer,texture,NULL,&Rectangle2);
        
        SDL_RenderPresent(renderer);
    }



    SDL_DestroyTexture(texture);



    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}