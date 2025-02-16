#include "raylib.h"
#include "Player.h"
#define MAP_WIDTH 50
#define MAP_HEIGHT 38
#define TILE_WIDTH 28
#define TILE_HEIGHT 28  
#define STEP 5

Player::Player(float x, float y, Texture2D texture, bool attack, float atTime){
    posX = x;
    posY = y;
    CharacterTexture = texture;
    isAtacking = attack;
    attackTime = atTime;

}
void Player::Draw() {
    DrawTexture(CharacterTexture,posX,posY,WHITE);
}

static bool IsSolid(int x, int y, int **map) {
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) return true; // Out of bounds = solid
    return map[y][x] == 1;
}


void Player::ChangeDirection(float x, float y){
    Direction.x = x;
    Direction.y = y;
}

void Player::Update(Texture2D texture,int **map) {
    float newX = posX + Direction.x*STEP;
    float newY = posY + Direction.y*STEP;
    CharacterTexture = texture;

    // Convert new position to tile coordinates
    int tileX1 = newX / TILE_WIDTH;                   // Top-left
    int tileY1 = newY / TILE_HEIGHT;
    int tileX2 = (newX + texture.width - 1) / TILE_WIDTH;  // Top-right
    int tileY2 = (newY + texture.height - 1) / TILE_HEIGHT;

    // Check all corners for collision
    if (!IsSolid(tileX1, tileY1,map) && !IsSolid(tileX2, tileY1,map) &&
        !IsSolid(tileX1, tileY2,map) && !IsSolid(tileX2, tileY2,map)) {
        // Only move if no collision
        posX = newX;
        posY = newY;
    }

    // Keep player inside screen bounds
    if (posX < 0) posX = 0;
    if (posX > GetScreenWidth() - texture.width) posX = GetScreenWidth() - texture.width;
    if (posY < 0) posY = 0;
    if (posY > GetScreenHeight() - texture.height) posY = GetScreenHeight() - texture.height;
}

float Player::GetPosX(){ return posX;}
float Player::GetPosY(){return posY;}