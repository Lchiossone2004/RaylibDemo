#ifndef Character_H
#define Character_H

#include "raylib.h"

class Character {
    public:
    //basic presets
    int textScale;
    int step;
    float posX, posY;
    Vector2 Direction = {0,1};
    float health;
    //Texture settings
    Texture2D MovementTexture;
    Rectangle TextureFrame;
    float TextureWith;
    float TextureHeigh; 
    //Attack settings
    bool isAtacking = false;
    //Invencibility
    bool inv = false;
    float invTime = 0.0f;

public:
    Character(float x, float y,Texture2D texture,int textureColums, int textureRows, int scale, int speed);
    void Draw();
    void ChangeDirection();
    void Update(int **map,int currentFrame);
    float GetPosX();
    float GetPosY();
};

#endif
