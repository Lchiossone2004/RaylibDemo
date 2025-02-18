#include "SetUp.h"

AllTextures LoadTextures(){
    AllTextures toRet;
    toRet.background = LoadTexture("./Sprites/Stage/CastleGarden.png"); 
    toRet.PlayerMovement = LoadTexture("./Sprites/Zelda/ZeldaMovement.png");
    toRet.GuardMovement = LoadTexture("./Sprites/Enemy/GuardMovement.png");
    return toRet;
}

AllMusic LoadMusicTracks(){
    AllMusic toRet;
    toRet.GameplayMusic = LoadMusicStream("./Music/ZeldaMusic.mp3");
    toRet.MenuMusic = LoadMusicStream("./Music/MenuMusic.mp3");
    PlayMusicStream(toRet.GameplayMusic);
    PlayMusicStream(toRet.MenuMusic);  
    return toRet;
}

void UnloadTextures(AllTextures *textures){
    UnloadTexture(textures->background);
    UnloadTexture(textures->PlayerMovement);
    UnloadTexture(textures->GuardMovement);


}
void UnloadMusicTracks(AllMusic *music){
    UnloadMusicStream(music->GameplayMusic);
    UnloadMusicStream(music->MenuMusic);
}

int ** CreateCollisionMap(){
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

void MainMenu(AllMusic music){
    UpdateMusicStream(music.MenuMusic);
    DrawText("Main Menu", GetScreenWidth()/2 - MeasureText("Main Menu", 60)/2, GetScreenHeight()/5, 60, BLACK);
    DrawText("Press ENTER to Play", GetScreenWidth()/2 - MeasureText("Press ENTER to Play", 50)/2, GetScreenHeight()/3, 50, DARKGRAY);
    DrawText("Press O for Options", GetScreenWidth()/2 - MeasureText("Press O for Options", 40)/2, GetScreenHeight()/2, 40, DARKGRAY);         
}