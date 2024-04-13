#include <iostream>
#include <SDL2/SDL.h>
#include "TextureRectangle.hpp"
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

    std::vector<std::shared_ptr<TextureRectangle>> rectangles;
    for (int i = 0; i < 10; i++)
    {
        std::shared_ptr<TextureRectangle> rect = std::make_shared<TextureRectangle>(renderer, "../images/kong.bmp");
        rectangles.push_back(rect);
    }
    int row = 0;
    int col = 1;
    for( int i = 0; i<10;i++){
        rectangles[i]->SetRectangle(100*col,30*row,200,200);
        if(i%3==0){
            row++;
            col=1;
        }
        col++;
    }
    // SDL_SetColorKey(surface,SDL_TRUE,SDL_MapRGB(surface->format,0xFF,0,0xFF));

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

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        for (auto &rects : rectangles)
        {
            rects->render(renderer);
        }
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);

    return 0;
}