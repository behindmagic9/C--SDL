#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <ctime>
#include <random>

const int TILE_WIDTH = 100;
const int TILE_GAP = 60;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int PARALLAX_SCROLL_SPEED = 2;

struct Tile
{
    int x;
    int height;
    SDL_Rect rect;

    Tile(int startX, int randomHeight) : x(startX), height(randomHeight)
    {
        rect = {x, SCREEN_HEIGHT - height, TILE_WIDTH, height};
    }

    void updatePosition(int offsetX)
    {
        x -= offsetX;
        rect.x = x;
    }
};

struct Car
{
    int x;
    int y;
    SDL_Rect rect;
    Car(int x, int y, int width, int height)
    {
    }
};

int getRandomHeight()
{
    return (rand() % 200) + 200; // Height between 50 and 150
}

int main()
{
    srand(static_cast<unsigned>(time(0)));

    SDL_Window *window = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not be initialized! SDL Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    window = SDL_CreateWindow("Tile Scroller with Vector", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Load textures
    SDL_Surface *tiles_surface = SDL_LoadBMP("images/tile.bmp");
    SDL_Surface *bg_surface = SDL_LoadBMP("images/forest(1).bmp"); // Parallax background
    SDL_Surface *car_surface = SDL_LoadBMP("images/car.bmp");
    SDL_SetColorKey(car_surface, SDL_TRUE, SDL_MapRGB(car_surface->format, 0x00, 0x00, 0x00));

    if (!tiles_surface || !bg_surface || !car_surface)
    {
        std::cout << "Error loading images! SDL Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_Texture *tiles_texture = SDL_CreateTextureFromSurface(renderer, tiles_surface);
    SDL_Texture *bg_texture = SDL_CreateTextureFromSurface(renderer, bg_surface);
    SDL_Texture *car_texture = SDL_CreateTextureFromSurface(renderer, car_surface);
    SDL_FreeSurface(tiles_surface);
    SDL_FreeSurface(car_surface);
    SDL_FreeSurface(bg_surface);

    SDL_Rect car_rect = {100, 100, 100, 100};

    std::vector<Tile> tiles;
    int startX = 340;
    int bg_offset = 0; // Background parallax scrolling offset

    // Initial tile generation
    for (int i = 0; i < 10; ++i)
    {
        tiles.emplace_back(startX + i * (TILE_WIDTH + TILE_GAP), getRandomHeight());
    }

    bool isGameRunning = true;
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    static int offsetX = 0;
    int scrollSpeed = 1; // Base scrolling speed

    while (isGameRunning)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isGameRunning = false;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
            {
                car_rect.y -= 50;
                car_rect.x += 2;
            }
        }

        // Handle scrolling
        // if (keys[SDL_SCANCODE_LEFT]) {
        // offsetX = -scrollSpeed;  // Scroll to the right
        // } else if (keys[SDL_SCANCODE_RIGHT]) {
        offsetX = scrollSpeed; // Scroll to the left
        // } else {
        // offsetX = 0;
        // }

        car_rect.x += 1;
        car_rect.y += 2;

        if (car_rect.y > 620)
        {
            car_rect.y = 620;
            std::cout << car_rect.y << std::endl;
        }

        if (car_rect.y <= 0)
        {
            car_rect.y = 0;
        }

        // Update tile positions
        // for (auto &tile : tiles)
        // {
        //     tile.updatePosition(offsetX);
        // }

        const float TILE_AMPLITUDE = 20.0f; // Maximum height change
        const float TILE_FREQUENCY = 2.0f;  // Speed of the wave

        // Inside your game loop
        for (auto &tile : tiles)
        {
            float time = SDL_GetTicks() / 1000.0f;                                                            // Get time in seconds
            tile.rect.y = SCREEN_HEIGHT - tile.height + TILE_AMPLITUDE * sin(TILE_FREQUENCY * time + tile.x); // Move tile up and down
        }

        // Remove and reposition tiles
        if (!tiles.empty() && tiles.front().x + TILE_WIDTH < 0)
        {
            Tile recycledTile = tiles.front();                       // Recycle the first tile
            recycledTile.x = tiles.back().x + TILE_WIDTH + TILE_GAP; // Reposition at the right
            recycledTile.height = getRandomHeight();                 // Give it a new height
            recycledTile.rect = {recycledTile.x, SCREEN_HEIGHT - recycledTile.height, TILE_WIDTH, recycledTile.height};
            tiles.push_back(recycledTile); // Add the recycled tile to the back
            tiles.erase(tiles.begin());    // Remove the tile from the front
        }

        // Handle parallax scrolling for background
        bg_offset -= PARALLAX_SCROLL_SPEED;
        if (bg_offset <= -SCREEN_WIDTH)
        {
            bg_offset = 0; // Reset background scroll once fully off-screen
            
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0x36, 0x98, 0xAE, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // Render parallax background (scrolls slower than tiles)
        SDL_Rect bg_rect = {bg_offset, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderCopy(renderer, bg_texture, nullptr, &bg_rect);

        SDL_Rect bg_rect2 = {bg_offset + SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderCopy(renderer, bg_texture, nullptr, &bg_rect2);

        // Render tiles
        for (auto &tile : tiles)
        {
            SDL_RenderCopy(renderer, tiles_texture, nullptr, &tile.rect);
        }
        SDL_RenderCopy(renderer, car_texture, nullptr, &car_rect);

        // Present updated screen
        SDL_RenderPresent(renderer);

        // Delay to control frame rate (for smoother rendering)
        SDL_Delay(16); // Approximately 60 FPS
    }

    // Cleanup
    SDL_DestroyTexture(tiles_texture);
    SDL_DestroyTexture(bg_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
