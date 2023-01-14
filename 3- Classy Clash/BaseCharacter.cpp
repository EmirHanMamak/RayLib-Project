#include "BaseCharacter.h"

BaseCharacter::BaseCharacter()
{
}
void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::GetCollisionRec()
{
    return Rectangle{
        screenPos.x,
        screenPos.y,
        textureWidth * scale - 5,
        textureHeight * scale + 5};
}
void BaseCharacter::tick(float deltaTime)
{
       worldPosLastFrame = worldPos;
    // update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames)
            frame = 0;
    }

    // draw the character
    Rectangle source{frame * textureWidth, 0.f, rightLeft * textureWidth, textureHeight};
    Rectangle dest{screenPos.x, screenPos.y, scale * textureWidth, scale * textureHeight};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}