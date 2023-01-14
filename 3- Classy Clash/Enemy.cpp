#include "Enemy.h"
#include "raymath.h"
Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture) 
{
    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    textureWidth = (float)texture.width / 6.0f;
    textureHeight = (float)texture.height;
    speed = 3.f;
}
void Enemy::tick(float deltaTime) {
    //get to toTarget
    Vector2 toTarget = Vector2Subtract(target->getScreenPos(), screenPos);
    //normalize toTarget
    toTarget = Vector2Normalize(toTarget);
    //multipy to target
    toTarget = Vector2Scale(toTarget, speed);
    //move to enemy
    worldPos = Vector2Add(worldPos, toTarget);
    screenPos = Vector2Subtract(worldPos, target->getWorldPos());
        BaseCharacter::tick(deltaTime);
}