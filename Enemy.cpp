#include "raylib.h"
#include "Enemy.h"
#define MAP_WIDTH 50
#define MAP_HEIGHT 38
#define TILE_WIDTH 28
#define TILE_HEIGHT 28  
#define STEP 3

void Enemy::Speed(float x, float y){
    SpeedX = x;
    SpeedY = y;
}
