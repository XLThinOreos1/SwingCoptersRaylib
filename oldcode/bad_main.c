// Swing copter game

#include <raylib.h>
#include <raymath.h>
#include "bad_data.h"

Texture2D textures[MAX_TEXTURES];
s_tile world[WORLD_HEIGHT][WORLD_WIDTH];
Camera2D camera = {0};
s_pipe pipes[10];
s_player player = {
    .position = {200, 500},
    .velocity = {0, -2},
    .move_speed = 200};

void GameStartup();
void GameUpdate();
void GameRender();
void game_shutdown();
void draw_tile(int pos_x, int pos_y, int texture_index_x, int texture_index_y);
void PlayerInput();

void GameStartup()
{
   textures[TEXTURE_TILEMAP] = LoadTexture("assets/Tilemap/tilemap_packed.png");
   textures[TEXTURE_PLAYER] = LoadTexture("assets/ufo.png");
   textures[TEXTURE_BACKGROUND] = LoadTexture("assets/background1.png");
   textures[TEXTURE_INFBACKGROUND] = LoadTexture("assets/endless-background.png");

   camera.target = (Vector2){player.position.x, player.position.y - 180};
   camera.offset = (Vector2){(float)screenWidth / 2, (float)screenHeight / 2};
   camera.rotation = 0.0f;
   camera.zoom = 1.1f;
}

void world_generate()
{
   for (int x = 0; x < WORLD_WIDTH; x++)
   {
      world[WORLD_HEIGHT - 2][x].type = TILE_TYPE_FLOOR;
   }

   for (int x = 0; x < WORLD_WIDTH; x++)
   {
      world[WORLD_HEIGHT - 1][x].type = TILE_TYPE_DIRT;
   }

   for (int i = 0; i < 10; i++)
   {
      float random_height = GetPipeRandomHeight();
      pipes[i].position = (Vector2){i * 400.0f + 800.0f, random_height};
      pipes[i].collision_top = (Rectangle){pipes[i].position.x - 64.0f, pipes[i].position.y - 868.0f, 128.0f, 768.0f};
   }
}
void GameUpdate()
{
   PlayerInput();

   scrollingBG_y += scrollSpeed * GetFrameTime();

   if (scrollingBG_y >= textures[TEXTURE_INFBACKGROUND].height)
   {
      scrollingBG_y = 0;
   }
}

void GameRender()
{
   DrawTexture(textures[TEXTURE_INFBACKGROUND], 0, (int)scrollingBG_y, WHITE);
   DrawTexture(textures[TEXTURE_INFBACKGROUND], 0, (int)scrollingBG_y - textures[TEXTURE_INFBACKGROUND].height, WHITE);

   BeginMode2D(camera);

   DrawTexture(textures[TEXTURE_BACKGROUND], 0, 0, WHITE);
   DrawTexture(textures[TEXTURE_PLAYER], player.position.x, player.position.y, WHITE);

   s_tile tile;
   int texture_index_x = 0;
   int texture_index_y = 0; // 1 4

   for (int y = 0; y < WORLD_HEIGHT; y++)
   {
      for (int x = 0; x < WORLD_WIDTH; x++)
      {
         if (world[y][x].type == 0)
            continue;
         texture_index_x = (world[y][x].type) % 16;
         texture_index_y = (world[y][x].type) / 16;
         draw_tile(x * TILE_WIDTH, y * TILE_HEIGHT,
                   texture_index_x, texture_index_y);
      }
   }

   for (int i = 0; i < 10; i++)
   {
      // world[y][x].type == 3 draw_tile(x * TILE_WIDTH, y * TILE_HEIGHT, texture_index_x, texture_index_y);
   }

   EndMode2D();

   // Draw floor
}

void draw_tile(int pos_x, int pos_y, int texture_index_x, int texture_index_y)
{
   Rectangle source = {(float)TILE_WIDTH * texture_index_x, (float)TILE_HEIGHT * texture_index_y, (float)TILE_WIDTH, (float)TILE_HEIGHT};
   Rectangle dest = {(float)(pos_x), (float)(pos_y), (float)TILE_WIDTH, (float)TILE_HEIGHT};
   Vector2 origin = {0, 0};
   DrawTexturePro(textures[TEXTURE_TILEMAP], source, dest, origin, 0.0f, WHITE);
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
   camera.offset.y -= player.velocity.y;
}

void game_shutdown()
{
   for (int i = 0; i < MAX_TEXTURES; i++)
   {
      UnloadTexture(textures[i]);
   }
}

int Main()
{
   InitWindow(screenWidth, screenHeight, "Swing Copter");
   SetTargetFPS(60);

   GameStartup();
   world_generate();

   while (!WindowShouldClose())
   {
      GameUpdate();

      BeginDrawing();
      ClearBackground(BLACK);
      GameRender();
      EndDrawing();
   }

   game_shutdown();
   return 0;
}
