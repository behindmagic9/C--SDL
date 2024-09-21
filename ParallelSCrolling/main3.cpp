#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include "TextureManager.hpp"
#include "GameStateManager.hpp"
#include "GameObjectSprite.hpp"
#include "Collider.hpp"
#include "font.hpp"

void resetAxe(GameObject& axe1, GameObject& axe2){
    axe1.setxy(0, 345);
    axe2.setxy(-230, 345);
}


void resetheart(GameObject& heart){
    heart.setxy(-320, 300);
}

void clearScreen(SDL_Renderer *render)
{
    SDL_SetRenderDrawColor(render, 0x66, 0x66, 0x66, 0xFF);
    SDL_RenderClear(render);
}

void updateObject(GameObject* object, int x)
{
    // int newx = object.GetX() + x;
    object->updatex(x);
}

void updateObjectxy(GameObject* object, int y)
{
    // int newx = object.GetX() + x;
    object->updatey(y);
}

int main()
{
    ColliderVisitor collisiondetector;
    SDL_Window *window = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not be initialized! SDL Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    window = SDL_CreateWindow("Ninja Runner", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
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
    if (TTF_Init() == -1)
    {
        std::cout << "SDL_TTF could not be initialized! SDL_ttf Error : " << TTF_GetError() << std::endl;
        return -1;
    }

    Font score(render);
    if (!score.LoadFont("Fonts/LIVINGBY.TTF", 44))
    {
        return -1;
    }

    Font Health(render);
    if (!Health.LoadFont("Fonts/LIVINGBY.TTF", 44))
    {
        return -1;
    }

    Font highScore(render);
    if (!highScore.LoadFont("Fonts/LIVINGBY.TTF", 70))
    {
        return -1;
    }

    SDL_Color color = {0, 0, 0, 255};

    Texture mountains_texture(render);
    Texture hills_texture(render);
    Texture roads_texture(render);
    Texture clouds_texture(render);
    SpriteTexture ninja_Run_texture(render);
    SpriteTexture ninja_Jump_texture(render);
    Texture axe_texture(render);
    SpriteTexture ninja_hurt_texture(render);
    Texture heart_texture(render);
    Texture menu(render);

    menu.Load("images/StartScreen1.bmp");

    Texture pause(render);

    pause.Load("images/Pause.bmp");

    Texture over(render);

    over.Load("images/GameOver.bmp");



    mountains_texture.Load("images/mountains2.bmp");
    hills_texture.LoadWithColorKey("images/hills4.bmp", 0xCE ,0xFA, 0xEB);
    roads_texture.LoadWithColorKey("images/road3.bmp", 0xCE ,0xFA, 0xEB);
    clouds_texture.LoadWithColorKey("images/clouds3.bmp", 0xCE ,0xFA, 0xEB);
    ninja_Run_texture.LoadSprite("images/ninja_Run_Sprite3.bmp");
    ninja_Jump_texture.LoadSprite("images/ninja_Jump_sprite1.bmp");
    ninja_hurt_texture.LoadSprite("images/ninja_hurt1.bmp");
    axe_texture.Load("images/ax12.bmp");
    heart_texture.Load("images/Heart.bmp");
    float heartSpeed = 0.05f; // Speed of movement (adjust for faster or slower)
    float heartAmplitude = 30.0f; // How far up and down the heart moves
    float heartTime = 0.0f; // Time variable for sine wave

    GameObject mountains1(0, 0, 640, 480, &mountains_texture);
    GameObject mountains2(-639, 0, 640, 480, &mountains_texture);

    GameObject hills1(0, 0, 640, 480, &hills_texture);
    GameObject hills2(-639, 0, 640, 480, &hills_texture);

    GameObject roads1(0, 0, 640, 480, &roads_texture);
    GameObject roads2(-639, 0, 640, 480, &roads_texture);

    GameObject clouds1(0, 0, 640, 480, &clouds_texture);
    GameObject clouds2(-639, 0, 640, 480, &clouds_texture);

    // GameObject heart(0,245,50,50,&heart_texture);

    // srand(static_cast<unsigned int>(time(0)));

    GameObject axe1 = {0, 345, 80, 70, &axe_texture};
    GameObject axe2 = {-230, 345, 80, 70, &axe_texture};
    // const int ninjawidth = 58;
    // const int minAxeGap = ninjawidth;

    GameObjectSprite ninja_run = {500, 300, 58, 103, &ninja_Run_texture, 0, 0, 67, 67};
    GameObjectSprite ninja_jump = {500, 300, 58, 103, &ninja_Jump_texture, 0, 0, 67, 67};
    GameObjectSprite ninja_hurt = {500, 300, 58, 103, &ninja_hurt_texture, 0, 0, 67, 67};

    GameObject heart = {-320, 300, 58, 53, &heart_texture};
    int heartinitialX = -320;
    int heartinitialY = 300;
    int heartinitialW = 58;
    int heartinitialH = 53;

    bool isJumping = false;
    bool isHurt = false;
    int totalJumpFrame = 9;
    int totalRunFrame = 6;
    int totalhurtframe = 3;
    Uint32 lastFrametime = SDL_GetTicks();

    float axeangle = 0.0f;

    float accumulatedtime = 0.0f;
    float animationSpedd = 0.1f;
    int frame = 0;

    int initialX = ninja_run.GetDstX();
    int initialY = ninja_run.GetDstY();
    int originalWidth = 67;
    int originalHeight = 67;

    int heartXdirection = 1;

    // first load the menu and the pause screen
    // load the texture;
    // defauklt set the gamestatemanager to the menu
    GameStateManager &gameState = GameStateManager::getInstance();
    bool gameIsRunning = true;

    while (gameIsRunning)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                gameIsRunning = false;
            }

            // Handle different game states
            switch (gameState.getGameState())
            {
            case MENU:
                // Display the menu
                // Add logic to render menu and handle selection input
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
                {
                    // Assuming pressing "Enter" starts the game
                    gameState.setGameState(PLAYING);
                }
                break;
                

            case PLAYING:
                // Handle the game playing logic
                if(gameState.getPrevGameState() != PLAYING){
                    isHurt = false;
                }
                if (event.type == SDL_KEYDOWN)
                {
                    if (event.key.keysym.sym == SDLK_p)
                    {
                        // Pause the game when 'P' is pressed
                        gameState.setGameState(PAUSED);
                    }
                    if (event.key.keysym.sym == SDLK_SPACE)
                    {
                        if (!isJumping && !isHurt)
                        {
                            // Only jump if not already jumping and not hurt
                            isJumping = true; // Enable jumping
                            frame = 0;        // Reset frame to start jump animation
                        }
                    }
                }
                // Add game logic (movement, collision, health, etc.) here
                break;

            case PAUSED:
                // Handle the paused state
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
                {
                    // Resume the game when 'P' is pressed again
                    gameState.setGameState(PLAYING);
                }
                break;

            case GAME_OVER:
                // Handle game over state
                // Display game over screen and handle input for restarting or quitting
                if (event.type == SDL_KEYDOWN)
                {
                    if (event.key.keysym.sym == SDLK_r)
                    {
                        collisiondetector.resetscore();
                        resetAxe(axe1, axe2);
                        resetheart(heart);
                        // Restart the game
                        gameState.setGameState(PLAYING);
                        // Reset game variables such as health, position, etc.
                    }
                    if (event.key.keysym.sym == SDLK_q)
                    {
                        // End the game
                        gameIsRunning = false;
                    }
                }
                break;
            }
        }

        clearScreen(render);
        
        if (gameState.getGameState() == PLAYING)
        {

            SDL_Delay(15);

            updateObject(&mountains1, 1);
            updateObject(&mountains2, 1);
            updateObject(&clouds1, 2);
            updateObject(&clouds2, 2);
            updateObject(&hills1, 2);
            updateObject(&hills2, 2);
            updateObject(&roads1, 4);
            updateObject(&roads2, 4);
            updateObject(&axe1, 5);
            updateObject(&axe2, 5);
            updateObject(&heart, 4);


            axeangle += 5.0f; // increment the angle for continous rotation
            if (axeangle >= 360.0f)
                axeangle = 0.0f;

            Uint32 currentTime = SDL_GetTicks();
            float deltatime = (currentTime - lastFrametime) / 1000.0f;
            lastFrametime = currentTime;

            accumulatedtime += deltatime;
            if (accumulatedtime >= animationSpedd)
            {
                if (isJumping)
                {
                    frame = (frame + 1) % totalJumpFrame; // if frame+1 == toatljumpfarme .. % will give 0 so its to reset the frame
                    // settig the source  again
                    ninja_jump.SetMinusRectangle(522, 16, 58, 103, frame);

                    if (frame == totalJumpFrame - 1)
                    {
                        isJumping = false;
                        frame = 0;
                        // std::cout << "jumping fininshesd" << std::endl;
                    }
                }
                else if (isHurt)
                {
                    frame = (frame + 1) % totalhurtframe;

                    ninja_hurt.SetPlusRectangle(1, 1, 57, 76, frame);

                    if (frame == totalhurtframe - 1)
                    {
                        isHurt = false;
                        frame = 0;
                        // std::cout << "hurt finished" << std::endl;
                    }
                }
                else 
                {
                    frame = (frame + 1) % totalRunFrame;
                    // again setting the source
                    ninja_run.SetMinusRectangle(343, 17, 67, 67, frame);
                }
                accumulatedtime = 0.0f;
            }

            // now its the scaling factor of the jump as in the animation it seems preety small
            float JumpScale = 1.3f;
            float runScale = 1.1f;

            if (isJumping)
            {
                int w = static_cast<int>(58 * JumpScale);
                int h = static_cast<int>(103 * JumpScale);
                ninja_jump.updatewh(w, h);
            }
            else
            {
                int w = static_cast<int>(67 * runScale);
                int h = static_cast<int>(67 * runScale);
                ninja_run.updatewh(w, h);
            }

            // updating the scaled postions
            int xx = initialX + (originalWidth - ninja_jump.GetDstW()) / 2;
            int yy = initialY + (originalWidth - ninja_jump.GetDstH()) / 2;
            ninja_jump.updatexy(xx, yy);
            ninja_hurt.updatexy(xx, yy);

            mountains1.render();
            mountains2.render();


            hills1.render();
            hills2.render();

            clouds1.render();
            clouds2.render();

            roads1.render();
            roads2.render();

            axe2.render(axeangle, SDL_FLIP_NONE);
            axe1.render(axeangle, SDL_FLIP_NONE);

            heart.render();

            SDL_Rect ninjaBox;
            if (isJumping)
            {
                ninjaBox.x = ninja_jump.GetDstX();     // X position of jumping ninja
                ninjaBox.y = ninja_jump.GetDstY();     // Y position of jumping ninja
                ninjaBox.w = ninja_jump.GetDstW();     // Width of jumping ninja
                ninjaBox.h = ninja_jump.GetDstH() / 2; // Height of jumping ninja
                ninja_jump.render();
            }
            else if(!isHurt)
            {
                ninjaBox.x = ninja_run.GetDstX(); // X position of running ninja
                ninjaBox.y = ninja_run.GetDstY(); // Y position of running ninja
                ninjaBox.w = ninja_run.GetDstW(); // Width of running ninja
                ninjaBox.h = ninja_run.GetDstH(); // Height of running ninja
                ninja_run.render();
            }
            
            if (collisiondetector.CheckCollisionWithobject(ninjaBox, &axe1) || collisiondetector.CheckCollisionWithobject(ninjaBox, &axe2))
            { // this detect the collison of ninjabox with both axe and axe 2 if any true give true
                // make the axe transparent and run the hit sprite
                isHurt = true;
                // std::cout << "hurt " << std::endl;
                ninja_hurt.render();
            }

            // // check sollison for heart;
            collisiondetector.CheckCollisonwithHeart(ninjaBox, &heart);
            std::string scores = std::to_string(collisiondetector.getScore());
            std::string health = std::to_string(collisiondetector.getHealth());
            // std::string scores = std::to_string(scoress);
            score.RenderText("Score : " + scores, 10, 10, color);
            Health.RenderText("Health : " + health, 400, 10, color);
        }

        if (gameState.getGameState() == PAUSED)
        {
            SDL_Rect rect {0,0,640,480};
            pause.Render(&rect);
            // render the pause texture
        }

        if (gameState.getGameState() == GAME_OVER)
        {
            // render the gameover texture
            std::string high =  std::to_string( collisiondetector.getScore());
            SDL_Rect rect {0,0,640,480};
            over.Render(&rect);
            highScore.RenderText("High score : "+ high,20,250,color);
        }

        if (gameState.getGameState() == MENU)
        {
            // render the menu texture
            SDL_Rect rect {0,0,640,480};
            menu.Render(&rect);
        }

        // SDL_RenderDrawRect(render, &ninjaBox);
        SDL_RenderPresent(render);
    }

    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}