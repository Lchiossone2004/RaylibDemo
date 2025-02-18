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
        Vector2 swordPos = playerPos;

        float rotationAngle = 0.0f; // Default (right weaponDirection)

        if (weaponDirection.x > 0) { // Facing RIGHT
            swordPos.x += swordWidth*4;
            swordPos.y += swordHeight/2;
            rotationAngle = 90.0f; // No rotation
        } else if (weaponDirection.x < 0) { // Facing LEFT
            swordPos.x -= swordWidth*2;
            swordPos.y += swordHeight/2;
            rotationAngle = -90.0f; // Flip horizontally
        } else if (weaponDirection.y > 0) { // Facing DOWN
            swordPos.x += swordWidth;
            swordPos.y += swordHeight*2;
            rotationAngle = 180.0f; // Rotate downward
        } else if (weaponDirection.y < 0) { // Facing UP
            swordPos.x += swordWidth ;
            swordPos.y -= swordHeight;
        }

        // Draw the sword with correct scaling and rotation
        Rectangle sourceRec = { 0, 0, TextureWith, TextureHeigh };
        Rectangle destRec = { swordPos.x, swordPos.y, swordWidth, swordHeight };
        Vector2 origin = { swordWidth / 2, swordHeight / 2 }; // Rotate from the center

        DrawTexturePro(weaponTexture, sourceRec, destRec, origin, rotationAngle, WHITE);
    }
}


void Sword::UnloadSword(){
    UnloadTexture(weaponTexture);
}

