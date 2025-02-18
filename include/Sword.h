#ifndef SWORD_H
#define SWORD_H
#include "raylib.h"

class Sword {
    public:
        Vector2 weaponDirection = {0,0};
        bool isAttacking;
        float attackDuration;
        float attackTimer;
        Texture2D weaponTexture = LoadTexture("./Sprites/Weapons/Sword.png");
        float TextureWith = weaponTexture.width;
        float TextureHeigh = weaponTexture.height;
        Sword();
        void Attack();    // Start an attack
        void Update();    // Handle attack timing
        void Draw(Vector2 playerPos, float textScale); // Draw the sword
        void UnloadSword();
};
#endif