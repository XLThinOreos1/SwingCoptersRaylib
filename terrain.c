#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "data.h"

#define PIPE_SPEED 170.0f
#define PIPE_WIDTH_VARIANCE 500.0f

Texture2D bgTexture, bgTextureInf, pipeT, playerTexture;
sPipe pipes[2];

float distTrav;
float timeTrav;

void InitTextures(void);
void InitTerrain(void);
void TerrainReset(void);
void DrawPipes(void);
void TerrainUpdate(float deltaTime);
float GetPipeRandomX();

void InitTextures(void)
{
    Image bgImage = LoadImage("assets/background.png");
    Image bgImageInf = LoadImage("assets/endless-background.png");
    Image playerSprite = LoadImage("assets/ufo.png");
    Image pipe = LoadImage("assets/pipe.png");

    ImageResize(&pipe, 300, 32);

    bgTexture = LoadTextureFromImage(bgImage);
    bgTextureInf = LoadTextureFromImage(bgImageInf);
    playerTexture = LoadTextureFromImage(playerSprite);
    pipeT = LoadTextureFromImage(pipe);
}

void InitTerrain(void)
{
    for (int i = 0; i < 1; i++)
    {
        float randomWidth = GetPipeRandomX();

        pipes[i].position = (Vector2){randomWidth, player.position.y - 400};        // {i * 400.0f + 800.0f, randomWidth};
        pipes[i].collision = (Rectangle){pipes[i].position.x, pipes[i].position.y}; // 900.0f, 128.0f, 768.0f

        // pipes[i].collision = (Rectangle){pipes[i].position.x, pipes[i].position.y - 400.0f, 128.0f, 200.0f}; // 900.0f, 128.0f, 768.0f
    }
}

void TerrainReset(void)
{
    for (int i = 0; i < 1; i++)
    {
        float randomWidth = GetPipeRandomX();

        pipes[i].position = (Vector2){randomWidth, player.position.y - 400};        // {i * 400.0f + 800.0f, randomWidth};
        pipes[i].collision = (Rectangle){pipes[i].position.x, pipes[i].position.y}; // 900.0f, 128.0f, 768.0f
    }
}

void DrawPipes(void)
{
    // Draw Pipes
    for (int i = 0; i < 1; i++)
    {
        DrawTexture(pipeT, pipes[i].collision.x, pipes[i].collision.y, BLUE);
        DrawTexture(pipeT, pipes[i].collision.x + 400, pipes[i].collision.y, RED);

        printf("%f BLUE\n", pipes[i].collision.x);
        printf("%f RED\n", pipes[i].collision.x);
        printf("%f PLAYER\n", player.position.y);

        DrawRectangleLinesEx(pipes[i].collision, 10.0f, GREEN);
        DrawRectangleLinesEx(pipes[i].collision, 10.0f, GREEN);
        DrawRectangle(pipes[i].collision.x, pipes[i].collision.y, pipeT.width, pipeT.height, GREEN);
    }
}

void TerrainUpdate(float deltaTime)
{
    for (int i = 0; i < 2; i++)
    {
        // Move each pipe
        if (player.isAlive)
        {
            pipes[i].position.y += (PIPE_SPEED * deltaTime);
        }

        // Move pipes over as new ones if they are outside range
        if (pipes[i].position.y > player.position.y + 200.0f)
        {
            pipes[i].position.y = player.position.y - 600.0f;
            pipes[i].position.x = GetPipeRandomX();
            printf("Reset pipe!");
        }
        // Move colliders along with position
        pipes[i].collision = (Rectangle){pipes[i].position.x, pipes[i].position.y};
    }
    DrawPipes();
}

float GetPipeRandomX(void)
{
    float randomWidth = (rand() % (101)) - 200;
    return randomWidth;
}
