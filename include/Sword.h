#include "raylib.h"

class Sword{
    public:
    //Datos basicos
    float damage = 10;
    float attackTime = 0.5f;
    float coldown = 0.3f;
    //Forma
    Texture2D weaponTexture = LoadTexture("./Sprites/Weapons/Sword.png");
    int nSprites;
    Rectangle attackHitbox;
    void UnloadSword();
};