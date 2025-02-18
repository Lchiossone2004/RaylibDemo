#ifndef SETUP_H
#define SETUP_H

#include"raylib.h"
#include "iostream"
struct AllTextures{
    Texture2D background;
    Texture2D PlayerMovement;
    Texture2D WeaponH;
    Texture2D WeaponV;
    Texture2D GuardMovement;
};
struct AllMusic{
    Music GameplayMusic;
    Music MenuMusic;
};
AllTextures LoadTextures();
AllMusic LoadMusicTracks();
void UnloadTextures(AllTextures *textures);
void UnloadMusicTracks(AllMusic *music);
int ** CreateCollisionMap();
void MainMenu(AllMusic music);

#endif