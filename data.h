#ifndef DATA_H_
#define DATA_H_

#include <raylib.h>
#include <raymath.h>

#define WORLD_WIDTH 22
#define WORLD_HEIGHT 33

const int screenWidth = 400;  // 400
const int screenHeight = 600; // 600
const float scrollSpeed = 100.0f;

float flashTime = 0.2f;
float fadeTime = 0.5f;
float currentFlashTime = 0.0f;
float alpha = 0.0f;
bool flashActive = false;

float acceleration = 0.175f;
float scrollingBG_y = 0.0f;

typedef struct
{
   Vector2 position;
   Vector2 velocity;
   bool isAlive;
   Rectangle collider;
} sPlayer;

typedef struct
{
   Vector2 position;
   Rectangle collision;
} sPipe;

sPlayer player = {
    .position = {200.0f, 500.0f},
    .velocity = {0, -2},
    .isAlive = true};

#endif
