#include "Game.h"

int main(void){   
    InitWindow(640*SCALE, 480*SCALE, "link (no zelda (nintendo no me denuncies))");
    InitAudioDevice();
    SetTargetFPS(60);

    AllTextures textures = LoadTextures();          //Cargo todas las texturas
    AllMusic music = LoadMusicTracks();             //Cargo la musica  
    Gameplay gameplay(GetScreenWidth()/2,GetScreenHeight()/2, textures.PlayerMovement,3,4,SCALE,3);
    Timer gameTimer;                                //Inicio el timer para el gameplay
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
            gameplay.UpdateTimer(&gameTimer.timeCounter,&gameTimer.currentFrame,gameTimer.animationSpeed);
            gameplay.ChangeScene(StageNumber,music,textures,SCALE);
            gameplay.UploadMap(collisionMap,StageNumber,&mapUploaded);
            gameplay.UpdatePlayer(collisionMap,gameTimer.currentFrame);
            //Comportamiento del enemigo
            Knight.KeepInbound();
            Knight.Update(gameTimer.currentFrame);
            Knight.Move(collisionMap);
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

