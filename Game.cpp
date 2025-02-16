#include <iostream>
#include <raylib.h>
#include "raymath.h"
#include "string.h"
#include "Player.h"
#include "Enemy.h"
#include "colisionMap.h"
using namespace std;

int **SetUpMap();
void UploadMap(int **colMap, int map[38][50]);

int main(void){   
    InitWindow(1390, 1064, "link (no zelda (nintendo no me denuncies))");
    InitAudioDevice();
    SetTargetFPS(60);

    // Load music
    Music GameplayMusic = LoadMusicStream("./Music/ZeldaMusic.mp3");
    PlayMusicStream(GameplayMusic);  // ✅ Start playing the music
    Music MenuMusic = LoadMusicStream("./Music/MenuMusic.mp3");
    PlayMusicStream(MenuMusic);  // ✅ Start playing the music

    // Load Player sprites
    Texture2D Front[2] = {LoadTexture("./Sprites/Zelda/ZeldaFront1.png"),LoadTexture("./Sprites/Zelda/ZeldaFront2.png")};
    Texture2D Left[2] = {LoadTexture("./Sprites/Zelda/ZeldaLeft1.png"),LoadTexture("./Sprites/Zelda/ZeldaLeft2.png")};
    Texture2D Back[2] = {LoadTexture("./Sprites/Zelda/ZeldaBack1.png"),LoadTexture("./Sprites/Zelda/ZeldaBack2.png")};
    Texture2D Right[2] = {LoadTexture("./Sprites/Zelda/ZeldaRight1.png"),LoadTexture("./Sprites/Zelda/ZeldaRight2.png")};
    Texture2D background = LoadTexture("./Sprites/Stage/Garden.png"); 
    Texture2D WeaponH = LoadTexture("./Sprites/Weapons/Weapon.png");
    Texture2D WeaponV = LoadTexture("./Sprites/Weapons/WeaponVertical.png");
    Texture2D Soldier[4] = {LoadTexture("./Sprites/Enemy/SoldierFront.png"),LoadTexture("./Sprites/Enemy/SoldierBack.png"),LoadTexture("./Sprites/Enemy/SoldierRight.png"),LoadTexture("./Sprites/Enemy/SoldierLeft.png")};

    
    int currentFrame = 0;
    float animationSpeed = 0.4f;
    float timeCounter = 0.0f;

    //Inicializo los personajes
    Player Princes(GetScreenWidth()/2,GetScreenHeight()/2, Front[0],false,0.0f);
    Enemy Knight;
    Knight.UpdateTexture(Soldier);
    Knight.Direction = {0,1};

    //Inicializo las pantallas
    typedef enum { MENU, GAMEPLAY, OPTIONS } GameScreen;
    GameScreen currentScreen = MENU; //Arranca en la de menu

    //SceneNumber
    int SceneNumber = 0;
    //Mapa de Colisiones
    int **collisionMap = SetUpMap();
    bool mapUploaded = false;

    while (!WindowShouldClose())
    {
        
        BeginDrawing();

        ClearBackground(GREEN);

        switch (currentScreen){
        
        case MENU:
            UpdateMusicStream(MenuMusic);
            DrawText("Main Menu", GetScreenWidth()/2 - MeasureText("Main Menu", 60)/2, GetScreenHeight()/5, 60, BLACK);
            DrawText("Press ENTER to Play", GetScreenWidth()/2 - MeasureText("Press ENTER to Play", 50)/2, GetScreenHeight()/3, 50, DARKGRAY);
            DrawText("Press O for Options", GetScreenWidth()/2 - MeasureText("Press O for Options", 40)/2, GetScreenHeight()/2, 40, DARKGRAY);            
            if (IsKeyPressed(KEY_ENTER)) currentScreen = GAMEPLAY;
        break;

        case GAMEPLAY:

            timeCounter += GetFrameTime();
            if (timeCounter >= animationSpeed)
            {
                currentFrame = (currentFrame + 1) % 2;
                timeCounter = 0.0f;
            }
            if(SceneNumber == 0){   //Primera Pantalla
                if(!mapUploaded){
                    UploadMap(collisionMap, Scene1Map);
                    mapUploaded = true;
                }
                UpdateMusicStream(GameplayMusic); 
                DrawTexture(background, 0, 0, WHITE);
            }
            if(SceneNumber == 1){  //Segunda Pantalla 
                if(!mapUploaded){
                int secondMap[38][50];
                UploadMap(collisionMap, secondMap);
                mapUploaded = true;
                }
                ClearBackground(GREEN);

            }
            if(IsKeyDown(KEY_D)){ //Moverse hacia la derecha 
                Princes.Direction  ={1,0};
               Princes.Update(Right[currentFrame],collisionMap);
            }
            else if(IsKeyDown(KEY_A)){ //Moverse hacia la izquierda
                Princes.Direction  ={-1,0};
                Princes.Update(Left[currentFrame],collisionMap);
            }
            else if(IsKeyDown(KEY_W)){ //Moverse hacia arriba
                Princes.Direction  ={0,-1};
                Princes.Update(Back[currentFrame],collisionMap);
            }
            else if(IsKeyDown(KEY_S)){ //Moverse hacia abajo 
                Princes.Direction  ={0,1};
                Princes.Update(Front[currentFrame],collisionMap);
            }
            Princes.Draw();
            if(IsKeyDown(KEY_SPACE) && !Princes.isAtacking && Princes.attackCooldown == 0){ //Ataque basico 
                Princes.isAtacking = true;
                Princes.attackTime = 0.2f;
                Princes.attackHitbox = (Rectangle){Princes.GetPosX() + 20*Princes.Direction.x, Princes.GetPosY(), 50,50};
            }
            if (Princes.isAtacking) {  
                Princes.attackTime -= GetFrameTime();  
                if (Princes.attackTime <= 0) {  
                    Princes.attackCooldown = 0.5f;
                    Princes.isAtacking = false;  
                }  
            }
            if(Princes.attackCooldown < 0){
                Princes.attackCooldown = 0;
            }
            else if(Princes.attackCooldown != 0){
        
                Princes.attackCooldown -= GetFrameTime();  
            }
            DrawTexture(Princes.CharacterTexture, Princes.GetPosX(), Princes.GetPosY(), WHITE);

            if (Princes.isAtacking && Princes.attackCooldown == 0) {
                if(Princes.Direction.x != 0){
                Vector2 weaponPos = {Princes.GetPosX() + 50*Princes.Direction.x, Princes.GetPosY() + 25};
               DrawTexture(WeaponH,weaponPos.x,weaponPos.y,WHITE);  // Dibujar hitbox de ataque para depuración
                }
                if(Princes.Direction.y != 0){
                    Vector2 weaponPos = {Princes.GetPosX() + 25, Princes.GetPosY() + 50*Princes.Direction.y};
                   DrawTexture(WeaponV,weaponPos.x,weaponPos.y,WHITE);  // Dibujar hitbox de ataque para depuración
                    }
            }

            //Chequeo si cambio de escenaario
            
            if (Princes.GetPosX() >= 645 && Princes.GetPosY() <= 685 && Princes.GetPosY() == 227){
                SceneNumber = 1;
                mapUploaded = false;
            }

            //Comportamiento del enemigo

            //Chequeo la colision entre el ataque y el enemigo
            if(CheckCollisionRecs({Knight.posX,Knight.posY,(float)Knight.CurrentTexture.width/2,(float)Knight.CurrentTexture.height},Princes.attackHitbox) && Princes.isAtacking && !Knight.inv){
                Knight.health -= Princes.attackDamage;
                Knight.ChangeDirection(Princes.Direction.x,Princes.Direction.y);
                Knight.inv = true;
                Knight.invTime = 0.5f;
            }
            if (Knight.inv) {  
                Knight.invTime -= GetFrameTime();  
                if (Knight.invTime <= 0) {  
                    Knight.inv = false; 
                    Knight.Speed(0,0);
                    Knight.Draw(currentFrame);
                }  
                Knight.DrawHit(currentFrame);
            }
            if(!Knight.inv && Knight.health >0){
                Knight.Draw(currentFrame);
            }
            Knight.Update(collisionMap,currentFrame);

        break;

        case OPTIONS:

        break;
        }
          
        EndDrawing();
    }

     //Liberamos la memeoria usada y cerrramos todo 
    UnloadTexture(background);
    for(int i = 0; i<2; i ++){
        UnloadTexture(Front[i]);
        UnloadTexture(Back[i]);
        UnloadTexture(Right[i]);
        UnloadTexture(Left[i]);
    }
    for(int i = 0; i<4; i ++){
        UnloadTexture(Soldier[i]);
    }

    UnloadMusicStream(GameplayMusic);
    UnloadMusicStream(MenuMusic);
    free(collisionMap);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}

int **SetUpMap(){
    int rows = 38;
    int cols = 50;

    // Allocate an array of int* (for each row)
    int **colMap = (int **)malloc(rows * sizeof(int *));

    // Allocate an array of ints for each row
    for (int i = 0; i < rows; i++) {
        colMap[i] = (int *)malloc(cols * sizeof(int));
    }

    // Example: Initialize all elements to 0
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            colMap[i][j] = 0;
        }
    }
    return colMap;
}

void UploadMap(int **colMap, int map[38][50]){
    int rows = 38;
    int cols = 50;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            colMap[i][j] = map[i][j];
        }
    }
}