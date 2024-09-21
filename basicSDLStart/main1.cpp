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

    window = SDL_CreateWindow("Ninja Animation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
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
    SDL_Surface *mountain = SDL_LoadBMP("images/mountains.bmp");
    SDL_Surface *cloud = SDL_LoadBMP("images/clouds.bmp");
    SDL_Surface *hill = SDL_LoadBMP("images/hills.bmp");
    SDL_Surface *road = SDL_LoadBMP("images/roads.bmp");
    SDL_Surface *ninja = SDL_LoadBMP("images/ninja_Jump_sprite1.bmp"); // Load ninja jump sprite
    SDL_Surface *ninjaRun = SDL_LoadBMP("images/ninja_Run_Sprite1.bmp"); // Load ninja run sprite
    SDL_Surface *axe_surface = SDL_LoadBMP("images/axe.bmp");

    if (!mountain || !cloud || !hill || !road || !ninja || !ninjaRun || !axe_surface)
    {
        std::cout << "Error loading images! SDL Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Set transparency for images
    SDL_SetColorKey(mountain, SDL_TRUE, SDL_MapRGB(mountain->format, 0xff, 0x00, 0xff));
    SDL_SetColorKey(hill, SDL_TRUE, SDL_MapRGB(hill->format, 0xff, 0x00, 0xff));
    SDL_SetColorKey(road, SDL_TRUE, SDL_MapRGB(road->format, 0xff, 0x00, 0xff));
    SDL_SetColorKey(cloud, SDL_TRUE, SDL_MapRGB(cloud->format, 0xff, 0x00, 0xff));

    // Create textures
    SDL_Texture *mountain_texture = SDL_CreateTextureFromSurface(render, mountain);
    SDL_Texture *cloud_texture = SDL_CreateTextureFromSurface(render, cloud);
    SDL_Texture *hill_texture = SDL_CreateTextureFromSurface(render, hill);
    SDL_Texture *road_texture = SDL_CreateTextureFromSurface(render, road);
    SDL_Texture *ninja_texture = SDL_CreateTextureFromSurface(render, ninja); // Ninja jump texture
    SDL_Texture *ninja_run_texture = SDL_CreateTextureFromSurface(render, ninjaRun); // Ninja run texture

    SDL_Texture* axe_texture = SDL_CreateTextureFromSurface(render, axe_surface);

    SDL_FreeSurface(mountain);
    SDL_FreeSurface(cloud);
    SDL_FreeSurface(hill);
    SDL_FreeSurface(road);
    SDL_FreeSurface(ninja);
    SDL_FreeSurface(ninjaRun);
    SDL_FreeSurface(axe_surface);

    // Define positions and sizes of elements
    SDL_Rect mountains1 = {0, 0, 640, 480};
    SDL_Rect mountains2 = {-639, 0, 640, 480};
    SDL_Rect clouds1 = {0, 0, 640, 480};
    SDL_Rect clouds2 = {-639, 0, 640, 480};
    SDL_Rect hills1 = {0, 0, 640, 480};
    SDL_Rect hills2 = {-639, 0, 640, 480};
    SDL_Rect roads1 = {0, 0, 640, 480};
    SDL_Rect roads2 = {-639, 0, 640, 480};
    SDL_Rect axe1 = {0,310,100,103};
    SDL_Rect axe2 = {-639,310,100, 103};


    SDL_Rect dest = {500, 300, 58, 103}; // Ninja position
    SDL_Rect src = {0, 0, 67, 67};       // Ninja frame position
    bool gameIsRunning = true;
    bool isJumping = false; // Track jumping state
    int totalframeJump = 10;
    int totalframeRun = 6;
    Uint32 lastFrametime = SDL_GetTicks();
    float animationSpeed = 0.1f;
    float accumulatedTime = 0.0f;
    int frame = 1;

    int initialX = dest.x; // Store the initial X position of the ninja
    int initialY = dest.y; 
    int originalWidth = 67;
    int originalHeight = 67;

    float axeangle = 0.0f;

    while (gameIsRunning)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                gameIsRunning = false;
            }

            // Detect spacebar press to trigger jump
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
            {
                if (!isJumping) // Only jump if not already jumping
                {
                    isJumping = true;
                    frame = 0; // Reset jump frame to start
                }
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(render, 0x66, 0x66, 0x66, 0xFF);
        SDL_RenderClear(render);

        // Update background positions
        SDL_Delay(20);
        mountains1.x += 1;
        mountains2.x += 1;
        hills1.x += 2;
        hills2.x += 2;
        clouds1.x += 2;
        clouds2.x += 2;
        roads1.x += 4;
        roads2.x += 4;
        axe1.x += 5;
        axe2.y += 5;

        // Reset positions when out of screen
        if (clouds1.x > 639) clouds1.x = -639;
        if (clouds2.x > 639) clouds2.x = -639;
        if (mountains1.x > 639) mountains1.x = -639;
        if (mountains2.x > 639) mountains2.x = -639;
        if (hills1.x > 639) hills1.x = -639;
        if (hills2.x > 639) hills2.x = -639;
        if (roads1.x > 639) roads1.x = -639;
        if (roads2.x > 639) roads2.x = -639;
        

   if (axe1.x > 639) axe1.x = -100;
    if (axe2.x > 639) axe2.x = -100;

    // Update the rotation angle for continuous rotation
    axeangle += 5.0f; // Increment rotation angle, you can adjust the speed by changing this value
    if (axeangle >= 360.0f) axeangle = 0.0f; 

        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastFrametime) / 1000.0f;
        lastFrametime = currentTime;

        accumulatedTime += deltaTime;
        if (accumulatedTime >= animationSpeed)
        {
            if (isJumping)
            {
                // Handle jump animation
                frame = (frame + 1) % totalframeJump;
                src.x = 522 - (frame * 58); // Adjust for jump frame positions
                src.y = 16;
                src.w = 58;
                src.h = 103;

                // End jump after one cycle of jump animation
                if (frame == totalframeJump - 1)
                {
                    isJumping = false; // Return to running after jump finishes
                    frame = 0;
                }
            }
            else
            {
                // Handle running animation
                frame = (frame + 1) % totalframeRun;
                src.x = 343 - (frame * 67); // Adjust for run frame positions
                src.y = 17;
                src.w = 67;
                src.h = 67;
            }
            

            accumulatedTime = 0.0f;
        }
         float jumpScale = 1.05f; // Scale factor for jump
        float runScale = 1.1f;  // Scale factor for running

        // Adjust the size of the ninja when jumping
        if (isJumping)
        {
            dest.w = static_cast<int>(58 * jumpScale); // Scaled width for jump sprite
            dest.h = static_cast<int>(103 * jumpScale); // Scaled height for jump sprite
        }
        else
        {
            dest.w = static_cast<int>(67 * runScale); // Scaled width for run sprite
            dest.h = static_cast<int>(67 * runScale); // Scaled height for run sprite
        }
        // Keep the ninja in the same horizontal position (centered)
        dest.x = initialX + (originalWidth - dest.w) / 2;
        dest.y = initialY + (originalHeight - dest.h) / 2;

    
        // Render background elements
        SDL_RenderCopy(render, mountain_texture, NULL, &mountains1);
        SDL_RenderCopy(render, mountain_texture, NULL, &mountains2);
        SDL_RenderCopy(render, hill_texture, NULL, &hills1);
        SDL_RenderCopy(render, hill_texture, NULL, &hills2);
        SDL_RenderCopy(render, cloud_texture, NULL, &clouds1);
        SDL_RenderCopy(render, cloud_texture, NULL, &clouds2);
        SDL_RenderCopy(render, road_texture, NULL, &roads1);
        SDL_RenderCopy(render, road_texture, NULL, &roads2);
        SDL_RenderCopyEx(render, axe_texture, NULL, &axe1,axeangle,NULL,SDL_FLIP_NONE );
        SDL_RenderCopy(render, axe_texture, NULL, &axe2);

        // Render ninja (running or jumping based on state)
        SDL_RenderCopy(render, isJumping ? ninja_texture : ninja_run_texture, &src, &dest);

        // Present updated screen
        SDL_RenderPresent(render);
    }

    // Cleanup
    SDL_DestroyTexture(mountain_texture);
    SDL_DestroyTexture(hill_texture);
    SDL_DestroyTexture(road_texture);
    SDL_DestroyTexture(cloud_texture);
    SDL_DestroyTexture(ninja_texture);
    SDL_DestroyTexture(ninja_run_texture);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
