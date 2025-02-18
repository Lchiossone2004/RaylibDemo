#include "Gameplay.h"

Gameplay::Gameplay(int with,int heigh, Texture2D texture, int a, int b, int scale,int c)
    :Zelda(with,heigh,texture,a,b,scale,c){
}

void Gameplay::UpdatePlayer(int **collisionMap,int currentFrame){
    Zelda.Move(collisionMap);
    Zelda.Update(currentFrame);
    Zelda.Draw();
    Zelda.ZeldaSword.Update();
    Zelda.Direction = {0,0};
}

void Gameplay::UpdateTimer(float *timeCounter, int *currentFrame, float animationSpeed){
    *timeCounter += GetFrameTime();
    if (*timeCounter >= animationSpeed)
    {
        *currentFrame = (*currentFrame + 1) % 3;
        *timeCounter = 0.0f;
    }
}

void Gameplay::ChangeScene(int StageNumber, AllMusic music, AllTextures textures, int scale){
    if(StageNumber == 0){   //Primera Pantalla
        UpdateMusicStream(music.GameplayMusic); 
        DrawTextureEx(textures.background,{0,0},0.0f,scale, WHITE);
    }
    if(StageNumber == 1){  //Segunda Pantalla 
        ClearBackground(GREEN);

    }
}
void Gameplay::UploadMap(int** collisionMap,int StageNumber,bool *mapUploaded){             //Mejorar esto!!
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