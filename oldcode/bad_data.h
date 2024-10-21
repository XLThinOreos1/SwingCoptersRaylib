#ifndef DATA_H_
#define DATA_H_

#include <raymath.h>
#include <raylib.h>

#define TILE_WIDTH 18
#define TILE_HEIGHT 18
#define WORLD_WIDTH 22
#define WORLD_HEIGHT 33
#define MAX_TEXTURES 4
#define TILESET_WIDTH 16

const int screenWidth = 400;
const int screenHeight = 600;
const float scrollSpeed = 100.f;

int score; // lägg till score system senare
float acceleration = 0.15f;
float scrollingBG_y = 0.0f;

typedef enum
{
   TILE_TYPE_EMPTY = 0,
   TILE_TYPE_FLOOR = 1 * TILESET_WIDTH + 2,
   TILE_TYPE_DIRT = 2 * TILESET_WIDTH + 2,
   TILE_TYPE_WALL_LEFT = 7 * TILESET_WIDTH + 13,
   TILE_TYPE_WALL_HORIZONTAL = 7 * TILESET_WIDTH + 14,
   TILE_TYPE_WALL_RIGHT = 7 * TILESET_WIDTH + 15
} tile_type;

typedef struct
{
   int x;
   int y;
   int type;
} s_tile;

typedef struct
{
   Vector2 position;
   Vector2 velocity;
   float move_speed;
   bool is_alive;
} s_player;

typedef enum
{
   TEXTURE_TILEMAP = 0,
   TEXTURE_PLAYER,
   TEXTURE_BACKGROUND,
   TEXTURE_INFBACKGROUND
} texture_asset;

typedef struct
{
   Vector2 position;
   Rectangle collision_top;
   Rectangle collision_bottom;
} s_pipe;

#endif
