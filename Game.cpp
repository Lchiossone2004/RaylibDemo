#include <iostream>
#include <raylib.h>
#include "raymath.h"
#include "string.h"
#include "Player.h"
#include "Enemy.h"
#include "colisionMap.h"
#define SCALE 2
using namespace std;

int **SetUpMap();
void UploadMap(int **colMap, int map[30][50]);

int main(void){   
    InitWindow(640*SCALE, 480*SCALE, "link (no zelda (nintendo no me denuncies))");
    InitAudioDevice();
    SetTargetFPS(60);

    // Load music
    Music GameplayMusic = LoadMusicStream("./Music/ZeldaMusic.mp3");
    PlayMusicStream(GameplayMusic);  // ✅ Start playing the music
    Music MenuMusic = LoadMusicStream("./Music/MenuMusic.mp3");
    PlayMusicStream(MenuMusic);  // ✅ Start playing the music

    Texture2D background = LoadTexture("./Sprites/Stage/CastleGarden.png"); 
    Texture2D PlayerMovement = LoadTexture("./Sprites/Zelda/ZeldaMovement.png");
    Texture2D WeaponH = LoadTexture("./Sprites/Weapons/Weapon.png");
    Texture2D WeaponV = LoadTexture("./Sprites/Weapons/WeaponVertical.png");
    Texture2D GuardMovement = LoadTexture("./Sprites/Enemy/GuardMovement.png");
    
    int currentFrame = 0;
    float animationSpeed = 0.4f;
    float timeCounter = 0.0f;

    //Inicializo los personajes
    Player Princes(GetScreenWidth()/2,GetScreenHeight()/2, PlayerMovement,3,4,SCALE,3);
    Enemy Knight(GetScreenWidth()/2,GetScreenHeight()/2, GuardMovement,3,4,SCALE,2);
    Knight.Direction = {1,0};

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
                DrawTextureEx(background,{0,0},0.0f,SCALE, WHITE);
            }
            if(SceneNumber == 1){  //Segunda Pantalla 
                if(!mapUploaded){
                int secondMap[30][50];
                UploadMap(collisionMap, secondMap);
                mapUploaded = true;
                }
                ClearBackground(GREEN);

            }
            if (IsKeyDown(KEY_D)) {
                Princes.Direction.x = 1;
            } if (IsKeyDown(KEY_A)) {
                Princes.Direction.x = -1;
            } if (IsKeyDown(KEY_W)) {
                Princes.Direction.y = -1;
            } if (IsKeyDown(KEY_S)) {
                Princes.Direction.y = 1;
            }
            Princes.ChangeDirection();
            Princes.Update(collisionMap, currentFrame);
            Princes.Draw();
            Princes.Direction = {0,0};
          

            //Chequeo si cambio de escenaario
            
            if (Princes.GetPosX() >= 645 && Princes.GetPosY() <= 685 && Princes.GetPosY() == 227){
                SceneNumber = 1;
                mapUploaded = false;
            }

            //Comportamiento del enemigo
            Knight.KeepInbound();
            Knight.Update(collisionMap,currentFrame);
            Knight.Draw();
        break;

        case OPTIONS:

        break;
        }
          
        EndDrawing();
    }

     //Liberamos la memeoria usada y cerrramos todo 
    UnloadTexture(background);
    UnloadTexture(PlayerMovement);
    UnloadTexture(GuardMovement);
    UnloadMusicStream(GameplayMusic);
    UnloadMusicStream(MenuMusic);
    free(collisionMap);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}

int **SetUpMap(){
    int rows = 30;
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

void UploadMap(int **colMap, int map[30][50]){
    int rows = 30;
    int cols = 50;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            colMap[i][j] = map[i][j];
        }
    }
}