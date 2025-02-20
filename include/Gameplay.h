#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "Player.h"
#include "Enemy.h"
#include "SetUp.h"
#include "ColisionMap.h"

class Gameplay{
    public:
    Player Zelda;
    Enemy Enemies; //Por ahora es 1 despues vemos como hago si son mas
    Gameplay(int width, int height,AllTextures *textures, int a, int b, int scale, int c);
    void ChangeScene(int StageNumber, AllMusic music, AllTextures textures, int scale);
    void UpdateTimer(float *timeCounter, int *currentFrame, float animationSpeed);
    void UploadMap(int** collisionMap,int StageNumber,bool *mapUploaded);
    void UpdatePlayer(int **collisionMap,int currentFrame);
    void UpdateEnemy(int **collisionMap,int currentFrame);
    void CheckHit();
};
#endif