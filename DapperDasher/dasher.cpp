#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main()
{
    const int windowWidth = 800, windowHeight = 400;
    // int rectangle_radius = 50;
    InitWindow(windowWidth, windowHeight, "Mamak Dasher");
    // Scrafy Frame
    int frame{};
    const float updateTime{1.0f / 12.0f};
    float runningTime{};
    // SCARFY
    Texture2D scrafy = LoadTexture("textures/scarfy.png");
    AnimData scrafyData;
    scrafyData.rec.width = scrafy.width / 6;
    scrafyData.rec.height = scrafy.height;
    scrafyData.rec.x = 0.0;
    scrafyData.rec.y = 0.0;
    scrafyData.pos.x = windowWidth / 2 - (scrafyData.rec.width / 2);
    scrafyData.pos.y = windowHeight - scrafyData.rec.height;
    scrafyData.frame = 0;
    scrafyData.updateTime = 1.0f / 12.0f;
    scrafyData.runningTime = 0.0f;

    /*Rectangle scarfyRec;
    scarfyRec.width = scrafy.width / 6;
    scarfyRec.height = scrafy.height;
    scarfyRec.x = scrafy.width / 6 * 0;
    scarfyRec.y = 0;
    Vector2 scrafyPos;
    scrafyPos.x = windowWidth / 2 - (scarfyRec.width / 2);
    scrafyPos.y = windowHeight - scrafy.height;

    // Scrafy Frame
    int nebFrame{};
    const float nebUpdateTime{1.0f / 12.0f};
    float nebRunningTime{};*/

    // Nebula
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    
    AnimData nebuladata {
        {0.0, 0.0, nebula.width / 8, nebula.height / 8}, //nebula rec
        {windowWidth + nebula.width / 8, windowHeight - nebula.height/ 8}, //nebula pos
        0, //nebula frame
        1.0f / 12.0f, //nebula updatetime
        0.0f //nebula runningtime
    };
    
        AnimData nebuladata2 {
        {0.0, 0.0, nebula.width / 8, nebula.height / 8}, //nebula2 rec
        {windowWidth + nebula.width / 8 + 300 , windowHeight - nebula.height/ 8}, //nebula2 pos
        0, //nebula2 frame
        1.0f / 12.0f, //nebula2 updatetime
        0.0f //nebula2 runningtime
    };
    int nebVel{-4};
    /*Rectangle nebRec{0.0, 0.0, nebula.width / 8, nebula.height / 8};
    // Nebula Location on the canvas
    Vector2 nebPos{windowWidth + nebRec.width, windowHeight - nebRec.height};
    */
    // Variables
    // Gravity (pixel/s) /s
    const int gravity{1'000};

    // Jump () pixels / sec
    int jumpVel{-600};
    // Velocity
    int velocity{60};
    // IsOnAir
    bool isOnAir{};
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Delta time (time since last frame)
        float dT{GetFrameTime()};
        BeginDrawing();
        ClearBackground(WHITE);
        // logical math
        if (scrafyData.pos.y >= windowHeight - scrafyData.rec.height)
        {
            velocity = 0;
            isOnAir = false;
            // scarfyRec.x = scrafy.width / 6 *0 ;
            // DrawText("gravity",150, 200, 12, RED);
        }
        else
        {
            velocity += gravity * dT;
            isOnAir = true;  
        }
        // Jump check
        if (IsKeyPressed(KEY_SPACE) && !isOnAir)
        {
            velocity += jumpVel;
            scrafyData.rec.x = scrafy.width / 6 * 2;
        }

        // UPDATE POSITION
        scrafyData.pos.y += velocity * dT;

        // Scarfy ANIMATION UPDATE
        if (!isOnAir)
        {
            runningTime += dT;
            if (runningTime >= updateTime)
            {
                runningTime = 0.0f;
                // Frame Check
                scrafyData.rec.x = frame * scrafyData.rec.width;
                frame++;
                if (frame > 5)
                {
                    frame = 0;
                }
            }
        }

        // NEBULA ANIMATION UPDATE
        nebuladata.runningTime += dT;

        if(nebuladata.runningTime >= nebuladata.updateTime) {
            nebuladata.runningTime = 0.0f;
            nebuladata.rec.x = nebuladata.frame * nebuladata.rec.width;
            nebuladata.frame++;
            if(nebuladata.frame > 7) {
                nebuladata.frame = 0;

            }
        }
        nebuladata.pos.x += nebVel;
        if(nebuladata.pos.x + nebuladata.rec.width < 0) {
            nebuladata.pos.x = windowWidth + nebuladata.rec.width;
        }
        // logical math end
        //  DrawRectangle(rectanglePosX, rectanglePosY, rectangle_radius, rectangle_radius, RED);
        DrawTextureRec(scrafy, scrafyData.rec, scrafyData.pos, WHITE);
        DrawTextureRec(nebula, nebuladata.rec, nebuladata.pos, WHITE);
        EndDrawing();
    }
    UnloadTexture(scrafy);
    UnloadTexture(nebula);
    CloseWindow();
}