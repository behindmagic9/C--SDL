#include <iostream>
#include <SDL2/SDL.h>
#include "../include/TextureRectangle.hpp"
#include "../include/GameEntity.hpp"
#include "../include/SDL_App.h"
#include "../include/Animated_sprite.hpp"
#include "../include/Vector2d.hpp"
#include "../include/ResourceManager.hpp"
#include "../include/Sound.hpp"
#include"../include/DynamicRectangle.hpp"
#include "../include/Music.hpp"
#include <vector>
#include <string>
#include <memory>

SDLApp* app;

GameEntity* LeftPaddle; // game entioyt type containing its vector of collider like set fo more rectangles of that object type
GameEntity* RightPaddle;
GameEntity* Ball;

Sound* CollisionSound;
Sound* ScoreSound;

Music* MusicTrack;

struct GameState{
    float movementspeed;
    float ballspeed;
    int ballXDirection;
    int ballydirection;
    int leftScore;
    int rightScore;
};

GameState* gamestate;

void HandleLeftPaddle(){
    const Uint8 *state =  SDL_GetKeyboardState(NULL);
    int LeftPaddleX = LeftPaddle->GetTextureRectangle().GetPositionX();
    int LeftPaddleY = LeftPaddle->GetTextureRectangle().GetPositionY();
    if(state[SDL_SCANCODE_W]){
        LeftPaddleY -= gamestate->movementspeed;
        LeftPaddle->SetPosition(LeftPaddleX,LeftPaddleY);
    }
    else if(state[SDL_SCANCODE_S]){
        LeftPaddleY += gamestate->movementspeed;
        LeftPaddle->SetPosition(LeftPaddleX,LeftPaddleY);
    }
}


void HandleRightPaddle(){
    const Uint8 *state =  SDL_GetKeyboardState(NULL);
    int RightPaddleX = RightPaddle->GetTextureRectangle().GetPositionX();
    int RightPaddleY = RightPaddle->GetTextureRectangle().GetPositionY(); 
    if(state[SDL_SCANCODE_UP]){
        RightPaddleY -= gamestate->movementspeed;
        RightPaddle->SetPosition(RightPaddleX,RightPaddleY);
    }
    else if(state[SDL_SCANCODE_DOWN]){
        RightPaddleY += gamestate->movementspeed;
        RightPaddle->SetPosition(RightPaddleX,RightPaddleY);
    }
}

// before was
// TextureRectangle* LeftPaddle;
// TextureRectangle* RightPaddle;


void HandleEvents()
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            app->StopAppLoop() ;
        }
        HandleLeftPaddle();
        HandleRightPaddle();
     // {
            // checking object of RightPaddle 's vector in which of its set of entity like "leftpaddle" is stricking the other entity of type ball , in thats set of object particular 0 index object is colldign or not  with RightPaddle's  index object 

            // if (RightPaddle->GetCollider(0).IsColliding(LeftPaddle->GetCollider(0)))
            // {
            //     std::cout << "IS colidding with hit box 1" << std::endl;
            //     CollisionSound->PlaySound();
            // }else{
            //     std::cout <<  " nOt colliding with hit box 1" << std::endl;
            // }

            // if(RightPaddle->GetCollider(0).IsColliding(LeftPaddle->GetCollider(1))){
            //     std::cout << "is colliding with hit box 2" << std::endl;
            //     CollisionSound->PlaySound();
            // }
            // else
            // {
            //     std::cout << "not colliding with hit box 2" << std::endl;
            // }
        // }
    }
}

void SetBallCenterPosition(){
    int ballPositionX = app->GetWindowWidth() / 2 - (Ball->GetTextureRectangle().GetWidth() / 2);
    int ballPositionY = app->GetWindowHeight() / 2 - (Ball->GetTextureRectangle().GetHeight() / 2);

    Ball->SetPosition(ballPositionX,ballPositionY);
}
void Handleballmoving(){
    int ballPositionX = Ball->GetTextureRectangle().GetPositionX();
    int ballPositionY = Ball->GetTextureRectangle().GetPositionY();

    if(gamestate->ballXDirection == 1){
        ballPositionX += gamestate->movementspeed;
    }
    else{
        ballPositionX -= gamestate->movementspeed;
    }

    if(gamestate->ballydirection == 1){
        ballPositionY += gamestate->movementspeed;
    }else{
        ballPositionY -= gamestate->movementspeed;
    }

    Ball->SetPosition(ballPositionX,ballPositionY);

}

