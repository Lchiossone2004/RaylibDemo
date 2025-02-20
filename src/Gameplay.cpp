#include "Gameplay.h"

Gameplay::Gameplay(int width, int height,AllTextures *textures, int a, int b, int scale, int c)
    : Zelda(width, height, textures->PlayerMovement, a,b, scale, c),
      Enemies(width, height, textures->GuardMovement, a, b, scale, c) {
}

void Gameplay::UpdatePlayer(int **collisionMap,int currentFrame){
    Zelda.Move(collisionMap);
    Zelda.Update(currentFrame);
    Zelda.Draw(WHITE);
    Zelda.ZeldaSword.Update();
    Zelda.Direction = {0,0};
}

void Gameplay::UpdateEnemy(int **collisionMap,int currentFrame){
    Enemies.Move(collisionMap);
    Enemies.Update(currentFrame);
    Enemies.Draw(WHITE);
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

void Gameplay::CheckHit(){
    Rectangle enemyHitbox = {Enemies.posX,Enemies.posY,Enemies.TextureWith,Enemies.TextureHeigh};
    //Rectangle weaponHitbox = {Zelda.posX,Zelda.posY,Zelda.ZeldaSword.TextureWith,Zelda.ZeldaSword.TextureHeigh};
    if(CheckCollisionRecs(Zelda.ZeldaSword.hitbox,enemyHitbox) && Zelda.ZeldaSword.isAttacking && !Enemies.inv){
        Enemies.GetHit();
        Enemies.health -= Zelda.ZeldaSword.damage;
        std::cout << "ouch" << std::endl;
    }
    if(Enemies.inv){
        Enemies.invTime -= GetFrameTime();
    }
    if(Enemies.invTime < 0){
        Enemies.inv = false;
        Enemies.invTime = 0;
        
    }
}

//Actualizo el mapa si se cambia la escena

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