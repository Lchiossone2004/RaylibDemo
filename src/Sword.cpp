#include "Sword.h"


Sword::Sword() {
    isAttacking = false;
    attackDuration = 0.3f; // Attack lasts 0.3 seconds
    attackTimer = 0.0f;
}

void Sword::Attack() {
    if (!isAttacking) {
        isAttacking = true;
        attackTimer = attackDuration;
    }
}

void Sword::Update() {
    if (isAttacking) {
        attackTimer -= GetFrameTime();
        if (attackTimer <= 0) {
            isAttacking = false;
        }
    }
}

void Sword::Draw(Vector2 playerPos, float textScale) {
    if (isAttacking) {
        // Define sword size (adjust to your sprite)
        float swordWidth = TextureWith * textScale;
        float swordHeight = TextureHeigh * textScale;

        // Set sword position relative to the player
        swordPos = playerPos;
        float rotationAngle = 0.0f; // Default (right weaponDirection)

        if (weaponDirection.x > 0) { // Facing RIGHT
            swordPos.x += swordWidth*4;
            hitbox = {swordPos.x - swordWidth,swordPos.y,swordHeight,swordWidth};
            swordPos.y += swordHeight/2;
            rotationAngle = 90.0f;
        } else if (weaponDirection.x < 0) { // Facing LEFT
            swordPos.x -= swordWidth*2;
            hitbox = {swordPos.x - swordWidth*2,swordPos.y,swordHeight,swordWidth};
            swordPos.y += swordHeight/2;
            rotationAngle = -90.0f; 
        } else if (weaponDirection.y > 0) { // Facing DOWN
            swordPos.y += swordHeight*2;
            hitbox = {swordPos.x,swordPos.y - swordHeight/2,swordWidth,swordHeight};
            swordPos.x += swordWidth;
            rotationAngle = 180.0f; 
        } else if (weaponDirection.y < 0) { // Facing UP
            swordPos.y -= swordHeight;
            hitbox = {swordPos.x,swordPos.y - swordHeight,swordWidth,swordHeight};
            swordPos.x += swordWidth ;
        }
        // Draw the sword with correct scaling and rotation
        Rectangle sourceRec = { 0, 0, TextureWith, TextureHeigh };
        Rectangle destRec = { swordPos.x, swordPos.y, swordWidth, swordHeight };
        Vector2 origin = { swordWidth / 2, swordHeight / 2 }; 

        DrawTexturePro(weaponTexture, sourceRec, destRec, origin, rotationAngle, WHITE);
    }
}


void Sword::UnloadSword(){
    UnloadTexture(weaponTexture);
}

