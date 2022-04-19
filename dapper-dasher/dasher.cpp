#include "raylib.h"

int main()
{
    // window dimensions
    const int windowWidth{512};
    const int windowHeight{380};

    // init window
    InitWindow(windowWidth, windowHeight, "Dapper Dasher!");
    SetTargetFPS(60);
    
    // gravity
    const int gravity{1000};

    // nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebRec{0.0, 0.0, nebula.width/8, nebula.height/8 };
    Vector2 nebPos{windowWidth, windowHeight - nebRec.height};

    int nebVel{-600};

    // scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec{0,0,scarfy.width/6,scarfy.height};
    Vector2 scarfyPos{windowWidth/2 - scarfyRec.width/2, windowHeight - scarfyRec.height};

    const int jumpVel{-600};
    int velocity{0};
    bool isInAir{true};

    // animations
    int frame{};
    const float updateTime{1.0/12.0};
    float runningTime{};


    // game loop
    while (!WindowShouldClose())
    {
        // delta time
        const float dT{GetFrameTime()};

        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);
        
        // ground check
        if (scarfyPos.y >= windowHeight - scarfyRec.height)
        {   
            // rectangle is on the ground
            velocity = 0;
            isInAir = false;
        }
        else 
        {
            // rectangle is in the air
            velocity += gravity * dT;
            isInAir = true;
        }

        // check for jumping
        if (IsKeyPressed(KEY_SPACE) && !isInAir) 
        {
            velocity += jumpVel;
        }  
        // update nebula position
        nebPos.x += nebVel * dT;

        // update scarfy position
        scarfyPos.y += velocity * dT;

        if (!isInAir)
        {
            runningTime += dT;
            if (runningTime >= updateTime )
            {
                runningTime = 0;
                // update animation frame
                scarfyRec.x = frame * scarfyRec.width;
                frame++;
                if (frame > 5)
                {
                    frame = 0;
                }
            }
        }


        // draw nebula
        DrawTextureRec(nebula, nebRec, nebPos, WHITE);

        // draw scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        // stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}