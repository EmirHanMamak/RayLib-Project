#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
int main()
{
    const int windowWidth{512};
    const int windowHeight{512};
    InitWindow(windowWidth, windowHeight, "Mamak's Top Down");

    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{5.0f};
    //Character Initialize
    Character knight{windowWidth,windowHeight};
    //Prop Initialize
    Prop props[3] {
        Prop{Vector2 {300.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2 {300.f, 500.f}, LoadTexture("nature_tileset/Log.png")},
        Prop{Vector2 {500.f, 500.f}, LoadTexture("nature_tileset/Sign.png")}
        };
    //Character Enemy
    /*Texture2D enemy_texture = LoadTexture("characters/goblin_idle_spritesheet.png");
    Texture2D enemy_idle = LoadTexture("characters/goblin_idle_spritesheet.png");
    Texture2D enemy_run = LoadTexture("characters/goblin_run_spritesheet.png");
    */Enemy enemy{Vector2{},
    LoadTexture("characters/goblin_idle_spritesheet.png"), 
    LoadTexture("characters/goblin_run_spritesheet.png")};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // draw the map
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);
        //draw the props
        for(auto Prop : props) {
            Prop.Render(knight.getWorldPos());
        }
        knight.tick(GetFrameTime());
        //draw enemy
        enemy.tick(GetFrameTime());
        enemy.setTarget(&knight);

        // check map bounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowWidth > map.width * mapScale ||
            knight.getWorldPos().y + windowHeight > map.height * mapScale)
        {
            knight.undoMovement();
        }
        //Check Prop Colliange
        for(auto prop : props) {
            if(CheckCollisionRecs(prop.GetCollisionRec(knight.getWorldPos()), knight.GetCollisionRec())) {
                knight.undoMovement();
            }
        }

        EndDrawing();
    }
    CloseWindow();
}
