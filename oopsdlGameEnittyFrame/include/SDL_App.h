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

    void SetRenderCallback(std::function<void(void)> func);

    void RunLoop();

    SDL_Renderer* GetRender() const;
    int GetMouseX();
    int GetMouseY();
    void StopAppLoop();
    void SetMaxFrameRate(int frameRate);
    int GetWindowWidth();
    int GetWindowHeight();

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
};

#endif



//  can do like this but as callback are for user to customise them , we have to leave this apporach and use the functor instead for callbacks
/* 

    SDLApp(char *title, int x, int y, int w, int h)
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            std::cout << "sdl not initialsed " << std::endl;
        }

        window = SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    }

    void EventCallback()
    {
        SDL_Event e;

        int mousex;
        int mousey;
        Uint32 buttons;
        buttons = SDL_GetMouseState(&mousex, &mousey);

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                std::cout << "SDL QUIT" << std::endl;
                m_isGameRunning = false;
            }
            if (e.button.button == SDL_BUTTON_LEFT)
            {
                if (rect1.IsColiding(rect))
                {
                    std::cout << "IS colidding " << std::endl;
                }
                else
                {
                    std::cout << "not colliding " << std::endl;
                }
            }
        }
    }

    void RenderCallback()
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        rect.Draw(50, 50, 100, 100);
        rect1.Draw(mousex, mousey, 100, 100);

        rect.render(renderer);
        rect1.render(renderer);

        SDL_RenderPresent(renderer);
    }

    void RunLoop()
    {
        while (m_isGameRunning)
        {
            EventCallback();
            RenderCallback();
        }
    }
    ~SDLApp()
    {
        SDL_DestroyWindow(window);
    }

*/