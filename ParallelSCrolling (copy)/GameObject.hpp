#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include "TextureManager.hpp"
#include<random>
#include <iostream>
#include "Collider.hpp"

std::random_device dev;
std::mt19937 rng(dev());
std::uniform_int_distribution<std::mt19937::result_type>dist(-500,-100);
class GameObject
{
public:
        bool damageApplied = false;

    GameObject () = default;

    GameObject(int x, int y, int w, int h, Texture *textures) : textures(textures)
    {
        rect = {x, y, w, h};
    }

    void updatex(int rectx)
    {
        rect.x += rectx;
        if (rect.x > 639)
        {
            rect.x = -639;
        }
    }

    void updatey(int y){
        if(rect.y >= 300){
            rect.y -= y;
        }

        if(rect.y <= 240){
            rect.y += y;
        }
    }
    

    void setxy(int x , int y){
        rect.x = x;
        rect.y = y;
    }

    void updateaxex(int rectx){
        rect.x += rectx;
        if(rect.x > 639){
            rect.x = 58+dist(rng);
        }
        
    }

    void set(int x, int y, int w , int h){
        rect = {x,y,w,h};
    }

    void SetDestroyed(bool destroyed){
        isDestroyed = destroyed;
    }

    void stoprender(){
        rect= {0,0,0,0};
        textures->Render(&rect);
        // set the state of destroy and regenrate 
    }


    bool IsDestroyed() const { return isDestroyed;}

    const SDL_Rect *GetRect() const { return &rect; }

    void render(){
        textures->Render(&rect);
    }

    void render(float angle , SDL_RendererFlip flip)
    {
        textures->Render(&rect , angle ,flip );
    }

    // virtual void Accept(ColliderVisitor* visitor) = 0;

    const int &GetX () const{
        return rect.x;
    }
    const int &GetY () const{
        return rect.y;
    }
    
    const int &GetW () const{
        return rect.w;
    }

    const int &GetH () const{
        return rect.h;
    }

private:
    Texture *textures;
    SDL_Rect rect;
    bool isDestroyed;
};
#endif