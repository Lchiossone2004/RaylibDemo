// Player.h
#ifndef Player_H
#define Player_H

#include "raylib.h"
#include "Character.h"
#include "Sword.h"

class Player : public Character{
    public:
    Sword ZeldaSword;
    Player(float x, float y,Texture2D texture,int textureColums, int textureRows,int scale,int speed) : Character(x, y, texture, textureColums, textureRows, scale,speed){
    }
    void EquipSword(Sword GreatSword);
    void Move(int **map) override;
    void Draw(Color color) override;
};
#endif
