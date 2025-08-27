#ifndef COMMON_H
#define COMMON_H

#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <stdbool.h>

//GLOBAL CONSTANTS
#define SCREENWIDTH 1200
#define SCREENHEIGHT 800
#define TARGETFPS 60

//MAP CONSTANTS
#define CELLSIZE 32 // 32x32
#define COLUMNCOUNT 100
#define ROWCOUNT 100

//TILE CONSTANTS
#define AMOUNTOFTILETEXTURES 4
#define MAXTILES 10000

typedef struct{
  Texture2D *selectedTexture;
}User;

typedef struct{
  int id; 
  Vector2 pos;
  Texture2D *texture;
  bool active;
}Tile;

typedef struct{
  Texture2D tile1;
  Texture2D tile2;
  Texture2D tile3;
  Texture2D tile4;
}TextureManager;

#endif


