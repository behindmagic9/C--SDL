#ifndef NINJA_HPP
#define NINJA_HPP


// #include "Collider.hpp"
#include "GameObject.hpp"
#include "GameStateManager.hpp"

class Ninja : public GameObject  {
public:

    // Ninja(int x, int y , int w, int h, Texture* texture ) : GameObject(x, y, w, h, texture), health(100), score(0) {

    // }

    void TakeDamage(int damage){
        health -= damage;
        if(health <= 0){
            SetDestroyed(true);
            std::cout << "game over" << std::endl;
            GameStateManager::getInstance().setGameState(GAME_OVER);
        }
    }

    void IncreaseScore(int points){
        score += points;
    }

    void IncreaseHealth(int healthPoints){
        if(health < 100 ){
            health += healthPoints;
        }
    }

    // void accept(ColliderVisitor* visitor) {
    //     visitor->visitNinja(this);
    // }

    int Gethealth() const{ return health;}

    int GetScore() const { return score; }

    void ResetScore(){  health = 100; }

private:
    int health = 100;
    int score = 0;
};

#endif