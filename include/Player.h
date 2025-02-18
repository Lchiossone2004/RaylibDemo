// Player.h
#ifndef Player_H
#define Player_H

#include "raylib.h"
#include "Character.h"

class Player : public Character{
    public:
    Player(float x, float y,Texture2D texture,int textureColums, int textureRows,int scale,int speed) : Character(x, y, texture, textureColums, textureRows, scale,speed){
    }
};
#endif
