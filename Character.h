#ifndef Character_H
#define Character_H

#include "raylib.h"

class Character {
public:
    //Data
    float posX = GetScreenWidth()/2 + 100, posY = GetScreenHeight()/2 + 100;  // Initialize position variables
    int health = 1000;
    bool inv = false;
    float invTime = 0;
    float SpeedX = 0, SpeedY = 0;
    bool isAtacking;
    float attackTime;
    float attackCooldown = 0;
    float attackDamage = 50;
    Rectangle attackHitbox;
    Texture2D CurrentTexture;
    Texture2D *AllTextures;
    Vector2 Direction;

    //Functions
    void UpdateTexture(Texture2D *texture);
    void Draw(int curentFrame);
    void Update(int **map, int currentFrame);
    void DrawHit(int curentFrame);
    void ChangeDirection(float x, float y);
};

#endif
