#include "raylib.h"

int main() {
    int windowsDimensions[2];
    windowsDimensions[0] = 384;
    windowsDimensions[1] = 384;
    // Create Canvas
    InitWindow(windowsDimensions[0], windowsDimensions[1],"Classy Clash Mamak");

    // MAP LOAD
    Texture2D mapTexture = LoadTexture("nature_tileset/OpenWorldMap24x24.png");

    //fps limiter
    SetTargetFPS(60);
    //game loop
    while(!WindowShouldClose()) {
        //deta time
        //float dT = GetFrameTime();
        BeginDrawing();
        ClearBackground(WHITE);
        // Draw map
        Vector2 mapPos {0.0f, 0.0f};
        DrawTextureEx(mapTexture, mapPos, 0.0f, 4.0f, WHITE);
        EndDrawing();

    }
    UnloadTexture(mapTexture);

}