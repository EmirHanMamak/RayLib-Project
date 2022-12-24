#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};
bool isOnGround(AnimData data, int windowDimensions);
AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame);
int main()
{
    int windowDimensions[2] {{512},{380}};
    // int rectangle_radius = 50;
    InitWindow(windowDimensions[0], windowDimensions[1], "Mamak Dasher");
    // SCARFY
    Texture2D scrafy = LoadTexture("textures/scarfy.png");
    AnimData scrafyData;
    scrafyData.rec.width = scrafy.width / 6;
    scrafyData.rec.height = scrafy.height;
    scrafyData.rec.x = 0.0;
    scrafyData.rec.y = 0.0;
    scrafyData.pos.x = windowDimensions[0] / 2 - (scrafyData.rec.width / 2);
    scrafyData.pos.y = windowDimensions[1] - scrafyData.rec.height;
    scrafyData.frame = 0;
    scrafyData.updateTime = 1.0f / 12.0f;
    scrafyData.runningTime = 0.0f;

    // Nebula
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    const int sizeOfNebulae {3};
        AnimData nabulae[sizeOfNebulae]{};
        for(int i = 0 ; i < sizeOfNebulae ; i++) {
            //nebula same rectangels
            nabulae[i].rec.x = 0;
            nabulae[i].rec.y = 0;
            nabulae[i].rec.width = nebula.width / 8;
            nabulae[i].rec.height = nebula.height / 8;
            //nebula pos
            nabulae[i].pos.y = windowDimensions[1] - nebula.height/ 8;
            nabulae[i].frame = 0;
            nabulae[i].runningTime = 0.0f;
            nabulae[i].updateTime = 1.0f / 12.0f;
            nabulae[i].pos.x = windowDimensions[0] + nebula.width / 8 + i * 300;

        }
    // Variables
    int nebVel{-4};
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
        if (isOnGround(scrafyData, windowDimensions[1]))
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
        }

        // UPDATE POSITION
        scrafyData.pos.y += velocity * dT;

        // Scarfy ANIMATION UPDATE
        if (!isOnAir)
        {
            scrafyData = updateAnimData(scrafyData, dT, 5);
        }

        // NEBULA ANIMATION UPDATE
        for(int i = 0; i < sizeOfNebulae; i++) {
            nabulae[i] = updateAnimData(nabulae[i], dT, 8);
            nabulae[i].pos.x += nebVel;
        }


        // logical math end
        //DRAWING OBJECTS
        DrawTextureRec(scrafy, scrafyData.rec, scrafyData.pos, WHITE);
        for(int i = 0 ; i < sizeOfNebulae ; i++) {
             DrawTextureRec(nebula, nabulae[i].rec, nabulae[i].pos, WHITE);
        }
        //END OF DRAWING
        EndDrawing();
    }
    //UNLOAD TEXTURES
    UnloadTexture(scrafy);
    UnloadTexture(nebula);
    //CLOSE WINDOW
    CloseWindow();
}


//IS ON GROUND CHECK
bool isOnGround(AnimData data, int windowDimensions) {
    return data.pos.y >= windowDimensions - data.rec.height;

}
//Animation UPDATE
AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame) {
    data.runningTime += deltaTime;
    if(data.runningTime >= data.updateTime) {
        data.runningTime = 0.0f;
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if(data.frame > maxFrame) {
            data.frame = 0;
        }
    }
    return data;
}