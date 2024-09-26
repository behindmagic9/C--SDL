#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int TILE_WIDTH = 100;
const int TILE_GAP = 60;
const int PASSAGE_GAP = 200;

int getRandomGapPosition() {
    return (rand() % 200) + 100;
}

struct Car {
    Car(SDL_Renderer* render) 
        : renderer(render), time(0.0f), amplitude(100.0f), frequency(0.1f), speed(2.0f), 
          x(0), y(SCREEN_HEIGHT / 2), isJumping(false), jumpVelocity(0.0f), 
          gravity(0.5f), rotation(0.0f), texture(nullptr) {
        car_rect = {static_cast<int>(x), static_cast<int>(y), 100, 100}; // Set default size
    }

    void Load(const std::string& path) {
        SDL_Surface* car_surface = SDL_LoadBMP(path.c_str());
        SDL_SetColorKey(car_surface, SDL_TRUE, SDL_MapRGB(car_surface->format, 0x00, 0x00, 0x00));
        texture = SDL_CreateTextureFromSurface(renderer, car_surface);
        if(!texture) {
            std::cout << "Texture not loaded" << std::endl;
        }
        SDL_FreeSurface(car_surface);
    }

    void Update() {
        if (isJumping) {
            y += jumpVelocity; 
            jumpVelocity += gravity; 
            rotation = jumpVelocity * 2;

            if (y >= 620) { // Landed
                y = 620; 
                isJumping = false; 
                rotation = 0;
            }
        } else {
            rotation = 0;
        }

        if (y <= 1) {
            y = 1;
        }

        car_rect.x = static_cast<int>(x);
        car_rect.y = static_cast<int>(y);
    }

    void Jump() {
        isJumping = true;
        jumpVelocity = -10.0f; 
    }

    void Render() {
        SDL_RenderCopyEx(renderer, texture, nullptr, &car_rect, rotation, nullptr, SDL_FLIP_NONE);
    }

    SDL_Rect car_rect;
    SDL_Renderer* renderer;
    SDL_Texture* texture;

private:
    float time;
    const float amplitude;
    const float frequency;
    const float speed;
    float x;
    float y;
    bool isJumping;
    float jumpVelocity;
    const float gravity;
    float rotation;
};

struct Tiles {
    Tiles(SDL_Renderer* render, int x, int y, int h) : texture(nullptr), renderer(render) { 
        rect = {x, y, TILE_WIDTH, h};
    }

    void Load(std::string path) {
        SDL_Surface* tile_surface = SDL_LoadBMP(path.c_str());
        texture = SDL_CreateTextureFromSurface(renderer, tile_surface);
        if(!texture) {
            std::cout << "Texture not loaded" << std::endl;
        }
        SDL_FreeSurface(tile_surface);
    }

    void updatePosition(int offsetX) {
        rect.x -= offsetX;
        x = rect.x;
    }

    void Render() {
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
    }

    int x;
    int height;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect rect;
};

int main(int argc, char *argv[]) {

    srand(static_cast<unsigned>(time(0)));

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Wave Movement", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Car car(renderer);
    car.Load("images/car.bmp");

    std::vector<Tiles> tiles_vector_top;
    std::vector<Tiles> tiles_vector_bottom;

    int startX = 340;

    for (int i = 0; i < 10; i++) {
        int gapY = getRandomGapPosition();
        int bottom_tile_height = SCREEN_HEIGHT - gapY - PASSAGE_GAP;
        int top_tile_height = gapY;

        // bottom tiles
        Tiles bottom_tile(renderer, startX + i * (TILE_WIDTH + TILE_GAP), SCREEN_HEIGHT - bottom_tile_height, bottom_tile_height);
        bottom_tile.Load("images/tile1.bmp");
        tiles_vector_bottom.push_back(bottom_tile); // Fix: Add to bottom tiles vector

        // top tiles
        Tiles top_tile(renderer, startX + i * (TILE_WIDTH + TILE_GAP), 0, top_tile_height);
        top_tile.Load("images/tile1.bmp");
        tiles_vector_top.push_back(top_tile);
    }

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
                car.Jump();
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        car.Update();
        car.Render();

        // Render and update bottom tiles
        for (auto &tiles : tiles_vector_bottom) {
            tiles.updatePosition(2);
            tiles.Render();
        }

        // Render and update top tiles
        for (auto &tiles : tiles_vector_top) {
            tiles.updatePosition(2);
            tiles.Render();
        }

        // Recycling logic
        if (!tiles_vector_top.empty() && tiles_vector_bottom.front().rect.x + TILE_WIDTH < 0) {
            int gapY = getRandomGapPosition();
            int bottom_tile_height = SCREEN_HEIGHT - gapY - PASSAGE_GAP;
            int top_tile_height = gapY;

            // recycle bottom tiles
            Tiles recycleTile(renderer, tiles_vector_bottom.back().rect.x + TILE_WIDTH + TILE_GAP, SCREEN_HEIGHT - bottom_tile_height, bottom_tile_height);
            recycleTile.Load("images/tile1.bmp");
            tiles_vector_bottom.push_back(recycleTile);
            tiles_vector_bottom.erase(tiles_vector_bottom.begin());

            // recycle top tiles
            Tiles top_recycle_tile(renderer, tiles_vector_top.back().rect.x + TILE_WIDTH + TILE_GAP, 0, top_tile_height);
            top_recycle_tile.Load("images/tile1.bmp");
            tiles_vector_top.push_back(top_recycle_tile);
            tiles_vector_top.erase(tiles_vector_top.begin());
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Approx. 60 FPS
    }

    // Cleanup
    SDL_DestroyTexture(car.texture);
    for (auto &tile : tiles_vector_top) {
        SDL_DestroyTexture(tile.texture);
    }
    for (auto &tile : tiles_vector_bottom) {
        SDL_DestroyTexture(tile.texture);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}



// gameover screen 

// starting screen

// then work on the left over textures
