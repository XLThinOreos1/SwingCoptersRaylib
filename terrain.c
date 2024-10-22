#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "data.h"

#define PIPE_SPEED 170.0f
#define PIPE_WIDTH_VARIANCE 500.0f

Texture2D bgTexture, bgTextureInf, pipeT, playerTexture;
sPipe pipes[10];

float distTrav;
float timeTrav;

void InitTextures(void);
void InitTerrain(void);
void TerrainReset(void);
void DrawTerrain(void);
void TerrainUpdate(float deltaTime);
float GetPipeRandomWidth(void);

void InitTextures(void)
{
    Image bgImage = LoadImage("assets/background.png");
    Image bgImageInf = LoadImage("assets/endless-background.png");
    Image playerSprite = LoadImage("assets/ufo.png");
    Image pipe = LoadImage("assets/pipe.png");

    // Image pipe = LoadImage("assets/Tiles/tile_0109.png");
    // Image pipeLeft = LoadImage("assets/Tiles/tile_0111.png");
    // Image pipeRight = LoadImage("assets/Tiles/tile_0108.png");

    ImageResize(&pipe, 600, 32);

    bgTexture = LoadTextureFromImage(bgImage);
    bgTextureInf = LoadTextureFromImage(bgImageInf);
    playerTexture = LoadTextureFromImage(playerSprite);
    pipeT = LoadTextureFromImage(pipe);
}

void InitTerrain(void)
{
    for (int i = 0; i < 10; i++)
    {
        float randomWidth = GetPipeRandomWidth();

        pipes[i].position = (Vector2){i * 400.0f + 800.0f, randomWidth};
        pipes[i].collisionLeft = (Rectangle){pipes[i].position.x - 32.0f, pipes[i].position.y - 900.0f, 128.0f, 768.0f};
        pipes[i].collisionRight = (Rectangle){pipes[i].position.x - 32.0f, pipes[i].position.y + 168.0f, 128.0f, 768.0f};
    }
}

void TerrainReset(void)
{
    distTrav = 50.0f;

    for (int i = 0; i < 10; i++)
    {
        float randomWidth = GetPipeRandomWidth();
        pipes[i].position = (Vector2){i * 400.0f + 800.0f, randomWidth};
        pipes[i].collisionLeft = (Rectangle){pipes[i].position.x - 64.0f, pipes[i].position.y - 400.0f, 128.0f, 200.0f};  // 900.0f, 128.0f, 768.0f
        pipes[i].collisionRight = (Rectangle){pipes[i].position.x - 64.0f, pipes[i].position.y + 168.0f, 128.0f, 200.0f}; // 168.0f, 128.0f, 768.0f}
    }
}

void DrawTerrain(void)
{
    // Draw Pipes
    for (int i = 0; i < 10; i++)
    {
        DrawTexture(pipeT, pipes[i].collisionLeft.x, pipes[i].collisionLeft.y, RAYWHITE);
        DrawTexture(pipeT, pipes[i].collisionRight.x, pipes[i].collisionRight.y, RAYWHITE);
        // Debug
        // DrawRectangleLinesEx(pipes[i].collTop, 3.0f, RED);
        // DrawRectangleLinesEx(pipes[i].collBottom, 3.0f, RED);
    }
}

void TerrainUpdate(float deltaTime)
{
    for (int i = 0; i < 10; i++)
    {
        // Move each pipe
        pipes[i].position.y += (PIPE_SPEED * deltaTime);
        // Move pipes over as new ones if they are outside range
        if (pipes[i].position.y > player.position.y + 200.0f)
        {
            pipes[i].position.y += player.position.y - 1000.0f;
            pipes[i].position.x = GetPipeRandomWidth();
        }
        // Move colliders along with position
        pipes[i].collisionLeft = (Rectangle){pipes[i].position.x - 64.0f, pipes[i].position.y - 900.0f, 128.0f, 768.0f};
        pipes[i].collisionRight = (Rectangle){pipes[i].position.x - 64.0f, pipes[i].position.y + 168.0f, 128.0f, 768.0f};
    }
    DrawTerrain();
    // Keep score as pass pipes
    distTrav += PIPE_SPEED * deltaTime;
    if (distTrav >= 400.0f)
    {
        score += 10;
        distTrav = 0.0f;
    }
    timeTrav += deltaTime;
    if (timeTrav >= 1.0f)
    {
        timeTrav = 0.0f;
        score++;
    }
}

float GetPipeRandomWidth(void)
{
    float randomWidth = ((float)rand() / (float)(RAND_MAX / PIPE_WIDTH_VARIANCE)) + 262.0f;
    // printf("Random height set for pipe is: %f\n", randomWidth);
    return randomWidth;
}
