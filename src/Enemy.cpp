#include "raylib.h"
#include "Enemy.h"
#define MAP_WIDTH 50
#define MAP_HEIGHT 38
#define TILE_WIDTH 28
#define TILE_HEIGHT 28  
#define STEP 3

void Enemy::UpdateStep(int newStep){
    step = newStep;
}

void Enemy::KeepInbound(){
    if(posX >= spownPoint.x + movementRadious || posX <= spownPoint.x - movementRadious){
        Direction.x *= -1;
    }
    if(posY >= spownPoint.y + movementRadious || posY <= spownPoint.y - movementRadious){
        Direction.y *= -1;
    }   
}