void HandleBoundaryAndScore(){
    int ballPositionX = Ball->GetTextureRectangle().GetPositionX();
    int ballPositionY = Ball->GetTextureRectangle().GetPositionY();

    if(ballPositionY > app->GetWindowHeight()){
        gamestate->ballydirection = -1;
    }
    else if(ballPositionY < 0){
        gamestate->ballydirection = 1;
    }

    Ball->SetPosition(ballPositionX,ballPositionY);

    if(ballPositionX > app->GetWindowWidth() + 80){
        ScoreSound->PlaySound();
        gamestate->ballXDirection = -1;
        gamestate->leftScore += 1 ;
        SetBallCenterPosition();
    }
    else if(ballPositionX < -100 ){
        ScoreSound->PlaySound();
        gamestate->ballXDirection = 1;
        gamestate->rightScore += 1 ;
        SetBallCenterPosition();
    }

}


void handlePaddleCollision(){
    int ballPositionX = Ball->GetTextureRectangle().GetPositionX();
    int ballPositionY = Ball->GetTextureRectangle().GetPositionY();

    if(ballPositionX >= 20 && gamestate->ballXDirection == -1 && LeftPaddle->GetCollider(0).IsColliding(Ball->GetCollider(0))){
        gamestate->ballXDirection = 1;
        CollisionSound->PlaySound();
        int paddleMidpoint = LeftPaddle->GetTextureRectangle().GetPositionY()+100;
        if(paddleMidpoint <= ballPositionY){
            gamestate->ballydirection = -1;
        }else if(paddleMidpoint > ballPositionY){
            gamestate->ballydirection = 1;
        }
    }

    else if (ballPositionX <= 610 && gamestate->ballXDirection==1 && RightPaddle->GetCollider(0).IsColliding(Ball->GetCollider(0))){
        gamestate->ballXDirection = -1;
        CollisionSound->PlaySound();
        int paddleMidpoint = RightPaddle->GetTextureRectangle().GetPositionY() + 100;
        if(paddleMidpoint <= ballPositionY){
            gamestate->ballydirection = -1;
        }else if(paddleMidpoint > ballPositionY){
            gamestate->ballydirection = 1;
        }
    }
    Ball->SetPosition(ballPositionX,ballPositionY);
}

void HandleRendering()
{

    LeftPaddle->Render();
    RightPaddle->Render();
    Ball->Render();

    DynamicText LeftScore("../Assets/font.ttf",32);
    DynamicText RightScore("../Assets/font.ttf",32);

    std::string lScore = "left : " + std::to_string(gamestate->leftScore);
    std::string rScore = "right : " + std::to_string(gamestate->rightScore);
    
    LeftScore.DrawText(app->GetRender(),lScore,0,0,100,50);
    RightScore.DrawText(app->GetRender(),rScore,500,0,100,50);

     // texture are always render after rendering the game object or entities 
    // Score1.DrawText(app->GetRender(),"Mike SDL2",10,10,100,50);

}

