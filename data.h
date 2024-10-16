#ifndef DATA_H_
#define DATA_H_

#include <raymath.h>

#define TILE_WIDTH 18
#define TILE_HEIGHT 18
#define WORLD_WIDTH 22
#define WORLD_HEIGHT 33
#define MAX_TEXTURES 3
#define TILESET_WIDTH 16

const int screen_width = 400;
const int screen_height = 600;

int score; // lägg till score system senare
float acceleration = 0.15f;

typedef enum {
   TILE_TYPE_EMPTY = 0,
   TILE_TYPE_FLOOR = 1 * TILESET_WIDTH + 2,
   TILE_TYPE_DIRT = 2 * TILESET_WIDTH + 2,
   TILE_TYPE_WALL_LEFT,
   TILE_TYPE_WALL_HORIZONTAL,
   TILE_TYPE_WALL_RIGHT
} tile_type;

typedef struct {
   int x;
   int y;
   int type;
} s_tile;

typedef struct {
   Vector2 position;
   Vector2 velocity;
   float move_speed;
   bool is_alive;
} s_player;

typedef enum {
   TEXTURE_TILEMAP = 0,
   TEXTURE_PLAYER,
   TEXTURE_BACKGROUND
} texture_asset;

#endif
