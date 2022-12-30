#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight)
{
    textureWidth = (float)texture.width / 6.0f;
    textureHeight = (float)texture.height;
    screenPos = {static_cast<float>(winWidth) / 2.0f - scale * (0.5f * textureWidth),
                 static_cast<float>(winHeight) / 2.0f - scale * (0.5f * textureHeight)};
}
void Character::tick(float deltaTime)
{
    if(IsKeyDown(KEY_LEFT_SHIFT)) {
    speed = 6.0f;
    updateTime = 1.f / 12.f;
    }
    else {
    speed = 4.f;
    updateTime = 1.f / 18.f;
    }
    worldPosLastFrame = worldPos;
    Vector2 direction{};
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0;
    if (IsKeyDown(KEY_D))
        direction.x += 1.0;
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0;
    if (IsKeyDown(KEY_S))
        direction.y += 1.0; 
    if (Vector2Length(direction) != 0.0)
    {
        // set worldPos = worldPos + direction
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
        direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
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
void Character::undoMovement() {
    worldPos = worldPosLastFrame;
}