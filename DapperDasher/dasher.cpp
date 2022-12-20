#include "raylib.h"

int main()
{
    const int windowWidth = 512, windowHeight = 380;
    //int rectangle_radius = 50;
    InitWindow(windowWidth, windowHeight, "Mamak Dasher");
    // Rectangle just for start sesion

    //int recPosY;
    //int rectanglePosX = 
    //int rectanglePosY = windowHeight - rectangle_radius;

    //SCARFY
    Texture2D scrafy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scrafy.width / 6;
    scarfyRec.height = scrafy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scrafyPos;
    scrafyPos.x = windowWidth / 2 - (scarfyRec.width / 2); 
    scrafyPos.y = windowHeight - scrafy.height;

    // Variables
    // Gravity
    const int gravity {1};

    // Jump ()
    int jumpVel {-22};
    // Velocity
    int velocity {0};
    //IsOnAir
    bool isOnAir {};
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        // logical math
        if( scrafyPos.y > windowHeight - scarfyRec.height ) {
            velocity = 0;
            isOnAir = false;
            //DrawText("gravity",150, 200, 12, RED);
        }else
         {
            velocity += gravity;
            isOnAir = true;
         }
        // Jump check
        if (IsKeyPressed(KEY_SPACE) && !isOnAir)
        {
            velocity += jumpVel;
        }

        // UPDATE POSITION
        scrafyPos.y += velocity;
        // logical math end
      //  DrawRectangle(rectanglePosX, rectanglePosY, rectangle_radius, rectangle_radius, RED);
        DrawTextureRec(scrafy, scarfyRec, scrafyPos, WHITE);
        EndDrawing();
    }
    UnloadTexture(scrafy);
    CloseWindow();
}