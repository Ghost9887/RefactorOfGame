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
#define AMOUNTOFTILETEXTURES 5
#define MAXTILES 10000

//PLAYER CONSTANTS/ENUM
#define PAINT 0 // tile can be walked through
#define SOLID 1 // tile cannot be walked through
#define PLAYERSPAWN 2

typedef struct{
  Texture2D *selectedTexture;
  int textureId;
  bool interactingWithUI;
  int mode; //determine what type of tile to place
}User;

typedef struct{
  int id; 
  Vector2 pos;
  bool active;
  bool solid; //cant walk through
  //
  //playerspawn attributes
  bool playerSpawn;

}Tile;

typedef struct{
  Texture2D tile1;
  Texture2D tile2;
  Texture2D tile3;
  Texture2D tile4;
  Texture2D player;
}TextureManager;

#endif


