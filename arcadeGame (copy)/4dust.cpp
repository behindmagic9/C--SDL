#include <iostream>
#include <vector>
#include <algorithm>
#include <SDL2/SDL.h>

struct Fire
{
    SDL_Rect fireRect;
    float fireSpeed;
    bool active;
    int direction; // 1 for right, -1 for left
};

struct Dust
{
    SDL_Rect dustRect;
    float fadeSpeed; // Speed of fading effect
    int lifetime;    // How long the dust lasts
    bool active;     // Whether the dust is active
};

struct Tile
{
    SDL_Rect tile_rect;

    bool isColliding(const SDL_Rect &playerRect)
    {
        return playerRect.x + playerRect.w > tile_rect.x &&
               playerRect.x < tile_rect.x + tile_rect.w &&
               playerRect.y + playerRect.h >= tile_rect.y &&
               playerRect.y + playerRect.h <= tile_rect.y + tile_rect.h;
    }
};

int main()
{
    SDL_Window *window = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not be initialized! SDL Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    window = SDL_CreateWindow("Ninja Animation with Fire and Dust", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
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
    SDL_Surface *RightPerson = SDL_LoadBMP("images/PotPlayerRight3.bmp");
    SDL_SetColorKey(RightPerson, SDL_TRUE, SDL_MapRGB(RightPerson->format, 0xff, 0xff, 0xff));
    SDL_Surface *fireSurface = SDL_LoadBMP("images/Fire.bmp");
    SDL_Surface *dustSurface = SDL_LoadBMP("images/dust1.bmp"); // Load dust texture

    // loading the enemy
    SDL_Surface *enemy_surface = SDL_LoadBMP("images/Enemy.bmp");


    // loading tile surface
    SDL_Surface* tile_surface = SDL_LoadBMP("images/tile.bmp");

    if (!background_Space || !RightPerson || !fireSurface || !dustSurface || !tile_surface || !enemy_surface)
    {
        std::cout << "Error loading images! SDL Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Set transparency for fire and dust
    SDL_SetColorKey(fireSurface, SDL_TRUE, SDL_MapRGB(fireSurface->format, 0xff, 0xff, 0xff));
    // SDL_SetColorKey(dustSurface, SDL_TRUE, SDL_MapRGB(dustSurface->format, 0xff, 0xff, 0xff));

    // Create textures
    SDL_Texture *background_texture = SDL_CreateTextureFromSurface(render, background_Space);
    SDL_Texture *Right_person = SDL_CreateTextureFromSurface(render, RightPerson);
    SDL_Texture *fire_texture = SDL_CreateTextureFromSurface(render, fireSurface);
    SDL_Texture *dust_texture = SDL_CreateTextureFromSurface(render, dustSurface);
    SDL_Texture* enemy_texture = SDL_CreateTextureFromSurface(render,enemy_surface );

    // tile texture
    SDL_Texture* tile_texture = SDL_CreateTextureFromSurface(render, tile_surface);
    
    // Free surfaces
    SDL_FreeSurface(background_Space);
    SDL_FreeSurface(RightPerson);
    SDL_FreeSurface(fireSurface);
    SDL_FreeSurface(dustSurface);
    SDL_FreeSurface(enemy_surface);

    SDL_Rect enemy_rect = {500,500,80,80};;

    SDL_FreeSurface(tile_surface);

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

    // Fire and Dust variables
    std::vector<Fire> fires; // List of active fireballs
    float fireSpeed = 10.0f; // Speed at which fireballs travel

    std::vector<Dust> dustParticles; // List of active dust particles
    const int dustLifetime = 30;     // Lifetime of dust particles

    const Uint8 *state = SDL_GetKeyboardState(NULL); // Get the keyboard state
    bool isLanding = false;
    int landingTimer = 0;
    const int landingDuration = 10;
    float scaleFactor = 1.0f;
    bool onTile = false;

    std::vector<Tile> tiles;

    Tile center_bottom_tile;
    center_bottom_tile.tile_rect = {480, 450, 200, 40};
    tiles.push_back(center_bottom_tile);

    Tile upper_left_tile;
    upper_left_tile.tile_rect = {0, 200, 200, 40};
    tiles.push_back(upper_left_tile);

    Tile upper_right_tile;
    upper_right_tile.tile_rect = {1110, 200, 200, 40};
    tiles.push_back(upper_right_tile);

    Tile middle_right_tile;
    middle_right_tile.tile_rect = {0, 400, 200, 40};
    tiles.push_back(middle_right_tile);

    Tile middle_left_tile;
    middle_left_tile.tile_rect = {1110, 400, 200, 40};
    tiles.push_back(middle_left_tile);

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

            // Fire handling
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_f)
            {
                // Create a fireball starting from the center of the player
                Fire newFire;
                if (direction < 0)
                {
                    newFire.fireRect.x = Right_Playerrect.x - 25;
                }
                else
                {
                    newFire.fireRect.x = Right_Playerrect.x + (Right_Playerrect.w) - 13;
                }

                // newFire.fireRect.x = Right_Playerrect.x + (Right_Playerrect.w ) - 20;
                newFire.fireRect.y = Right_Playerrect.y + (Right_Playerrect.h / 2) - 18;
                newFire.fireRect.w = 40; // Width of fireball
                newFire.fireRect.h = 20; // Height of fireball
                newFire.fireSpeed = fireSpeed;
                newFire.active = true;
                newFire.direction = direction; // Fire in the current direction

                // Add the fireball to the list of fires
                fires.push_back(newFire);
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
                isJumping = false; // Stop jumping
                isLanding = true;  // Trigger landing effect
                verticalVelocity = 0;
            }
        }

        // Collision with the tile
        for (auto &tile : tiles)
        {
            if (tile.isColliding(Right_Playerrect))
            {
                if (verticalVelocity > 0)
                {                                                               // Only land if falling down
                    verticalVelocity = 0; // Reset vertical velocity
                    Right_Playerrect.y = tile.tile_rect.y - Right_Playerrect.h ; // Stick player to tile's top surface
                    {
                        std::cout << "Right PLayer y is  :  " << Right_Playerrect.y << std::endl;
                        std::cout <<  "tile rect y is  :  " << tile.tile_rect.y << std::endl;
                        std::cout <<  "Right PLayer h is  :  " << Right_Playerrect.h << std::endl;
                    }
                    // Right_Playerrect.y = tile.tile_rect.y + (tile.tile_rect.h - Right_Playerrect.h);
                    isLanding = false;                                           // Player is on the tile
                    onTile = true;
                    isJumping = false;    // Stop jumping since landed
                    std::cout << "Tile is : " << onTile << std::endl;
                }
            }
            else if (!onTile && !isJumping)
            {
                // If player moves off the tile
                onTile = false;
                if (!isJumping)
                {
                    Right_Playerrect.y += verticalVelocity; // Apply vertical velocity
                    verticalVelocity = gravity +2 ;
                }
                if (Right_Playerrect.y >= 500)
                {
                    Right_Playerrect.y = 500;
                }
                std::cout << "Tile is : " << onTile << std::endl;
            }else{
                onTile = false;
            }
        }

        // Manage dust particles when landing
        if (isLanding )

        {
            Dust newDust;
            newDust.dustRect.x = Right_Playerrect.x + (Right_Playerrect.w / 2) - 25; // Center the dust
            newDust.dustRect.y = Right_Playerrect.y + Right_Playerrect.h - 20 ;       // Position dust at ground level
            newDust.dustRect.w = 40;                                                 // Width of dust
            newDust.dustRect.h = 20;                                                 // Height of dust
            newDust.fadeSpeed = 0.1f;                                                // Fade speed for dust
            newDust.lifetime = dustLifetime;                                         // Set lifetime
            newDust.active = true;                                                   // Activate dust

            dustParticles.push_back(newDust);
            isLanding = false; // Reset landing state
        }

        // Update dust particles
        for (auto &dust : dustParticles)
        {
            if (dust.active)
            {
                dust.lifetime--; // Decrease lifetime
                if (dust.lifetime <= 0)
                {
                    dust.active = false; // Deactivate dust when lifetime ends
                }
                dust.dustRect.y -= dust.fadeSpeed; // Optional: rise or fall effect
                // Optionally change the transparency or size over time here
            }
        }

        // Update fireball positions
        for (auto &fire : fires)
        {
            if (fire.active)
            {
                fire.fireRect.x += fire.fireSpeed * fire.direction; // Move fireball
                if (fire.fireRect.x < 0 || fire.fireRect.x > 1280)
                {
                    fire.active = false; // Deactivate if out of bounds
                }
            }
        }

        // cleaning the fireballs inactive one
        fires.erase(std::remove_if(fires.begin(), fires.end(), [](const Fire &fire)
                                   { return !fire.active; }),
                    fires.end());
        // cleannign the inactive dust particles
        dustParticles.erase(std::remove_if(dustParticles.begin(), dustParticles.end(), [](const Dust &dust)
                                           { return !dust.active; }),
                            dustParticles.end());

        // Clear the renderer
        SDL_RenderClear(render);
        SDL_RenderCopy(render, background_texture, NULL, &Space_rect);                              // Draw background
        SDL_RenderCopyEx(render, Right_person, NULL, &Right_Playerrect, rotationAngle, NULL, flip); // Draw player character
        SDL_RenderCopy(render, enemy_texture, nullptr, &enemy_rect);

        // rendering tiles
        SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
        for (auto &tile : tiles)
        {
            SDL_RenderCopy(render,tile_texture,nullptr ,&tile.tile_rect); // Draw the tile
        }

        // Draw active fireballs
        for (const auto &fire : fires)
        {
            if (fire.active)
            {
                SDL_RenderCopy(render, fire_texture, NULL, &fire.fireRect); // Draw fireball
            }
        }

        // Draw active dust particles
        for (const auto &dust : dustParticles)
        {
            if (dust.active)
            {
                SDL_RenderCopy(render, dust_texture, NULL, &dust.dustRect); // Draw dust
            }
        }

        // Present the rendered frame
        SDL_RenderPresent(render);
        SDL_Delay(16); // Maintain ~60 FPS
    }

    // Cleanup
    SDL_DestroyTexture(background_texture);
    SDL_DestroyTexture(Right_person);
    SDL_DestroyTexture(fire_texture);
    SDL_DestroyTexture(dust_texture);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
