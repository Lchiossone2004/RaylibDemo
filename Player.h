// Player.h
#ifndef Player_H
#define Player_H

#include "raylib.h"

class Player {
public:
    Texture2D CharacterTexture;
    float posX, posY;
public:
    Player(float x, float y, Texture2D texture,bool attack, float atTime);
    // Initialize position variables
    void Draw();
    void ChangeDirection(float x, float y);
    void Update(Texture2D texture,int **map);
    float GetPosX();
    float GetPosY();
    bool isAtacking;
    float attackTime;
    float attackCooldown = 0;
    float attackDamage = 50;
    Rectangle attackHitbox;
    Vector2 Direction;
};

#endif
