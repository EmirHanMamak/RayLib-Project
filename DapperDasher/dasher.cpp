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

    // Nebula DATA
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
            // SCARFY DATA
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
        //finishline
        float finishLine {nabulae[sizeOfNebulae - 1].pos.x + 10};
        // BACKGROUND DATA
        Texture2D backGround = LoadTexture("textures/far-buildings.png");
        float bgX {};
        Texture2D foreGround = LoadTexture("textures/foreground.png");
        float fgX {};
        Texture2D midGround = LoadTexture("textures/back-buildings.png");
        float mgX {};
    // Variables
    int nebVel{-200};
    // Gravity (pixel/s) /s
    const int gravity{1'000};

    // Jump () pixels / sec
    int jumpVel{-600};
    // Velocity
    int velocity{60};
    // IsOnAir
    bool isOnAir{};
    //collisions
    bool collision {};
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Delta time (time since last frame)
        float dT{GetFrameTime()};
        BeginDrawing();
        ClearBackground(WHITE);
        //background positions
        bgX -= 80 * dT;
        Vector2 bg1Pos {bgX, 0.0f};
        Vector2 bg2Pos {bgX + backGround.width * 2, 0.0f};

        //foreground positions
        fgX -= 80 *dT;
        Vector2 fg1Pos {fgX, 0.0f};
        Vector2 fg2Pos {fgX + foreGround.width * 2, 0.0f};
        
        //midground positions
        mgX -= 80 *dT;
        Vector2 mg1Pos {mgX, 0.0f};
        Vector2 mg2Pos {mgX + midGround.width * 2, 0.0f};
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
        finishLine += nebVel *dT;
        // Scarfy ANIMATION UPDATE
        if (!isOnAir)
        {
            scrafyData = updateAnimData(scrafyData, dT, 5);
        }

        // NEBULA ANIMATION UPDATE
        for(int i = 0; i < sizeOfNebulae; i++) {
            nabulae[i] = updateAnimData(nabulae[i], dT, 8);
            nabulae[i].pos.x += nebVel* dT;
        }

        //update finihline

        // logical math end
        //DRAWING OBJECTS

        //draw background
        if(bgX <= -backGround.width * 2 + 1) {
            bgX = 0.0f;
        }
        DrawTextureEx(backGround, bg1Pos, 0.0f, 2.0f, WHITE);
        DrawTextureEx(backGround, bg2Pos, 0.0f, 2.0f, WHITE);

        //draw midGround
        if(mgX <= -midGround.width * 2 + 1) {
            mgX = 0.0f;
        }
        DrawTextureEx(midGround, mg1Pos, 0.0f, 2.0f, WHITE);
        DrawTextureEx(midGround, mg2Pos, 0.0f, 2.0f, WHITE);

        //draw foreGround
        if(fgX <= -foreGround.width * 2 + 1) {
            fgX = 0.0f;
        }
        DrawTextureEx(foreGround, fg1Pos, 0.0f, 2.0f, WHITE);
        DrawTextureEx(foreGround, fg2Pos, 0.0f, 2.0f, WHITE);
        //draw nebulaes 
        for(int i = 0 ; i < sizeOfNebulae ; i++) {
             DrawTextureRec(nebula, nabulae[i].rec, nabulae[i].pos, WHITE);
        }

        for(AnimData nebulas : nabulae) {
            int pad {20};
            Rectangle nebRec {
                nebulas.pos.x + 2* pad ,
                nebulas.pos.y + pad,
                nebulas.rec.width - 5 * pad,
                nebulas.rec.height -5 * pad
            
            };            
            Rectangle scarfyRec {
                //no need make collision box smaller cause of image already dosn't have padding
                scrafyData.pos.x,
                scrafyData.pos.y,
                scrafyData.rec.width,
                scrafyData.rec.height

            };
            if(CheckCollisionRecs(nebRec, scarfyRec)) {
                collision = true;
            }
        }
        if(collision) {
            DrawText("Game Over", windowDimensions[0] / 2 - 50,windowDimensions[1] / 2, 30,RED);
        }
        else if(scrafyData.pos.x >= finishLine){
            DrawText("YOU WIN", windowDimensions[0] / 2 - 50,windowDimensions[1] / 2, 30,YELLOW);
            }
        else {
        //draw scarfy
        DrawTextureRec(scrafy, scrafyData.rec, scrafyData.pos, WHITE);
        }
        //END OF DRAWING
        EndDrawing();
    }
    //UNLOAD TEXTURES
    UnloadTexture(scrafy);
    UnloadTexture(nebula);
    UnloadTexture(backGround);
    UnloadTexture(foreGround);
    UnloadTexture(midGround);
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