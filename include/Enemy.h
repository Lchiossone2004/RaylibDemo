//  Enemy.h
#ifndef Enemy_H
#define Enemy_H

#include "raylib.h"
#include "Character.h"

class Enemy : public Character{
    public:
    Vector2 spownPoint;
    float movementRadious = 1000;

    Enemy(float x, float y,Texture2D texture,int textureColums, int textureRows,int scale,int speed) : Character(x, y, texture, textureColums, textureRows, scale,speed){
        spownPoint = {x,y};
        Direction = {1,0};
    }
    void KeepInbound();
    void UpdateStep(int newStep);
};

#endif
