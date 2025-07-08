#include <iostream>
#include <SDL2/SDL.h>

int main()
{
    SDL_Window *window = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not be initialized! SDL Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    window = SDL_CreateWindow("Ninja Animation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Renderer *render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!render)
    {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Load images
    SDL_Surface *background_Space = SDL_LoadBMP("images/backgroundSpace.bmp");
    SDL_Surface *RightPerson = SDL_LoadBMP("images/PotPlayerRight1.bmp");

    if (!background_Space || !RightPerson)
    {
        std::cout << "Error loading images! SDL Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Set transparency for images
    SDL_SetColorKey(RightPerson, SDL_TRUE, SDL_MapRGB(RightPerson->format, 0xff, 0xff, 0xff));

    // Create textures
    SDL_Texture *background_texture = SDL_CreateTextureFromSurface(render, background_Space);
    SDL_Texture *Right_person = SDL_CreateTextureFromSurface(render, RightPerson);

    SDL_FreeSurface(background_Space);
    SDL_FreeSurface(RightPerson);

    // Define positions and sizes of elements
    SDL_Rect Space_rect = {0, 0, 1280, 720};
    SDL_Rect Right_Playerrect = {1280 / 2, 500, 100, 100};

    bool isJumping = false;
    bool gameIsRunning = true;
    float jumpSpeed = -20.0f;  // Initial jump speed (upward)
    float gravity = 1.0f;      // Gravity acceleration
    float verticalVelocity = 0.0f; // Velocity along y-axis
    float moveSpeed = 5.0f;    // Horizontal move speed
    int groundLevel = 500;
    float rotationAngle = 0.0f; // Rotation angle
    float maxRotationAngle = 15.0f; // Max rotation when moving left or right

    const Uint8* state = SDL_GetKeyboardState(NULL); // Get the keyboard state

    while (gameIsRunning)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                gameIsRunning = false;
            }

            // Jump handling
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE && !isJumping)
            {
                isJumping = true;
                verticalVelocity = jumpSpeed;  // Start upward velocity
            }
        }

        // Handle continuous horizontal movement
        if (state[SDL_SCANCODE_LEFT])
        {
            Right_Playerrect.x -= moveSpeed;  // Move left
            rotationAngle = -maxRotationAngle;  // Tilt left
        }
        else if (state[SDL_SCANCODE_RIGHT])
        {
            Right_Playerrect.x += moveSpeed;   // Move right
            rotationAngle = maxRotationAngle;  // Tilt right
        }
        else
        {
            rotationAngle = 0;  // Reset rotation if no key is pressed
        }

        // Apply gravity and handle jumping
        if (isJumping)
        {
            // Vertical movement
            Right_Playerrect.y += verticalVelocity; // Apply vertical velocity
            verticalVelocity += gravity;            // Apply gravity

            // Boundaries for horizontal movement
            if (Right_Playerrect.x <= 0)
            {
                Right_Playerrect.x = 0;
            }
            else if (Right_Playerrect.x >= 1200)
            {
                Right_Playerrect.x = 1200;
            }

            // Check if the player lands back on the ground
            if (Right_Playerrect.y >= groundLevel)
            {
                Right_Playerrect.y = groundLevel;
                isJumping = false;        // Stop jumping
                verticalVelocity = 0;     // Reset vertical velocity
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(render, 0x66, 0x66, 0x66, 0xFF);
        SDL_RenderClear(render);

        // Render background elements
        SDL_RenderCopy(render, background_texture, NULL, &Space_rect);

        // Render player with rotation using SDL_RenderCopyEx
        SDL_RenderCopyEx(render, Right_person, NULL, &Right_Playerrect, rotationAngle, NULL, SDL_FLIP_NONE);

        // Present updated screen
        SDL_RenderPresent(render);

        // Limit frame rate
        SDL_Delay(16);
    }

    // Cleanup
    SDL_DestroyTexture(background_texture);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
