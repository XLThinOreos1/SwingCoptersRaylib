#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include "dataNEW.h"

Texture2D bgTexture, bgTextureInf, pipeHorizontalT, pipeLeftT, pipeRightT, playerTexture, floorT, dirtT;
Camera2D camera = {0};
sPipe pipes[10];
sPlayer player = {
    .position = {200, 500},
    .velocity = {0, -2},
    .moveSpeed = 200,
    .isAlive = true};

void CollisionCheck();
void GameStartup();
void GameUpdate();
void GameRender();
void PlayerInput();
void DrawImpact();
void UpdateImpactFlash();

void GameStartup()
{
    Image bgImage = LoadImage("assets/background.png");
    Image bgImageInf = LoadImage("assets/endless-background.png");
    Image playerSprite = LoadImage("assets/ufo.png");
    Image pipeHorizontal = LoadImage("assets/Tiles/tile_0109.png");
    Image pipeLeft = LoadImage("assets/Tiles/tile_0111.png");
    Image pipeRight = LoadImage("assets/Tiles/tile_0108.png");
    Image floor = LoadImage("assets/Tiles/tile_0018.png");
    Image dirt = LoadImage("assets/Tiles/tile_0034.png");

    bgTexture = LoadTextureFromImage(bgImage);
    bgTextureInf = LoadTextureFromImage(bgImageInf);
    playerTexture = LoadTextureFromImage(playerSprite);
    pipeHorizontalT = LoadTextureFromImage(pipeHorizontal);
    pipeLeftT = LoadTextureFromImage(pipeLeft);
    pipeRightT = LoadTextureFromImage(pipeRight);
    floorT = LoadTextureFromImage(floor);
    dirtT = LoadTextureFromImage(dirt);

    camera.target = (Vector2){player.position.x, player.position.y - 150};
    camera.offset = (Vector2){(float)screenWidth / 2, (float)screenHeight / 2};
    camera.rotation = 0.0f;
    camera.zoom = 1.2f;
}

void GameUpdate()
{
    CollisionCheck();

    if (player.isAlive)
    {
        PlayerInput();
        scrollingBG_y += scrollSpeed * GetFrameTime();

        if (scrollingBG_y >= bgTextureInf.height)
        {
            scrollingBG_y = 0;
        }
    }

    UpdateImpactFlash();
}

void GameRender()
{
    BeginDrawing();

    ClearBackground(BLACK);
    DrawTexture(bgTextureInf, 0, (int)scrollingBG_y, WHITE);
    DrawTexture(bgTextureInf, 0, (int)scrollingBG_y - bgTextureInf.height, WHITE);

    BeginMode2D(camera);

    DrawTexture(bgTexture, 0, 0, WHITE);
    DrawTexture(playerTexture, player.position.x, player.position.y, WHITE);

    EndMode2D();

    if (flashActive)
    {
        DrawImpact();
    }

    EndDrawing();
}

void PlayerInput()
{
    if (IsKeyPressed(KEY_SPACE))
    {
        player.velocity.x = 0;
        acceleration *= -1;
    }

    player.velocity.x += acceleration;
    player.position.x += player.velocity.x;
    player.position.y += player.velocity.y;
    camera.target.y += player.velocity.y;
}

void CollisionCheck()
{
    if (player.position.x < 0) // LEFT
    {
        player.position.x = 0;

        player.isAlive = false;
        flashActive = true;
        currentFlashTime = 0.0f;
        alpha = 0.9f;
    }

    if (player.position.x > (screenWidth - 50)) // RIGHT
    {
        player.position.x = screenWidth - 51;

        player.isAlive = false;
        flashActive = true;
        currentFlashTime = 0.0f;
        alpha = 0.9f;
    }
}

void UpdateImpactFlash()
{
    if (flashActive)
    {
        currentFlashTime += GetFrameTime(); // Update time elapsed for flash

        if (currentFlashTime <= flashTime) // Initial flash phase
        {
            alpha = 0.9f; // Full opacity
        }
        else if (currentFlashTime <= (flashTime + fadeTime)) // Fade-out phase
        {
            // Decrease opacity over time for the fade effect
            alpha = 0.9f - (currentFlashTime - flashTime) / fadeTime;
        }
        else
        {
            // Flash is over, reset state
            flashActive = false;
            alpha = 0.0f;
        }
    }
}

void DrawImpact()
{
    DrawRectangle(0, 0, screenWidth, screenHeight, Fade(WHITE, alpha));
}

int main()
{
    InitWindow(screenWidth, screenHeight, "Swing Copter");
    SetTargetFPS(60);

    GameStartup();

    while (!WindowShouldClose())
    {
        GameUpdate();
        GameRender();
    }

    return 0;
}