#include <iostream>
#include <SDL2/SDL.h>

void SetPixel(SDL_Surface* surface , int x, int y , uint8_t r, uint8_t g, uint8_t b ){
    SDL_LockSurface(surface);
    uint8_t* pixelArray = (uint8_t*)surface->pixels; // casting the surface* to the uint8_t* to make that point to the pixels fp the surface ,
    // which be contain the pixel array as the surface as the rbg color so in array of type uint8_t
    // tahts why amade the array of pointer of uint8_t type

    // now customizing the surface 
    // pixel - >length of the row of the pixel in bytes
    // to locate a pixel we have to do like -> y*pitch + x
    pixelArray[y*surface->pitch + x*surface->format->BytesPerPixel + 0 ] = g;
    pixelArray[y*surface->pitch + x*surface->format->BytesPerPixel + 1] = b;
    pixelArray[y*surface->pitch + x*surface->format->BytesPerPixel + 2] = r;
    SDL_UnlockSurface(surface);
}

int main()
{

    SDL_Window *window = nullptr;
    SDL_Surface *screen;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL not initlaised " << std::endl;
    }

    window = SDL_CreateWindow("C++ window", 20, 20, 640, 480, SDL_WINDOW_SHOWN);

    screen = SDL_GetWindowSurface(window);

    bool isGameRunning = true;
    while (isGameRunning)
    {
        SDL_Event e;
        int x, y;
        Uint32 buttons;
        buttons = SDL_GetMouseState(&x, &y);

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                isGameRunning = false;
            }
            if (e.button.button == SDL_BUTTON_LEFT)
            {
                std::cout << "Left mouse was presses at x: " << x << " , y : " << y << std::endl;
                SetPixel(screen , x, y , 255 , 0 ,0);
            }
            if (e.button.button == SDL_BUTTON_RIGHT)
            {
                std::cout << "right mouse was presses at x: " << x << " , y : " << y << std::endl;
                SetPixel(screen , x, y , 0 , 255 ,0);
            }


        }

        SDL_UpdateWindowSurface(window);
    }

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}