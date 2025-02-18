#include "Game.h"

#define SCALE 2

int main(void){   
    InitWindow(640*SCALE, 480*SCALE, "link (no zelda (nintendo no me denuncies))");
    InitAudioDevice();
    SetTargetFPS(60);

    AllTextures textures = LoadTextures();          //Cargo todas las texturas
    AllMusic music = LoadMusicTracks();             //Cargo la musica
    
    Timer gameTimer;

    //Inicializo los personajes
    Player Princes(GetScreenWidth()/2,GetScreenHeight()/2, textures.PlayerMovement,3,4,SCALE,3);
    Enemy Knight(GetScreenWidth()/2,GetScreenHeight()/2, textures.GuardMovement,3,4,SCALE,2);


    //Inicializo las pantallas
    GameScreen currentScreen = MENU; //Arranca en la de menu

    //SceneNumber
    int SceneNumber = 0;
    int **collisionMap = CreateCollisionMap();
    bool mapUploaded = false;

    while (!WindowShouldClose())
    {
        
        BeginDrawing();

        ClearBackground(GREEN);

        switch (currentScreen){
        
        case MENU:
            MainMenu(music);        
            if (IsKeyPressed(KEY_ENTER)) currentScreen = GAMEPLAY;
        break;

        case GAMEPLAY:
            UpdateTimer(&gameTimer.timeCounter,&gameTimer.currentFrame,gameTimer.animationSpeed);
            ChangeScene(SceneNumber,music,textures,SCALE);
            UploadMap(collisionMap,SceneNumber,mapUploaded);
            MovePlayer(&Princes,collisionMap,gameTimer.currentFrame);
          

            //Chequeo si cambio de escenaario
            
            if (Princes.GetPosX() >= 645 && Princes.GetPosY() <= 685 && Princes.GetPosY() == 227){
                SceneNumber = 1;
                mapUploaded = false;
            }

            //Comportamiento del enemigo
            Knight.KeepInbound();
            Knight.Update(collisionMap,gameTimer.currentFrame);
            Knight.Draw();
        break;

        case OPTIONS:

        break;
        }
          
        EndDrawing();
    }

     //Liberamos la memeoria usada y cerrramos todo 
    UnloadTextures(&textures);
    UnloadMusicTracks(&music);
    free(collisionMap);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}

