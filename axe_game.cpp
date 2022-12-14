#include "raylib.h"
#include <unistd.h>
int main ()  {
    //windows dimension
    int width {1280}, height {720};
    InitWindow(width, height, "Mamak");
    //circle coordinates
    int circle_x {GetScreenWidth()/2}, circle_y = {GetScreenHeight()/2};
    int escape;

    while (WindowShouldClose() == false)    
    {
        BeginDrawing();
        ClearBackground(RED);

        //game logic begins
        SetTargetFPS(60);
        DrawCircle(circle_x, circle_y, 25.0f, BLUE);
        if(IsKeyDown(KEY_W)) {
            circle_y = circle_y - 10;
        }else if(IsKeyDown(KEY_S)) {
            circle_y = circle_y + 10;
        }
        if(IsKeyDown(KEY_D)) {
            circle_x  = circle_x + 10;
        }else if(IsKeyDown(KEY_A)) {
            circle_x = circle_x - 10; 
        }
        //game logic ends
        EndDrawing();
        escape = IsKeyPressed(KEY_ESCAPE);
        if(escape == 256)
        {
            WindowShouldClose() == true;   

        }
        
    }

    
}