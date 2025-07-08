// g++ main1.cpp ./src/glad.c -I./include/ -o a.out -lSDL2 -ldl

#include <SDL2/SDL.h>
#include "include/glad/glad.h"
#include <iostream>

int gScreenHight = 480;
int gScreenWidth = 640;

SDL_Window *gGraphicsApplicationWindow = nullptr;
SDL_GLContext gOpenGlContext = nullptr;

bool gQuit = false;

void getOpenGLVersion()
{
    std::cout << "Vendor : " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "render : " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Shading language : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

void InitialiseProgram()
{

// initliase sdl
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL2 could not be initialise video subsystem" << std::endl;
        exit(1);
    }

// set up some opengl attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 6);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); // support latest ucntions
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); // 24 bytes to get tprecison when dicrimainate in objec tor overlapiing

// created our window
    gGraphicsApplicationWindow = SDL_CreateWindow("opengl ", 0, 0, gScreenWidth, gScreenHight, SDL_WINDOW_OPENGL);

    if (gGraphicsApplicationWindow == nullptr)
    {
        std::cout << "SDL Window was not able to be created " << std::endl;
        exit(1);
    }

// opengl context
    gOpenGlContext = SDL_GL_CreateContext(gGraphicsApplicationWindow);
    if (gOpenGlContext == nullptr)
    {
        std::cout << "Opengl Context not avialable\n";
        exit(1);
    }

    // include the glad library
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
    { // loading up a bunch of function pointers
        std::cout << "glad was not initialised" << std::endl;
        exit(1);
    }

    getOpenGLVersion();
}

void CleanUp()
{
    SDL_DestroyWindow(gGraphicsApplicationWindow);
    SDL_Quit();
}

void Input()
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            std::cout << "GoodBye" << std::endl;
            gQuit = true;
        }
    }
}

void PreDraw()
{
}

void Draw()
{
}

void MainLoop()
{
    while (!gQuit)
    {

        Input();

        PreDraw();

        Draw();

        // update the screen
        // the way double buffering work is when we drawing a graphic screen .. we draw to back as soon as we done .. we sent that information to the buffer .. and drawing somehting else on the back while fornt is displayed to user ..
        SDL_GL_SwapWindow(gGraphicsApplicationWindow);
    }
}

int main()
{
    InitialiseProgram();

    MainLoop();

    CleanUp();
}