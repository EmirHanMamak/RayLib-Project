#include "raylib.h"

int main() {

    // window dimensions
    const int windowWidth =512;
    const int windowHeight=380;
    // setFrame 60
    SetTargetFPS(60);
    // rectange dimension
    int rectange_width{50};
    int rectange_height {80};
    int rectange_posY {windowHeight - rectange_height};

    //velocity dimension
    int velocity {0};
    // Screen
    InitWindow(windowWidth, windowHeight, "Dasher Game Mamak");
    while (!WindowShouldClose())
    {
        //start drawing
        BeginDrawing();
        ClearBackground(WHITE);
        if(IsKeyPressed(KEY_SPACE)) {
            velocity = -10;
            rectange_posY += velocity;
        }
        DrawRectangle(windowWidth / 2, rectange_posY, rectange_width, rectange_height, BLUE );
        //stop drawing
        EndDrawing();

    }
    CloseWindow();
    

}