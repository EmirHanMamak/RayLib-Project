#include "raylib.h"

int main() {
    const int Winwidth{1280}, Winheight{720};
    InitWindow(Winwidth, Winheight, "Mamak Dasher Try");
    //Gravity
    const int  gravity {1};

    //RECTANGLE
    int rectange_width{50};
    int rectange_height {80};
    
    //isAir
    bool isInAir {};

    // Jump
    const int jumVel {-22};

    //rectangle pos
        int rectange_posY {Winheight - rectange_height};

        //Velocity 
    int veloCity {0};

    SetTargetFPS(60);
    while (!WindowShouldClose())

    {
        BeginDrawing();
        ClearBackground(WHITE);
                // logical operations mathematical operations

                if(rectange_posY >= Winwidth - rectange_height) {
                    veloCity = 0;
                    isInAir = false;
                }else {
                    veloCity += gravity;
                    isInAir = true;
                }
            //Key Setup
            if(IsKeyPressed(KEY_SPACE) && !isInAir) {
                veloCity += jumVel; 
            }
                //Update Position
        rectange_posY += veloCity;

        DrawRectangle(Winwidth / 2, rectange_posY, rectange_width, rectange_height, RED);
        EndDrawing();
    }
    CloseWindow();
}