#ifndef SWORD_H
#define SWORD_H
#include "raylib.h"

class Sword {
    public:
        Vector2 weaponDirection = {0,0};
        Vector2 swordPos;
        bool isAttacking;
        float attackDuration;
        float attackTimer;
        float damage = 10;
        Texture2D weaponTexture = LoadTexture("./Sprites/Weapons/Sword.png");
        float TextureWith = weaponTexture.width;
        float TextureHeigh = weaponTexture.height;
        Rectangle hitbox;
        Sword();
        void Attack();    // Start an attack
        void Update();    // Handle attack timing
        void Draw(Vector2 playerPos, float textScale); // Draw the sword
        void UnloadSword();
};
#endif