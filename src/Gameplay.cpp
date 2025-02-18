#include "Gameplay.h"

void MovePlayer(Player *Princes,int **collisionMap,int currentFrame){
    if (IsKeyDown(KEY_D)) {
        (*Princes).Direction.x = 1;
    } if (IsKeyDown(KEY_A)) {
        (*Princes).Direction.x = -1;
    } if (IsKeyDown(KEY_W)) {
        (*Princes).Direction.y = -1;
    } if (IsKeyDown(KEY_S)) {
        (*Princes).Direction.y = 1;
    }
    Princes->ChangeDirection();
    Princes->Update(collisionMap, currentFrame);
    Princes->Draw();
    Princes->Direction = {0,0};
}

void UpdateTimer(float *timeCounter, int *currentFrame, float animationSpeed){
    *timeCounter += GetFrameTime();
    if (*timeCounter >= animationSpeed)
    {
        *currentFrame = (*currentFrame + 1) % 3;
        *timeCounter = 0.0f;
    }
}

void ChangeScene(int StageNumber, AllMusic music, AllTextures textures, int scale){
    if(StageNumber == 0){   //Primera Pantalla
        UpdateMusicStream(music.GameplayMusic); 
        DrawTextureEx(textures.background,{0,0},0.0f,scale, WHITE);
    }
    if(StageNumber == 1){  //Segunda Pantalla 
        ClearBackground(GREEN);

    }
}
void UploadMap(int** collisionMap,int StageNumber,bool *mapUploaded){             //Mejorar esto!!
    if(!*mapUploaded){
    if(StageNumber == 0){
        int rows = 30;
        int cols = 50;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                collisionMap[i][j] = scene1[i][j];
         }
     }
     *mapUploaded = true;
    }
    if(StageNumber == 1){
        int rows = 30;
        int cols = 50;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                collisionMap[i][j] = scene2[i][j];
        }
    }
     *mapUploaded = true;
    }
}
}