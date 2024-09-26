#include <SDL2/SDL.h>
#include <iostream>
#include<vector>
#include<random>
#include <cmath>
#include<ctime>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int TILE_WIDTH = 100;
const int TILE_GAP = 60;




int getRandomHeight(){
    return (rand() %200)+200;
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
        if(!texture){
            std::cout << "texture not laoded" << std::endl;
        }
        SDL_FreeSurface(car_surface);
    }

    void Update() {
        // Update jump physics
        if (isJumping) {
            y += jumpVelocity; 
            jumpVelocity += gravity; 

            rotation = jumpVelocity * 2;

            // Check if landed
            if (y >= 620) {
                y = 620; 
                isJumping = false; 
                rotation = 0;
            }
        } else {
            rotation = 0;
        }

        // Increment x position for forward movement
        x += speed;
        if (x > SCREEN_WIDTH) {
            x = 0; // Reset to start from the left again
        }

        if(y <= 1){
            y =1 ;
        }

        if (x > 320) {
            x = 320; // Reset to start from the left again
        }

        car_rect.x = static_cast<int>(x);
        car_rect.y = static_cast<int>(y);
    }

    void Jump() {
        isJumping = true;
        jumpVelocity = -10.0f; // Set initial jump velocity
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

struct Tiles{
    Tiles(SDL_Renderer* render, int x, int y , int h) : texture(nullptr), renderer(render){ 
        rect = {x, y ,TILE_WIDTH , h};
    }

    void Load(std::string path){
        SDL_Surface* tile_surface = SDL_LoadBMP(path.c_str());
        texture = SDL_CreateTextureFromSurface(renderer, tile_surface);
        if(!texture){
            std::cout << "texture not laoded" << std::endl;
        }
        SDL_FreeSurface(tile_surface);
    }

    // void SetPosition(int x, int y , int  w , int h){

    // }

    void updatePosition(int offsetX){
         rect.x -= offsetX;
          x = rect.x;
    }

    void Render(){
        SDL_RenderCopy(renderer, texture, nullptr , &rect);
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
    int bigOffset = 0;

    for(int i =0 ;i<10;i++){
        int tile_height = getRandomHeight();
        Tiles tiles(renderer, startX + i* (TILE_WIDTH + TILE_GAP),SCREEN_HEIGHT - tile_height ,tile_height);
        tiles.Load("images/tile1.bmp");
        tiles_vector_top.push_back(tiles);
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

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        car.Update();
        car.Render();

        for(auto &tiles : tiles_vector_top){
            tiles.updatePosition(2);
            tiles.Render();
        }

        if(!tiles_vector_top.empty() && tiles_vector_top.front().rect.x + TILE_WIDTH < 0){ // seeing if tiles last pixel is out of the screen so that to load it again or recycle it agian
            int height = getRandomHeight();
            Tiles recycleTile(renderer, tiles_vector_top.back().rect.x + TILE_WIDTH + TILE_GAP,SCREEN_HEIGHT - height, height);
            recycleTile.Load("images/tile1.bmp");
            tiles_vector_top.push_back(recycleTile);
            tiles_vector_top.erase(tiles_vector_top.begin());
        }


        // Present the back buffer
        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Approx. 60 FPS
    }

    SDL_DestroyTexture(car.texture);
    for (auto& tile : tiles_vector_top) {
        SDL_DestroyTexture(tile.texture);
    }

    SDL_DestroyTexture(car.texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
