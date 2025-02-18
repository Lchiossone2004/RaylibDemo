#include "Game.h"

int main(void){   
    InitWindow(640*SCALE, 480*SCALE, "link (no zelda (nintendo no me denuncies))");
    InitAudioDevice();
    SetTargetFPS(60);

    AllTextures textures = LoadTextures();          //Cargo todas las texturas
    AllMusic music = LoadMusicTracks();             //Cargo la musica  
    Timer gameTimer;                                //Inicio el timer para el gameplay
    Player Princes(GetScreenWidth()/2,GetScreenHeight()/2, textures.PlayerMovement,3,4,SCALE,3);    //Inicio el Player
    Enemy Knight(GetScreenWidth()/2,GetScreenHeight()/2, textures.GuardMovement,3,4,SCALE,2);       //Cargo un enemigo 
    GameScreen currentScreen = MENU;                //Inicio las pantallas (empieza en el menu)
    int StageNumber = 0;                            //Numero de la pantalla (stage)
    int **collisionMap = CreateCollisionMap();      //Reservo lugar para el mapa de colisiones 
    bool mapUploaded = false;                       //Chequeo si se actualiza el mapa de colisiones al cambiar de escena

    while (!WindowShouldClose())
    {
        BeginDrawing();
        switch (currentScreen){
        case MENU:
            MainMenu(music);        
            if (IsKeyPressed(KEY_ENTER)) currentScreen = GAMEPLAY;
        break;
        case GAMEPLAY:
            UpdateTimer(&gameTimer.timeCounter,&gameTimer.currentFrame,gameTimer.animationSpeed);
            ChangeScene(StageNumber,music,textures,SCALE);
            UploadMap(collisionMap,StageNumber,&mapUploaded);
            MovePlayer(&Princes,collisionMap,gameTimer.currentFrame);
            if (Princes.GetPosX() >= 645 && Princes.GetPosY() <= 685 && Princes.GetPosY() == 227){
                StageNumber = 1;
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

