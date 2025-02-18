#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "Player.h"
#include "SetUp.h"
#include "ColisionMap.h"

class Gameplay{
    public:
    Player Zelda;
    Gameplay(int with,int heigh, Texture2D texture, int a, int b, int scale,int c);
    void UpdatePlayer(int **collisionMap,int currentFrame);
    void UpdateTimer(float *timeCounter, int *currentFrame, float animationSpeed);
    void ChangeScene(int StageNumber, AllMusic music, AllTextures textures, int scale);
    void UploadMap(int** collisionMap,int StageNumber,bool *mapUploaded);
};
#endif