#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include "data.h"
#include "terrain.c"

Camera2D camera = {0};

void CollisionCheck(void);
void GameStartup(void);
void GameUpdate(void);
void GameRender(void);
void PlayerInput(void);
void DrawImpact(void);
void UpdateImpactFlash(void);

void GameStartup(void)
{
    InitTextures();

    InitTerrain();

    camera.target = (Vector2){player.position.x, player.position.y - 150};
    camera.offset = (Vector2){(float)screenWidth / 2, (float)screenHeight / 2};
    camera.rotation = 0.0f;
    camera.zoom = 1.2f;
}

void GameUpdate(void)
{
    float dT = GetFrameTime();
    TerrainUpdate(dT);

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

void GameRender(void)
{
    BeginDrawing();

    ClearBackground(BLACK);
    DrawTexture(bgTextureInf, 0, (int)scrollingBG_y, WHITE);
    DrawTexture(bgTextureInf, 0, (int)scrollingBG_y - bgTextureInf.height, WHITE);

    BeginMode2D(camera);

    DrawTexture(bgTexture, 0, 0, WHITE);
    DrawTexture(playerTexture, player.position.x, player.position.y, WHITE);

    DrawTerrain();

    EndMode2D();

    if (flashActive)
    {
        DrawImpact();
    }

    EndDrawing();
}

void PlayerInput(void)
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

void CollisionCheck(void)
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

void UpdateImpactFlash(void)
{
    if (flashActive)
    {
        currentFlashTime += GetFrameTime();

        if (currentFlashTime <= flashTime)
        {
            alpha = 0.9f;
        }
        else if (currentFlashTime <= (flashTime + fadeTime))
        {
            alpha = 0.9f - (currentFlashTime - flashTime) / fadeTime;
        }
        else
        {
            flashActive = false;
            alpha = 0.0f;
        }
    }
}

void DrawImpact(void)
{
    DrawRectangle(0, 0, screenWidth, screenHeight, Fade(WHITE, alpha));
}

int LoadHighScore(void)
{
    char filename[25] = "highscore.txt";
    FILE *f = fopen(filename, "r");

    if (f == NULL)
    {
        return 0;
    }

    int highscore;
    fscanf(f, "%d", &highscore);
    fclose(f);

    return highscore;
}

void SaveHighScore(int score)
{
    char filename[25] = "highscore.txt";
    FILE *f = fopen(filename, "w");

    if (f != NULL)
    {
        fprintf(f, "%d", score);
        fclose(f);
    }
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