#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "Player.h"
#include "SetUp.h"
#include "ColisionMap.h"

void MovePlayer(Player *Princes,int **collisionMap,int currentFrame);
void UpdateTimer(float *timeCounter, int *currentFrame, float animationSpeed);
void ChangeScene(int StageNumber, AllMusic music, AllTextures textures, int scale);
void UploadMap(int** collisionMap,int StageNumber,bool *mapUploaded);

#endif