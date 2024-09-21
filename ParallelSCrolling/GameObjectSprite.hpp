#ifndef GAME_OBJECT_SPRITE_HPP
#define GAME_OBJECT_SPRITE_HPP


#include "SpriteTextures.hpp"
#include <iostream>
class GameObjectSprite
{
public:
    GameObjectSprite(int x, int y, int w, int h, SpriteTexture* textures ,int sx, int sy, int sw, int sh) : textures(textures)
    {
        dest = {x, y, w, h};
        src = {sx, sy, sw, sh};
    }

    void update(int x, int y , int w, int h)
    {
        src = {x, y, w, h};
    }

    void SetPlusRectangle(int x, int y, int w, int h, int frame)
    {
        src.x = x + (frame * w);
        src.y = y;
        src.w = w;
        src.h = h;
    }

    void SetMinusRectangle(int x, int y, int w, int h, int frame)
    {
        src.x = x - (frame * w);
        src.y = y;
        src.w = w;
        src.h = h;
    }

    void updatewh(int w, int h ){
        dest.w = w;
        dest.h =h;
    }

    void updatexy(int x, int y ){
        dest.x = x;
        dest.y =y;
    }

    void render()
    {
        textures->Render( &src, &dest);
    }


// Getters for dst

    const int &GetDstX () const{
        return dest.x;
    }

    const int &GetDstY () const{
        return dest.y;
    }
    
    const int &GetDstW () const{
        return dest.w;
    }

    const int &GetDstH () const{
        return dest.h;
    }

//Getters For src

    const int &GetSrcX () const{
        return src.x;
    }

    const int &GetSrcY () const{
        return src.y;
    }
    
    const int &GetSrcW () const{
        return src.w;
    }

    const int &GetSrcH () const{
        return src.h;
    }
private:
    SpriteTexture *textures;
    SDL_Rect src;
    SDL_Rect dest;
};


#endif