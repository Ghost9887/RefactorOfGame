#ifndef COMMON_H
#define COMMON_H

#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <stdbool.h>

//GLOBAL CONSTANTS
#define SCREENWIDTH (GetScreenWidth())
#define SCREENHEIGHT (GetScreenHeight())
#define TARGETFPS 60

//MAP CONSTANTS
#define CELLSIZE 32 // 32x32
#define COLUMNCOUNT 100
#define ROWCOUNT 100

//TILE CONSTANTS
#define AMOUNTOFTILETEXTURES 5
#define MAXTILES 10000

//WEAPONBUYS
#define AMOUNTOFWEAPONS 4
#define MAXWEAPONSBUYS 100

//PERKBUYS
#define AMOUNTOFPERKS 2
#define MAXPERKBUYS 20

//PLAYER CONSTANTS/ENUM
#define PAINT 0 // tile can be walked through
#define SOLID 1 // tile cannot be walked through
#define PLAYERSPAWN 2
#define WEAPONBUY 3
#define PERKBUY 4

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
  
  //playerspawn attributes
  bool playerSpawn;

  //weaponBuy attributes
  bool weaponBuy;
  int weaponIndex;

  //perkBuy attributes
  bool perkBuy;
  int perkIndex;
}Tile;

typedef struct{
  Texture2D tile1;
  Texture2D tile2;
  Texture2D tile3;
  Texture2D tile4;
  Texture2D player;
  Texture2D pistol;
  Texture2D ar;
  Texture2D rpg;
  Texture2D shotgun;
  Texture2D healthPerk;
  Texture2D speedPerk;
}TextureManager;

#endif