void HandleUpdate(){

    int ballPositionX = Ball->GetTextureRectangle().GetPositionX();
    int ballPositionY = Ball->GetTextureRectangle().GetPositionY();

    Handleballmoving();
    HandleBoundaryAndScore();
    handlePaddleCollision();

    static int currentTime   = SDL_GetTicks();
    static int lastTime      = SDL_GetTicks();
    currentTime = SDL_GetTicks();
    if (currentTime > lastTime + 1000) {
        ScoreSound->StopSound();
        CollisionSound->StopSound();
        lastTime = currentTime;
    }

    // LeftPaddle->update();
    // RightPaddle->update();

    // static bool up =true;
    // static bool right = true;
    // static int posX = 0;
    // static int posY = 0;

    // if(up){
    //     posY--;
    // }else{
    //     posY++;
    // }

    // if(right){
    //     posX++;
    // }else{
    //     posX--;
    // }

    // if(posX+100 > app->GetWindowWidth()){
    //     right = false;
    // }else if(posX < 0){
    //     right = true;
    // }

    // if(posY+100 >= app->GetWindowHeight()){
    //     up = true;
    // }else if(posY < 0 ){
    //     up = false;
    // }
    // // object which is moving all around the screen by itself
    // Ball->SetPosition(posX,posY);
    // Ball->SetDimension(100,100);

    // LeftPaddle->SetPosition(10,10);


    // RightPaddle->SetPosition(620,10);
    // RightPaddle->SetDimension(20,200);

// its givng the object 1 ehcih is moving with mouse the boadries like setting its dimension  adn its postionj is as set to the mosue poisiton , but boundaries are given now,
// setting width of that too the wholeoriginal surface of kong without the SDL_St colorKey how look like ,  by GetTextureRectangle().GetWidth() and height of original surface divide by 2
    // LeftPaddle->GetCollider(1).SetDimension(LeftPaddle->GetTextureRectangle().GetWidth(), LeftPaddle->GetTextureRectangle().GetHeight()/2);

// this be set the boundaries of the second boaundaries to the kong auto setting the boundaries especailly by a n algorithm
    // Vector2d dims = LeftPaddle->GetCollider(0).SetoundsAutomatically(ResourceManager::GetInstance().GetSurface("../Assets/leftpaddle.bmp"), 0xff,0x00,0xff);
// then storing those dimesions of x and y to the vector2d of x and y mamber variables..
    // int newXpos = dims.x + app->GetMouseX();
    // int newYpos = dims.y + app->GetMouseY();

    // so updated position  be like is dims.x + mousex coordinates
    // same for y coordinates

    // then setting the LeftPaddle which is moving by mouse to the updates posx and posy of the rectangel of LeftPaddle's index 0 enity 's rectangle boundaries positon.
    // LeftPaddle->GetCollider(0).SetPosition(newXpos,newYpos);
}

int main()
{
    const char* title = "New SDL2 Abstraction";
    // with this bit wise or operator we are passing bith subsystem to the SDL to initialise them
    app = new SDLApp(SDL_INIT_AUDIO | SDL_INIT_VIDEO,title, 10, 10, 640, 480);
    app->SetMaxFrameRate(16);

    LeftPaddle = new GameEntity(app->GetRender()); // before was TextureRectange(app->GetRender(),....)
    LeftPaddle->AddTextureRectangleConponent("../Assets/leftpaddle.bmp");
    LeftPaddle->SetDimension(20,200);
    LeftPaddle->AddCollider2D();
    LeftPaddle->GetCollider(0).SetDimension(LeftPaddle->GetTextureRectangle().GetWidth(),LeftPaddle->GetTextureRectangle().GetHeight());
    LeftPaddle->SetPosition(10,200);
    // LeftPaddle->GetCollider(0)
    // LeftPaddle->AddCollider2D();

    RightPaddle = new GameEntity(app->GetRender());
    RightPaddle->AddTextureRectangleConponent( "../Assets/rightpaddle.bmp"); // not given color key son not be transparent
    RightPaddle->SetDimension(20,200);
    RightPaddle->AddCollider2D();
    RightPaddle->GetCollider(0).SetDimension(RightPaddle->GetTextureRectangle().GetWidth(),RightPaddle->GetTextureRectangle().GetHeight());
    RightPaddle->SetPosition(610,200);

    Ball = new GameEntity (app->GetRender());
    Ball->AddTextureRectangleConponent("../Assets/ball.bmp");
    Ball->AddCollider2D();
    Ball->GetTextureRectangle().SetDimension(20,20);
    Ball->GetCollider(0).SetDimension(Ball->GetTextureRectangle().GetWidth(), Ball->GetTextureRectangle().GetHeight());
    Ball->SetPosition(app->GetWindowWidth() / 2 , app->GetWindowHeight() / 2);

    CollisionSound = new Sound("../Assets/Sound/Colide.wav");
    CollisionSound->SetUpDevice(); 
    
    ScoreSound = new Sound("../Assets/Sound/Score.wav");
    ScoreSound->SetUpDevice();

    MusicTrack = new Music("../Assets/Music/guitarchords.mp3");
    MusicTrack->PlayMusic(-1);
    

    gamestate = new GameState;
    gamestate->movementspeed = 5.0f;
    gamestate->ballspeed        = 2.0f;
    gamestate->ballXDirection   = 1;
    gamestate->ballydirection   = 1;
    gamestate->leftScore        = 0;
    gamestate->rightScore       = 0;

    app->SetEventCallback(HandleEvents);
    app->SetUpdateCallback(HandleUpdate);
    app->SetRenderCallback(HandleRendering);

    app->RunLoop();

    delete app;
    delete LeftPaddle;
    delete RightPaddle;
    delete Ball;
    delete CollisionSound;
    delete ScoreSound;
    delete MusicTrack;

    return 0;
}
