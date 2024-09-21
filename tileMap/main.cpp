#include <iostream>
#include <SDL2/SDL.h>

int main()
{
    SDL_Window *window = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not be initialized! SDL Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    window = SDL_CreateWindow("Ninja Animation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Renderer *render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!render)
    {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Load images
    SDL_Surface *tiles_surface = SDL_LoadBMP("images/tile.bmp");

    if (!tiles_surface)
    {
        std::cout << "Error loading images! SDL Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Create textures
    SDL_Texture *tiles_texture = SDL_CreateTextureFromSurface(render, tiles_surface);

    SDL_FreeSurface(tiles_surface);

    // Define positions and sizes of elements
    SDL_Rect tiles_rect = {0, 0, 64, 64};

    bool isGameRunning = true;

    while (isGameRunning)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isGameRunning = false;
            }

            // Detect spacebar press to trigger jump
            // if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
            // {
                
            // }
        }
        std::cout <<  "game" << std::endl;

        // Clear screen
        SDL_SetRenderDrawColor(render, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(render);

        // SDL_SetRenderDrawColor(render, 0, 0, 0, SDL_ALPHA_OPAQUE);

        SDL_RenderCopy(render, tiles_texture, NULL, &tiles_rect);

        // Present updated screen
        SDL_RenderPresent(render);
    }

    // Cleanup
    SDL_DestroyTexture(tiles_texture);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
