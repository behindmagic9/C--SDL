#include <iostream>
#include <SDL2/SDL.h>
#include <ctime>
#include <random>


/*
    struct TileType{
        int tiletype;
        int layer;
        int visible;
        int destructable;
    };


*/

int main()
{
    srand(time(0));

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
    SDL_Surface *tiles_surface = SDL_LoadBMP("images/tile1.bmp");

    if (!tiles_surface)
    {
        std::cout << "Error loading images! SDL Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Create textures
    SDL_Texture *tiles_texture = SDL_CreateTextureFromSurface(render, tiles_surface);

    SDL_FreeSurface(tiles_surface);

    SDL_Rect number1 = {0, 0, 32, 32};
    SDL_Rect number2 = {32, 0, 32, 32};
    SDL_Rect number3 = {0, 32, 32, 32};
    SDL_Rect number4 = {32, 32, 32, 32};

    int tile[70][50];

    for (int i = 0; i < 40; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            tile[i][j] = (rand() % 4) + 1;
        }
    }
    SDL_Rect tiles_rect[40][20];
    for (int i = 0; i < 40; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            tiles_rect[i][j] = {i * 32, j * 32, 32, 32};
        }
    }
    // now render tiles

    // Define positions and sizes of elements

    // SDL_Rect tiles_rect = {0, 0, 64, 64};

    bool isGameRunning = true;

    const Uint8* keys = SDL_GetKeyboardState(NULL); // give poitner to an internal SDL array .. valid whole lifetime of application

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

        // Clear screen
        // 3698ae
        SDL_SetRenderDrawColor(render, 0x36, 0x98, 0xAE, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(render);

        static int offsetx  = 0;
        if(keys[SDL_SCANCODE_LEFT]){
            offsetx--;
            SDL_Delay(20);
        }

        if(keys[SDL_SCANCODE_RIGHT]){
            offsetx++;
            SDL_Delay(20);
        }

        if(offsetx < 0){
            offsetx=0;
        }
        if(offsetx > 39){
            offsetx=39;
        }

        static int offsety  = 0;
        if(keys[SDL_SCANCODE_UP]){
            offsety--;
            SDL_Delay(20);
        }

        if(keys[SDL_SCANCODE_DOWN]){
            offsety++;
            SDL_Delay(20);
        }

        if(offsety < 0){
            offsety=0;
        }
        if(offsety > 19){
            offsety=19;
        }        


        // SDL_SetRenderDrawColor(render, 0, 0, 0, SDL_ALPHA_OPAQUE);
        for (int i = 0; i < 70; i++)
        {
            for (int j = 0; j < 50; j++)
            {
                int x = i + offsetx;
                int y = j + offsety;
                if (x < 0 || x >= 40 || y < 0 || y >= 20)  // Ensure index stays within bounds
                  continue;

                // make swithc statrement sof 1 2 3 4 now
                switch (tile[i+offsetx][j+offsety])
                {
                case 1:
                    SDL_RenderCopy(render, tiles_texture, &number1, &tiles_rect[i][j]);
                    break;
                case 2:
                    SDL_RenderCopy(render, tiles_texture, &number2, &tiles_rect[i][j]);
                    break;
                // case 3:
                //     SDL_RenderCopy(render, tiles_texture, &number3,&tiles_rect[i][j]);
                //     break;
                case 4:
                    SDL_RenderCopy(render, tiles_texture, &number4, &tiles_rect[i][j]);
                    break;
                }
            }
        }

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
