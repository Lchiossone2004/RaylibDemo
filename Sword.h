#include "raylib.h"

class Sword{
    //Datos basicos
    float damage;
    float attackTime;
    float coldown;
    //Forma
    Texture2D weaponTexture;
    int nSprites;
    Rectangle attackHitbox;
};