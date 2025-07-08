#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

struct Tile
{
    SDL_Rect tileRect;
};

int main()
{
    SDL_Window *window = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not be initialized! SDL Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    window = SDL_CreateWindow("Ninja on Tile", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
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
    SDL_SetColorKey(RightPerson, SDL_TRUE, SDL_MapRGB(RightPerson->format, 0xff, 0xff, 0xff));

    if (!background_Space || !RightPerson)
    {
        std::cout << "Error loading images! SDL Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Create textures
    SDL_Texture *background_texture = SDL_CreateTextureFromSurface(render, background_Space);
    SDL_Texture *Right_person = SDL_CreateTextureFromSurface(render, RightPerson);

    // Free surfaces
    SDL_FreeSurface(background_Space);
    SDL_FreeSurface(RightPerson);

    // Define positions and sizes of elements
    SDL_Rect Space_rect = {0, 0, 1280, 720};
    SDL_Rect Right_Playerrect = {1280 / 2, 500, 100, 100};

    bool isJumping = false;
    bool gameIsRunning = true;
    float jumpSpeed = -20.0f;      // Initial jump speed (upward)
    float gravity = 1.0f;          // Gravity acceleration
    float verticalVelocity = 0.0f; // Velocity along y-axis
    float moveSpeed = 5.0f;        // Horizontal move speed
    int groundLevel = 500;
    float rotationAngle = 0.0f;            // Rotation angle
    float maxRotationAngle = 15.0f;        // Max rotation when moving left or right
    int direction = 1;                     // 1 for right, -1 for left (movement direction)
    SDL_RendererFlip flip = SDL_FLIP_NONE; // To handle flipping of character
    bool onTile = false;

    // Tile variables
    Tile tile;
    tile.tileRect = {480, 480, 100, 20}; // Position at x = 480, y = 480, width = 100, height = 20

    const Uint8 *state = SDL_GetKeyboardState(NULL); // Get the keyboard state

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
                verticalVelocity = jumpSpeed; // Start upward velocity
            }
        }

        // Handle continuous horizontal movement
        if (state[SDL_SCANCODE_LEFT])
        {
            Right_Playerrect.x -= moveSpeed;   // Move left
            direction = -1;                    // Set direction to left
            rotationAngle = -maxRotationAngle; // Tilt left
            flip = SDL_FLIP_HORIZONTAL;        // Flip character to face left
        }
        else if (state[SDL_SCANCODE_RIGHT])
        {
            Right_Playerrect.x += moveSpeed;  // Move right
            direction = 1;                    // Set direction to right
            rotationAngle = maxRotationAngle; // Tilt right
            flip = SDL_FLIP_NONE;             // Flip character to face right (no flip)
        }
        else
        {
            rotationAngle = 0; // Reset rotation if no key is pressed
        }

        // Horizontal screen wrapping
        if (Right_Playerrect.x <= -12)
        {
            Right_Playerrect.x = 1210;
        }
        else if (Right_Playerrect.x > 1210)
        {
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
                isJumping = false; // Stop jumping when reaching ground
                verticalVelocity = 0;
            }
        }

        // Collision with the tile
        if (Right_Playerrect.x + Right_Playerrect.w > tile.tileRect.x && Right_Playerrect.x < tile.tileRect.x + tile.tileRect.w && Right_Playerrect.y + Right_Playerrect.h >= tile.tileRect.y && Right_Playerrect.y + Right_Playerrect.h <= tile.tileRect.y + tile.tileRect.h)
        {
            // Check if the player is falling onto the tile
            // if (Right_Playerrect.y + Right_Playerrect.h >= tile.tileRect.y && Right_Playerrect.y + Right_Playerrect.h <= tile.tileRect.y + tile.tileRect.h) {
            if (verticalVelocity > 0)
            {                                                              // Only land if falling down
                Right_Playerrect.y = tile.tileRect.y - Right_Playerrect.h; // Stick player to tile's top surface
                onTile = true;                                             // Player is on the tile
                isJumping = false;                                         // Stop jumping since landed
                verticalVelocity = 0;                                      // Reset vertical velocity
                std::cout << "Tile is : " << onTile << std::endl;
            }
            // if(Right_Playerrect.x < tile.tileRect.x){
            //     onTile = false;
            // }
            // }
        }
        else
        {
            // If player moves off the tile
            onTile = false;
            if(!isJumping){Right_Playerrect.y += verticalVelocity; // Apply vertical velocity
            verticalVelocity += gravity;}
            if (Right_Playerrect.y >= 500)
            {
                Right_Playerrect.y = 500;
            }
            std::cout << "Tile is : " << onTile << std::endl;
        }

        // Clear the renderer
        SDL_RenderClear(render);
        SDL_RenderCopy(render, background_texture, NULL, &Space_rect);                              // Draw background
        SDL_RenderCopyEx(render, Right_person, NULL, &Right_Playerrect, rotationAngle, NULL, flip); // Draw player character

        // Draw the tile
        SDL_SetRenderDrawColor(render, 255, 0, 0, 255); // Red color for tile
        SDL_RenderFillRect(render, &tile.tileRect);     // Draw the tile

        // Present the rendered frame
        SDL_RenderPresent(render);
        SDL_Delay(16); // Maintain ~60 FPS
    }

    // Cleanup
    SDL_DestroyTexture(background_texture);
    SDL_DestroyTexture(Right_person);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
