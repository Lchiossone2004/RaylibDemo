#include "raylib.h"
#include "Character.h"
#include <cmath> 
#include <iostream>
#define MAP_WIDTH 40
#define MAP_HEIGHT 30
#define TILE_WIDTH 16
#define TILE_HEIGHT 16  

Character::Character(float x, float y,Texture2D texture,int textureColums, int textureRows,int scale,int newstep){
    posX = x;
    posY = y;
    textScale = scale;
    step = newstep;
    MovementTexture = texture;
    TextureWith = (texture.width/textureColums);
    TextureHeigh = (texture.height/textureRows);
}

void Character::Draw(Color color) {
    Rectangle destRec = { posX, posY, TextureWith * textScale, TextureHeigh * textScale };
    Vector2 origin = { 0, 0 };
    DrawTexturePro(MovementTexture, TextureFrame, destRec, origin, 0.0f, color);
}

static bool IsSolid(int x, int y, int **map) {
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) return true; // Out of bounds = solid
    return map[y][x] == 1;
}

static void CheckDirection(Vector2 *Direction){
    float magnitude = sqrt(Direction->x * Direction->x + Direction->y * Direction->y);
    
    // Evitar dividir por 0
    if (magnitude > 0) {
        Direction->x = Direction->x / magnitude;
        Direction->y = Direction->y / magnitude;
    } else {
        Direction->x = 0;
        Direction->y = 0;
    }
}

void Character::Move(int **map) {
    CheckDirection(&Direction);
    float newX = posX + Direction.x * step;
    float newY = posY + Direction.y * step;

    // Convert new position to tile coordinates (textScaled correctly)
    int tileX1 = (newX / textScale) / TILE_WIDTH;                   // Top-left
    int tileY1 = (newY / textScale) / TILE_HEIGHT;
    int tileX2 = ((newX + TextureWith - 1) / textScale) / TILE_WIDTH;  // Top-right
    int tileY2 = ((newY + TextureHeigh - 1) / textScale) / TILE_HEIGHT;

    // Check collision with textScaled map coordinates
    if (!IsSolid(tileX1, tileY1, map) && !IsSolid(tileX2, tileY1, map) &&
        !IsSolid(tileX1, tileY2, map) && !IsSolid(tileX2, tileY2, map)) {
        // Move only if no collision
        posX = newX;
        posY = newY;
    }
    else{
        Direction.x *=-1;
        Direction.y *=-1;
    }
    // Keep Character inside screen bounds
    if (posX < 0) posX = 0;
    if (posX > GetScreenWidth() - (TextureWith * textScale)) posX = GetScreenWidth() - (TextureWith * textScale);
    if (posY < 0) posY = 0;
    if (posY > GetScreenHeight() - (TextureHeigh * textScale)) posY = GetScreenHeight() - (TextureHeigh * textScale);
}

void Character::Update(int currentFrame){
    // Update animation frame
    if (Direction.x == 1 && Direction.y == 0) {
        TextureFrame = {TextureWith * currentFrame, TextureHeigh * 0, TextureWith, TextureHeigh};
    } else if (Direction.x == -1 && Direction.y == 0) {
        TextureFrame = {TextureWith * currentFrame, TextureHeigh * 1, TextureWith, TextureHeigh};
    } else if (Direction.x == 0 && Direction.y == 1) {
        TextureFrame = {TextureWith * currentFrame, TextureHeigh * 2, TextureWith, TextureHeigh};
    } else if (Direction.x == 0 && Direction.y == -1) {
        TextureFrame = {TextureWith * currentFrame, TextureHeigh * 3, TextureWith, TextureHeigh};
    }
    
}

void Character::GetHit(){
    if(!inv){
        inv = true;
        invTime = 0.5f;
    }
    Draw(RED);
}


