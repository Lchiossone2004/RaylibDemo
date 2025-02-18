#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <raylib.h>
#include "raymath.h"
#include "string.h"
#include "Player.h"
#include "Enemy.h"
#include "Sword.h"
#include "Gameplay.h"
#include "SetUp.h"

typedef enum { MENU, GAMEPLAY, OPTIONS } GameScreen;
struct Timer{
    int currentFrame = 0;
    float animationSpeed = 0.4f;
    float timeCounter = 0.0f;
};
#endif