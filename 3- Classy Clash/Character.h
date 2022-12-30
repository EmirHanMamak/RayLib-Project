#include "raylib.h"

class Character
{
public:
    Vector2 getWorldPos() { return worldPos; }
    Character(int winWidth, int winHeight);
    void tick(float deltaTime);
    void undoMovement();

private:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 worldPos{};
    Vector2 screenPos{};
    Vector2 worldPosLastFrame{};
    // 1 : facing right, -1 : facing left
    float rightLeft{1.f};
    // animation variables
    float runningTime{};
    int frame{};
    float updateTime{};
    int maxFrames{6};
    float speed{};
    float textureWidth;
    float textureHeight;
    float scale{4.f};
    float movementSpeed{};
};