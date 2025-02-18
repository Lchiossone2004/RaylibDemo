#include "raylib.h"
#include "Player.h"
#include <iostream>
#define MAP_WIDTH 40
#define MAP_HEIGHT 30
#define TILE_WIDTH 16
#define TILE_HEIGHT 16  
#define STEP 5
#define SCALE 2

void Player::EquipSword(Sword GreatSword){
    ZeldaSword = GreatSword;
}
void Player::Move(int **map){
    if (IsKeyDown(KEY_D)) {
        Direction.x = 1;  
        ZeldaSword.weaponDirection = {1,0};
    } else if (IsKeyDown(KEY_A)) {
        Direction.x = -1;
        ZeldaSword.weaponDirection = {-1,0};
    } else if (IsKeyDown(KEY_W)) {
        Direction.y = -1;
        ZeldaSword.weaponDirection = {0,-1};
    } else if (IsKeyDown(KEY_S)) {
        Direction.y = 1;
        ZeldaSword.weaponDirection = {0,1};
    }
    if(IsKeyDown(KEY_SPACE)){
        ZeldaSword.Attack();
    }
    Character::Move(map);
}
void Player::Draw(){
    ZeldaSword.Draw({posX,posY},textScale);
    Character::Draw();
}