#include "raylib.h"
#include <unistd.h>
int main ()  {
    //windows dimension
    int width {1280}, height {720};
    InitWindow(width, height, "Mamak");
    //circle coordinates . 
    int circle_x {GetScreenWidth()/2}, circle_y = {GetScreenHeight()/2};
    //axe cordinates
    int direction {10};
    int rectangle_x {(GetScreenWidth()/2) + 100}, rectangle_y = {(GetScreenHeight()/2) + 100};
    int temp_rectangel_y = rectangle_y;
    int rectangle_lenght {50};
    int circle_radius {25};
    int escape;

    while (WindowShouldClose() == false)    
    {
        BeginDrawing();
        ClearBackground(WHITE);
        SetTargetFPS(60);
        DrawCircle(circle_x, circle_y, circle_radius, BLUE);
        DrawRectangle(rectangle_x, rectangle_y, rectangle_lenght, rectangle_lenght, RED);
        //game logic begins

        //MOVE TO AXE 
        rectangle_y += direction;
        //edges to axe
        int l_circle_x{circle_x - circle_radius};
        int r_circle_x{circle_x + circle_radius};
        int b_circle_y{circle_y + circle_radius};
        int u_circle_y{circle_y - circle_radius};
        //edges to axe
        int l_rectangle_x {rectangle_x};
        int r_rectangle_x {rectangle_x + rectangle_lenght};
        int u_rectangle_y {rectangle_y};
        int b_rectangle_y {rectangle_y + rectangle_lenght};




        if(rectangle_y > temp_rectangel_y + 150 || rectangle_y < temp_rectangel_y - 350) {
            direction  = -direction;
        }


        if(IsKeyDown(KEY_W) && circle_y < circle_y * 2) {
            circle_y = circle_y - 10;
        }else if(IsKeyDown(KEY_S) && circle_y >  0) {
            circle_y = circle_y + 10;
        }
        if(IsKeyDown(KEY_D) && circle_x < circle_x *2) {
            circle_x  = circle_x + 10;
        }else if(IsKeyDown(KEY_A) && circle_x > 0 ) {
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