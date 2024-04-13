#include<iostream>
#include<SDL2/SDL.h>


int main(){

    SDL_Window* window = nullptr;

    SDL_Surface* screen;


    // if(SDL_INIT_VIDEO < 0){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){ 
        std::cout << "SDL could not be initliazed " << std::endl;
        SDL_GetError();
    }else{
        std::cout << "SDl video system is ready " << std::endl;
    }

    window = SDL_CreateWindow(
        "C++ screen" , 0 , 2500 , 640 , 480 , SDL_WINDOW_SHOWN
    );

    screen = SDL_GetWindowSurface(window);

    SDL_Surface* image;
    image = SDL_LoadBMP("../images/load.bmp");
    if(image == nullptr){
        std::cout << "no image was found" << std::endl;
    }
    SDL_BlitSurface(image,NULL,screen, NULL);
    SDL_FreeSurface(image);
    SDL_UpdateWindowSurface(window);



    bool isGameRunning = true;

    while(isGameRunning){
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                isGameRunning = false;
            }
            if(event.type == SDL_MOUSEMOTION){
                std::cout << "Mouse is moving " << std::endl;
            }
            if(event.type == SDL_KEYDOWN){
                std::cout << "a key is been pressed " << std::endl;
                if(event.key.keysym.sym == SDLK_0){
                    std::cout << "0 key is been pressed " << std::endl;
                }else{
                    std::cout << "0 key is not  pressed " << std::endl;
                }
            }

            const Uint8* state = SDL_GetKeyboardState(NULL);
            if(state[SDL_SCANCODE_RIGHT]){
                std::cout << "right arrow key is pressed\n";
            }

        }
    }

// before destroying the window no means of adding it before unless hown the pause behiviour
    // SDL_Delay(3000);
    // SDL_Delay(3000);
    // SDL_Delay(3000);

    SDL_DestroyWindow(window);

// this be help in perfectly destroying the resources/subsystems before the exit
    // SDL_Delay(3000);

    SDL_Quit();

    return 0 ;
}