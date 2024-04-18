#include "../include/SDL_App.h"
#include <iostream>

SDLApp::SDLApp(Uint32 subsystem , const char *title, int x, int y, int w, int h)
{
    if (SDL_Init(subsystem) < 0)
    {
        std::cout << "sdl not initialsed " << std::endl;
    }
    Windowwidth = w;
    Windowheight =h;
    max_framerate = 90;
    window = SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_SHOWN);
    m_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void SDLApp::SetEventCallback(std::function<void(void)> func)
{
    m_EventCallback = func;
}

void SDLApp::SetUpdateCallback(std::function<void(void)>func){
    m_UpdateCallback = func;
}

void SDLApp::SetRenderCallback(std::function<void(void)> func)
{
    m_RenderCallback = func;
}

void SDLApp::RunLoop()
{
    while (m_isGameRunning)
    {
        Uint32 startTime = SDL_GetTicks();
        Uint32 buttons;
        buttons = SDL_GetMouseState(&MouseX, &MouseY);

        m_EventCallback();

        m_UpdateCallback();

        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(m_renderer);

        SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        m_RenderCallback();

        SDL_RenderPresent(m_renderer);
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        if(elapsedTime < max_framerate){
            SDL_Delay(max_framerate - elapsedTime);
        }
        // SDL_Delay(100)s;
    }
}

void SDLApp::SetMaxFrameRate(int FrameRate){
    max_framerate = FrameRate;
}

int SDLApp::GetWindowWidth(){
    return Windowwidth;
}

int SDLApp::GetWindowHeight(){
    return Windowheight;
}

SDL_Renderer *SDLApp::GetRender() const
{
    return m_renderer;
}
int SDLApp::GetMouseX()
{
    return MouseX;
}
int SDLApp::GetMouseY()
{
    return MouseY;
}
void SDLApp::StopAppLoop()
{
    m_isGameRunning = false;
}

SDLApp::~SDLApp()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}
