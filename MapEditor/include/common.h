#ifndef COMMON_H
#define COMMON_H

#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//GLOBAL CONSTANTS
#define SCREENWIDTH (GetScreenWidth())
#define SCREENHEIGHT (GetScreenHeight())
#define TARGETFPS 0

//MAP CONSTANTS
#define CELLSIZE 32 // 32x32
#define COLUMNCOUNT 150 
#define ROWCOUNT 150

//ENEMY CONSTANTS
#define MAXENEMYSPAWNS 10

//TILE CONSTANTS
#define AMOUNTOFTILETEXTURES 17
#define MAXTILES 22500

//WEAPONBUYS
#define AMOUNTOFWEAPONS 4
#define MAXWEAPONSBUYS 100

//PERKBUYS
#define AMOUNTOFPERKS 3
#define MAXPERKBUYS 20

//PLAYER CONSTANTS/ENUM
#define PAINT 1 // tile can be walked through
#define SOLID 2 // tile cannot be walked through
#define BUCKET 3
#define PLAYERSPAWN 4
#define ENEMYSPAWN 5
#define WEAPONBUY 6
#define PERKBUY 7
#define CLEAR 8

typedef struct{
  Texture2D *selectedTexture;
  int textureId;
  bool interactingWithUI;
  int mode; //determine what type of tile to place
}User;

typedef struct Tile{
  int id;
  int textureId; 
  Vector2 pos;
  bool active;
  bool solid;
  bool playerSpawn;
  bool enemySpawn;
  bool weaponBuy;
  int weaponIndex;
  bool perkBuy;
  int perkIndex;
  struct Tile *next;
}Tile;

typedef struct{
  Tile *front;
  Tile *rear;
  int size;
}Queue;

typedef struct{
  Texture2D tile1;
  Texture2D tile2;
  Texture2D tile3;
  Texture2D tile4;
  Texture2D tile5;
  Texture2D tile6;
  Texture2D tile7;
  Texture2D tile8;
  Texture2D tile9;
  Texture2D tile10;
  Texture2D tile11;
  Texture2D tile12;
  Texture2D tile13;
  Texture2D tile14;
  Texture2D tile15;
  Texture2D player;
  Texture2D enemy;
  Texture2D pistol;
  Texture2D ar;
  Texture2D rpg;
  Texture2D shotgun;
  Texture2D healthPerk;
  Texture2D speedPerk;
  Texture2D generator;
}TextureManager;

#endif


