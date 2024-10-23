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
void ResetGame(void);

void GameStartup(void)
{
    InitTextures();
    InitTerrain();

    player.collider = (Rectangle){player.position.x, player.position.y};

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

    if (!player.isAlive)
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            ResetGame();
        }
    }
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
    // DEBUG
    DrawRectangle(player.collider.x, player.collider.y, playerTexture.width, playerTexture.height, RED);

    DrawPipes();

    EndMode2D();

    if (flashActive)
    {
        DrawImpact();
    }

    if (!player.isAlive)
    {
        DrawText("GAME OVER", 200, 500, 30, RED);
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
    player.collider.x = player.position.x;
    player.collider.y = player.position.y;
    camera.target.y += player.velocity.y;
}

void CollisionCheck(void)
{
    if (player.collider.x < 0) // LEFT
    {
        player.collider.x = 0;

        player.isAlive = false;
        flashActive = true;
        currentFlashTime = 0.0f;
        alpha = 0.9f;
    }

    if (player.collider.x > (screenWidth - 50)) // RIGHT
    {
        player.collider.x = screenWidth - 51;

        player.isAlive = false;
        flashActive = true;
        currentFlashTime = 0.0f;
        alpha = 0.9f;
    }

    for (int i = 0; i < 1; i++)
    {
        Rectangle r1 = player.collider;
        Rectangle r2 = pipes[i].collision;

        if (player.isAlive)
        {
            if (CheckCollisionRecs(r1, r2))
            {
                player.isAlive = false;
                flashActive = true;
                currentFlashTime = 0.0f;
                alpha = 0.9f;
                break;
            }
        }
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

void ResetGame(void)
{
    TerrainReset();
    player.position.x = 200.0f;
    player.collider = (Rectangle){player.position.x, player.position.y, playerTexture.width, playerTexture.height};

    player.velocity.x = 0;
    player.isAlive = true;
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