#include "raylib.h"
#include "Character.h"
#define MAP_WIDTH 50
#define MAP_HEIGHT 38
#define TILE_WIDTH 28
#define TILE_HEIGHT 28  
#define STEP 3

void Character::Draw(int currentFrame) {
    //DrawCircle(posX,posY,radious,WHITE);
    Rectangle frame = {(CurrentTexture.width/2)*currentFrame,0,CurrentTexture.width/2,CurrentTexture.height};
    DrawTextureRec(CurrentTexture,frame,{posX,posY}, WHITE);
}

void Character::DrawHit(int currentFrame){
    Rectangle frame = {(CurrentTexture.width/2)*currentFrame,0,CurrentTexture.width/2,CurrentTexture.height};
    if(currentFrame == 0){
        DrawTextureRec(CurrentTexture,frame,{posX,posY}, WHITE);
    }
    else{
        DrawTextureRec(CurrentTexture,frame,{posX,posY}, RED);
    }
}

void Character::ChangeDirection(float x, float y){
    Direction.x = x;
    Direction.y = y;
}

static bool IsSolid(int x, int y, int **map) {
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) return true; // Out of bounds = solid
    return map[y][x] == 1;
}

void Character::Update(int **map, int currentFrame) {
    float newX = posX + Direction.x*STEP;
    float newY = posY + Direction.y*STEP;

        // Convert new position to tile coordinates
        int tileX1 = newX / TILE_WIDTH;                   // Top-left
        int tileY1 = newY / TILE_HEIGHT;
        int tileX2 = (newX + CurrentTexture.width/2 - 1) / TILE_WIDTH;  // Top-right
        int tileY2 = (newY + CurrentTexture.height - 1) / TILE_HEIGHT;

    // Check all corners for collision
    if (!IsSolid(tileX1, tileY1,map) && !IsSolid(tileX2, tileY1,map) &&
    !IsSolid(tileX1, tileY2,map) && !IsSolid(tileX2, tileY2,map)) {
    // Only move if no collision
    posX = newX;
    posY = newY;
    }

     // Keep player inside screen bounds
     if (posX <= 0){
        posX = 0;
        Direction.x = 1;
    }
    if (posX >= GetScreenWidth() - CurrentTexture.width/2){ 
        posX = GetScreenWidth() - CurrentTexture.width/2;
        Direction.x = -1;
    }
    if (posY <= 0) {
        posY = 0;
        Direction.y *= -1;
    }
    if (posY >= GetScreenHeight() - CurrentTexture.height){
        posY = GetScreenHeight() - CurrentTexture.height;
        Direction.y *= -1;
    }


    if(Direction.x == 1 && Direction.y == 0){
        CurrentTexture = AllTextures[2];
    }

    if(Direction.x == -1 && Direction.y == 0){
        CurrentTexture = AllTextures[3];
    }

    if(Direction.x == 0 && Direction.y == 1){
        CurrentTexture = AllTextures[0];
    }

    if(Direction.x == 0 && Direction.y == -1){
        CurrentTexture = AllTextures[1];
    }
}

void Character::UpdateTexture(Texture2D *texture){
    AllTextures = texture;
}