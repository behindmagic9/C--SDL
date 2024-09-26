#include <iostream>
#include <SDL2/SDL.h>
#include <ctime>
#include <random>

const int TILE_WIDTH = 100;  // Width of each tile
const int TILE_GAP = 70;    // Gap between tiles
const int NUM_TILES = 40;   // Number of tiles

int getRandomHeight() {
    return (rand() % 250) + 50; // Random height between 50 and 100
}

int main() {
    srand(static_cast<unsigned>(time(0)));  // Seed for random heights

    SDL_Window *window = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not be initialized! SDL Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    window = SDL_CreateWindow("Tile Scroller", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Load textures (assuming "images/tile.bmp" exists in your project folder)
    SDL_Surface *tiles_surface = SDL_LoadBMP("images/tile.bmp");
    SDL_Surface *background_surface = SDL_LoadBMP("images/forest(1).bmp");
    // SDL_Surface 
    if (!tiles_surface || !background_surface) {
        std::cout << "Error loading images! SDL Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // if()

    SDL_Texture *tiles_texture = SDL_CreateTextureFromSurface(renderer, tiles_surface);
    SDL_Texture *backgrou_texture = SDL_CreateTextureFromSurface(renderer, background_surface);
    SDL_Rect background_rect = {0,0,1280,720};

    SDL_FreeSurface(tiles_surface);
    SDL_FreeSurface(background_surface);

    int tileHeights[NUM_TILES];
    for (int i = 0; i < NUM_TILES; i++) {
        tileHeights[i] = getRandomHeight();  // Random height for each tile
    }

    int startX = 340;  // Starting position for the first tile

    bool isGameRunning = true;
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    int offsetX = 0;
    int lower_height = 0;

    while (isGameRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isGameRunning = false;
            }
        }

        // Handle scrolling
        if (keys[SDL_SCANCODE_LEFT]) {
            offsetX -= 5;  // Scroll to the left
        }
        if (keys[SDL_SCANCODE_RIGHT]) {
            offsetX += 5;  // Scroll to the right
        }

        // if(offsetX >= 5){
        //     offsetX = 5;
        // }

        if(offsetX < 0){
            offsetX = 0;
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0x36, 0x98, 0xAE, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // Render tiles

        // for lower

        SDL_RenderCopy(renderer,backgrou_texture,NULL, &background_rect);
        for (int i = 0; i < NUM_TILES; i++) {
            int xPosition = startX + i * (TILE_WIDTH + TILE_GAP) - offsetX;
            int yPosition = 720 - tileHeights[i];  // Position the tiles from the bottom of the screen
            SDL_Rect tileRect = { xPosition, yPosition, TILE_WIDTH, tileHeights[i] };

            SDL_RenderCopy(renderer, tiles_texture, nullptr, &tileRect);  // Render tile
        }

// for upper
        for (int i = 0; i < NUM_TILES; i++) {
            int xPosition = startX + i * (TILE_WIDTH + TILE_GAP) - offsetX;
            int yPosition = 0;  // Position the tiles from the bottom of the screen
            // if(tileHeights[i] < 50){
            //     lower_height = 140;
            // }else{
            //     lower_height = 40;
            // }
            SDL_Rect tileRect = { xPosition, yPosition, TILE_WIDTH, tileHeights[i] };

            SDL_RenderCopy(renderer, tiles_texture, nullptr, &tileRect);  // Render tile
        }

        // Present updated screen
        SDL_RenderPresent(renderer);
    }

    // SDL_Rect background_rect = {0,0,640,480};

    // if(background_rect.x > 639){
    //     background_rect < 0;
    // }


    // Cleanup
    SDL_DestroyTexture(tiles_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
