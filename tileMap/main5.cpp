#include <SDL2/SDL.h>
#include<iostream>
#include <cmath>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Wave Movement", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;
    SDL_Event event;

    float time = 0.0f; // Time variable to control the wave movement
    const float amplitude = 100.0f; // Height of the wave
    const float frequency = 0.1; // Frequency of the wave
    const float speed = 2.0f; // Speed of forward movement

    float x = 0; // X position starting from the left side of the screen

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);


        // A * (B * sin(x-C)) + D
        // A is amplitutde (tallness)
        // B is number of waves or frequency
        // C is x's positojn wave sift
        // D is shift the wave's Y position

        // Calculate the position of the object using the sine function
        float y = SCREEN_HEIGHT / 2 + amplitude * sin(frequency * time); // Y position
        x += speed; // Increment x position for forward movement

        // Draw the object (a simple circle)
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        for (int w = 0; w < 10; w++) {
            for (int h = 0; h < 10; h++) {
                int dx = 5 - w; // Offset for circle drawing
                int dy = 5 - h;
                if (dx * dx + dy * dy <= 25) {
                    SDL_RenderDrawPoint(renderer, static_cast<int>(x) + dx, static_cast<int>(y) + dy);
                }
            }
        }

        // Update the time variable
        time += 0.7f; // Increment time for the next frame

        // Reset x position to create a looping effect when it goes off-screen
        if (x > SCREEN_WIDTH) {
            x = 0; // Reset to start from the left again
        }

        // Present the back buffer
        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Approx. 60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
