#include<iostream>
#include<SDL2/SDL.h>

int main(){

    SDL_Window* window = nullptr;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL not initialsed" << std::endl;
    }

    window = SDL_CreateWindow("c++ window" , 10,10,640,480,SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    SDL_Surface* surface = SDL_LoadBMP("../images/pool.bmp");
    if(surface == nullptr){
        std::cout << "file not found " << std::endl;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

    SDL_Rect rectangle;
    rectangle.x = 0;
    rectangle.y = 0;
    rectangle.w = 640;
    rectangle.h = 480;

    SDL_Rect rectangle2;
    rectangle2.x = -639;
    rectangle2.y = 0;
    rectangle2.w = 640;
    rectangle2.h = 480;

    SDL_Rect rectangle3;
    rectangle3.x = 0;
    rectangle3.y = 0;
    rectangle3.w = 640;
    rectangle3.h = 480;

    SDL_Rect rectangle4;
    rectangle4.x = 0;
    rectangle4.y = -480;
    rectangle4.w = 640;
    rectangle4.h = 480;

    bool isGameRunning = true;
    while(isGameRunning){
        SDL_Event e;
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                isGameRunning = false;
            }
            if(e.type == SDL_MOUSEBUTTONDOWN){
                if(e.button.button == SDL_BUTTON_LEFT){
                    SDL_SetTextureBlendMode(texture2,SDL_BLENDMODE_ADD);
                }
                if(e.button.button == SDL_BUTTON_RIGHT){
                    SDL_SetTextureBlendMode(texture2,SDL_BLENDMODE_BLEND);
                }
                if(e.button.button == SDL_BUTTON_MIDDLE){
                    SDL_SetTextureBlendMode(texture2,SDL_BLENDMODE_MOD);
                }
            }
        }

        SDL_SetRenderDrawColor(renderer,0,0,0xff,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        int w,h;
        SDL_QueryTexture(texture,NULL,NULL,&w,&h);

        SDL_Delay(20);

        rectangle.x++;
        if(rectangle.x > 639){
            rectangle.x = -639;
        }

        rectangle2.x++;
        if(rectangle2.x > 639){
            rectangle2.x = -639;
        }

        rectangle3.y++;
        if(rectangle3.y > 479){
            rectangle3.y = -479;
        }

        rectangle4.y++;
        if(rectangle4.y > 479){
            rectangle4.y = -479;
        }

        SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_NONE);
        SDL_RenderCopy(renderer,texture,NULL,&rectangle);
        SDL_RenderCopy(renderer,texture,NULL,&rectangle2);
        SDL_RenderCopy(renderer,texture2,NULL,&rectangle3);
        SDL_RenderCopy(renderer,texture2,NULL,&rectangle4);
        

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}