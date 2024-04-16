#ifndef SDL_APPH_HPP
#define SDL_APP_HPP
// #include <iostream>
#include<functional>
#include <SDL2/SDL.h>

class SDLApp
{
public:
    SDLApp(const char *title, int x, int y, int w, int h);

    void SetEventCallback(std::function<void(void)> func);

    void SetUpdateCallback(std::function<void(void)> func);

    void SetRenderCallback(std::function<void(void)> func);

    void RunLoop();

    void SetMaxFrameRate(int frameRate);
    SDL_Renderer* GetRender() const;

    int GetMouseX();
    int GetMouseY();
    int GetWindowWidth();
    int GetWindowHeight();

    void StopAppLoop();
    
    ~SDLApp();

private:
    SDL_Window *window = nullptr;
    SDL_Renderer *m_renderer = nullptr;
    bool m_isGameRunning = true;
    int MouseX;
    int MouseY;
    int max_framerate  = 0; 
    int Windowwidth = 0;
    int Windowheight = 0;
    std::function<void(void)> m_RenderCallback;
    std::function<void(void)> m_EventCallback;
    std::function<void(void)> m_UpdateCallback;
};

#endif

