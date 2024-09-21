#ifndef GAME_STATE_MANAGER
#define GAME_STATE_MANAGER

enum GameState{
    MENU,
    PLAYING,
    PAUSED,
    GAME_OVER
};


class GameStateManager{
    public  :
        static GameStateManager& getInstance(){
            static GameStateManager instance;
            return instance;
        }

        GameState getGameState() const { return gameState;}
        GameState getPrevGameState() const { return prevState;}

        void setGameState(GameState state) { prevState = gameState; gameState = state;}

        bool isGameover() const{ return gameState == GAME_OVER;}
        bool isGameOver() const{ return gameState == PLAYING;}
        bool isPaused() const{ return gameState == PAUSED;}
    private :
        GameState gameState;
        GameState prevState;
        GameStateManager() : gameState(MENU) , prevState(MENU) {}

        GameStateManager(const GameStateManager&) = delete;
        void operator=(const GameStateManager&) = delete;
};
#endif