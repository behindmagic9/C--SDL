#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

struct Fire {
    SDL_Rect fireRect;
    float fireSpeed;
    bool active;
    int direction; // 1 for right, -1 for left
};

int main()
{
    SDL_Window *window = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not be initialized! SDL Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    window = SDL_CreateWindow("Ninja Animation with Fire", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
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
    SDL_Surface *RightPerson = SDL_LoadBMP("images/PotPlayerRight.bmp");
    SDL_SetColorKey(RightPerson, SDL_TRUE, SDL_MapRGB(RightPerson->format, 0xff,0xff,0xff));
    SDL_Surface *fireSurface = SDL_LoadBMP("images/Fire.bmp");

    if (!background_Space || !RightPerson || !fireSurface)
    {
        std::cout << "Error loading images! SDL Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Set transparency for fire
    SDL_SetColorKey(fireSurface, SDL_TRUE, SDL_MapRGB(fireSurface->format, 0xff, 0xff, 0xff));

    // Create textures
    SDL_Texture *background_texture = SDL_CreateTextureFromSurface(render, background_Space);
    SDL_Texture *Right_person = SDL_CreateTextureFromSurface(render, RightPerson);
    SDL_Texture *fire_texture = SDL_CreateTextureFromSurface(render, fireSurface);

    // Free surfaces
    SDL_FreeSurface(background_Space);
    SDL_FreeSurface(RightPerson);
    SDL_FreeSurface(fireSurface);

    // Define positions and sizes of elements
    SDL_Rect Space_rect = {0, 0, 1280, 720};
    SDL_Rect Right_Playerrect = {1280 / 2, 500, 100, 100};

    bool isJumping = false;
    bool gameIsRunning = true;
    float jumpSpeed = -20.0f;   // Initial jump speed (upward)
    float gravity = 1.0f;       // Gravity acceleration
    float verticalVelocity = 0.0f; // Velocity along y-axis
    float moveSpeed = 5.0f;     // Horizontal move speed
    int groundLevel = 500;
    float rotationAngle = 0.0f; // Rotation angle
    float maxRotationAngle = 15.0f; // Max rotation when moving left or right
    int direction = 1;  // 1 for right, -1 for left (movement direction)
    SDL_RendererFlip flip = SDL_FLIP_NONE;  // To handle flipping of character

    // Fire variables
    std::vector<Fire> fires;    // List of active fireballs
    float fireSpeed = 10.0f;    // Speed at which fireballs travel

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

            // Fire handling
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_f)
            {
                // Create a fireball starting from the center of the player
                Fire newFire;
                newFire.fireRect.x = Right_Playerrect.x + (Right_Playerrect.w / 2);
                newFire.fireRect.y = Right_Playerrect.y + (Right_Playerrect.h / 2);
                newFire.fireRect.w = 40;  // Width of fireball
                newFire.fireRect.h = 20;  // Height of fireball
                newFire.fireSpeed = fireSpeed;
                newFire.active = true;
                newFire.direction = direction;  // Fire in the current direction

                // Add the fireball to the list of fires
                fires.push_back(newFire);
            }
        }

        // Handle continuous horizontal movement
        if (state[SDL_SCANCODE_LEFT])
        {
            Right_Playerrect.x -= moveSpeed;  // Move left
            direction = -1;  // Set direction to left
            rotationAngle = -maxRotationAngle;  // Tilt left
            flip = SDL_FLIP_HORIZONTAL;  // Flip character to face left
        }
        else if (state[SDL_SCANCODE_RIGHT])
        {
            Right_Playerrect.x += moveSpeed;   // Move right
            direction = 1;  // Set direction to right
            rotationAngle = maxRotationAngle;  // Tilt right
            flip = SDL_FLIP_NONE;  // Flip character to face right (no flip)
        }
        else
        {
            rotationAngle = 0;  // Reset rotation if no key is pressed
        }

        if(Right_Playerrect.x <= -12){
            Right_Playerrect.x = 1210;
        }
        else if(Right_Playerrect.x > 1210){
            Right_Playerrect.x = -8;
        }

        // Apply gravity and handle jumping
        if (isJumping)
        {
            Right_Playerrect.y += verticalVelocity; // Apply vertical velocity
            verticalVelocity += gravity;            // Apply gravity

            if (Right_Playerrect.y >= groundLevel)
            {
                Right_Playerrect.y = groundLevel;
                isJumping = false;  // Stop jumping
                verticalVelocity = 0;
            }
        }

        // Update fireball positions
        for (auto& fire : fires)
        {
            if (fire.active)
            {
                fire.fireRect.x += fire.fireSpeed * fire.direction;  // Move fireball horizontally based on direction

                // Deactivate fireball if it goes off-screen
                if (fire.fireRect.x > 1280 || fire.fireRect.x < 0)
                {
                    fire.active = false;
                }
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(render, 0x66, 0x66, 0x66, 0xFF);
        SDL_RenderClear(render);

        // Render background elements
        SDL_RenderCopy(render, background_texture, NULL, &Space_rect);

        // Render player with rotation using SDL_RenderCopyEx, including flip
        SDL_RenderCopyEx(render, Right_person, NULL, &Right_Playerrect, rotationAngle, NULL, flip);

        // Render fireballs
        for (auto& fire : fires)
        {
            if (fire.active)
            {
                SDL_RenderCopy(render, fire_texture, NULL, &fire.fireRect);
            }
        }

        // Present updated screen
        SDL_RenderPresent(render);

        // Limit frame rate
        SDL_Delay(16);
    }

    // Cleanup
    SDL_DestroyTexture(background_texture);
    SDL_DestroyTexture(fire_texture);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
