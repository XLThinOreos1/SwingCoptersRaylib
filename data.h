#ifndef DATA_H_
#define DATA_H_

#include <raylib.h>
#include <raymath.h>

#define WORLD_WIDTH 22
#define WORLD_HEIGHT 33

const int screenWidth = 1000;  // 400
const int screenHeight = 1000; // 600
const float scrollSpeed = 100.0f;

float flashTime = 0.2f;
float fadeTime = 0.5f;
float currentFlashTime = 0.0f;
float alpha = 0.0f;
bool flashActive = false;

int score; // lägg till score system senare
float acceleration = 0.175f;
float scrollingBG_y = 0.0f;

typedef struct
{
   Vector2 position;
   Vector2 velocity;
   float moveSpeed;
   bool isAlive;
} sPlayer;

typedef struct
{
   Vector2 position;
   Rectangle collisionLeft;
   Rectangle collisionRight;
} sPipe;

sPlayer player = {
    .position = {200, 500},
    .velocity = {0, -2},
    .moveSpeed = 200,
    .isAlive = true};

#endif
