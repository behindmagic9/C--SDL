#ifndef COLLIDER_HPP
#define COLLIDER_HPP
#include "SDL2/SDL.h"
#include "Ninja.hpp"
#include<thread>
#include <mutex>


#include "GameObject.hpp"

std::mutex lock;

class ColliderVisitor{
    public :
    // GameObject GameObject;
    Ninja ninja;

    // ColliderVisitor() : wascollide(false){};

    // bool wascollide ;
    bool CheckCollisionWithobject(SDL_Rect first,GameObject* obstacle ){
        int i =0;
        if( SDL_HasIntersection(&first, obstacle->GetRect())){
            if(!obstacle->damageApplied){
                // std::unique_lock locks{lock};
                OnCollideObject(obstacle);
                obstacle->damageApplied = true;
                // std::cout << "changing vlaue" << std::endl;
                // std::cout << "i value 1" << std::endl;
            }
            return true;
        }else{
            obstacle->damageApplied = false;
            // wascollide = false;
            // i = 0;

            // std::cout << "i value 0" << std::endl;
            return  false;
        }
    }
    void OnCollideObject(GameObject* object){
        ninja.TakeDamage(20);
        //signla axe to firsts blink then destroy 
        // object->stoprender();
        // 
        return ;
    }

    bool CheckCollisonwithHeart(SDL_Rect first,GameObject* obstacle){
        bool collide = false;
        if( SDL_HasIntersection(&first, obstacle->GetRect())){
            collide =true;
            OnCollideHeart(obstacle);
        if(obstacle->GetW() < 1){
            obstacle->set(-300,300,53,58);
        }
        };
        return collide;
    }


    // Add this flag to your class to track if damage has been applied
// bool damageApplied = false;

// // Refactored CheckCollisionwithHeart method
// bool CheckCollisionwithHeart(SDL_Rect first, GameObject* obstacle) {
//     bool collide = false;

//     if (SDL_HasIntersection(&first, obstacle->GetRect())) {
//         collide = true;

//         // Check if damage has already been applied during this collision
//         if (!damageApplied) {
//             OnCollideHeart(obstacle);
//             damageApplied = true; // Set flag to true to prevent multiple damage applications
//         }

//         // Reset the obstacle's position if its width is less than 1
//         if (obstacle->GetW() < 1) {
//             obstacle->set(-300, 300, 53, 58);
//         }
//     } else {
//         // Reset damage flag if no collision
//         damageApplied = false;
//     }

//     return collide;
// }

// Refactored OnCollideObject method
// bool OnCollideObject(GameObject* object) {
//     ninja.TakeDamage(20); // Apply damage only once per collision
//     // Additional collision handling (e.g., stopping rendering) can be added here
//     return true;
// }


    void OnCollideHeart(GameObject* object){
        ninja.IncreaseHealth(10);
        // std::cout << "increase health" << std::endl;
        ninja.IncreaseScore(100);
        object->stoprender();
        // return true;
    }

     int getHealth ()const{
        int score = ninja.Gethealth();
        // std::cout << "get health" << std::endl;
        return score;
    }

     int getScore()const{
        // std::cout << "get Score" << std::endl;
        return ninja.GetScore();
    }

    void resetscore(){ ninja.ResetScore();}

};
#endif

// to do 

// remove the texture render ater collide and regenrate when goes out of 640
// add the score adn health to show on top of the screen
// add menu 