//  Enemy.h
#ifndef Enemy_H
#define Enemy_H

#include "raylib.h"
#include "Character.h"

class Enemy : public Character{
public:
    void Speed(float x, float y);
};

#endif
