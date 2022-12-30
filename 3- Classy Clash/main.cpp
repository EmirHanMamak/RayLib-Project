#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
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
    Prop rock{Vector2 {300.f, 300.f}, LoadTexture("nature_tileset/Rock.png")};
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // draw the map
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);
        rock.Render(knight.getWorldPos());
        knight.tick(GetFrameTime());
        // check map bounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowWidth > map.width * mapScale ||
            knight.getWorldPos().y + windowHeight > map.height * mapScale)
        {
            knight.undoMovement();
        }

        EndDrawing();
    }
    CloseWindow();
}
