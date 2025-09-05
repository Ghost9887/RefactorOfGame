#ifndef COMMON_H
#define COMMON_H

#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

//game constants
#define SCREENWIDTH (GetScreenWidth())
#define SCREENHEIGHT (GetScreenHeight())
#define TARGETFPS 0

//enemy constants
#define MAXSPAWNENEMIES 40
#define MAXENEMYSPAWNS 10

//projectile constants
#define MAXPROJECTILES 100

//weapon constants
#define AMOUNTOFWEAPONS 4
#define MAXWEAPONS 3 //max amount of weapons the player can have on him
#define MAXWEAPONBUYS 20

//tile constants
#define MAXTILES 22500
#define AMOUNTOFTILETEXTURES 14
#define CELLSIZE 32 // size of a tile 

#define AMOUNTOFCHUNKS 9
#define CHUNKSIZE 50

//pickup constants
#define MAXPICKUPS 15 
#define AMOUNTOFPICKUPS 2

//perk constants
#define AMOUNTOFPERKS 2
#define MAXPERKBUYS 20

typedef struct{
  Texture2D playerTexture;
  Texture2D basicEnemyTexture;
  Texture2D pistolTexture;
  Texture2D arTexture;
  Texture2D rpgTexture;
  Texture2D shotgunTexture;
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
  Texture2D ammoPickupTexture;
  Texture2D healthPickupTexture;
  Texture2D healthPerkTexture;
  Texture2D speedPerkTexture;
}TextureManager;

typedef struct{
  int playerMoney;
}MoneyManager;

typedef struct{
  int id;
  Vector2 pos;
  float width;
  float height;
  float rotation;
  float scale;
  int damage;
  float projectileSpeed;
  float range;
  float spread;
  int weaponCost;
  int ammoCost;
  int maxMagCapacity;
  int magCapacity;
  int maxReserveCapacity;
  float reloadTime;
  float reloadTimer;
  int reserveCapacity;
  Texture2D *texture;
  float fireRate;
  float fireRateTimer;
  Rectangle frameRec;
  char *name;
  char *type;
}Weapon;

typedef struct{
  int id;
  Vector2 pos;
  int width;
  int height;
  float scale;
  Weapon *weapon;
  Rectangle frameRec;
}WeaponBuy;

typedef struct{
  int id;
  int data;
  int cost;
  char *name;
  Texture2D *texture;
}Perk;

typedef struct{
  int id;
  Vector2 pos;
  int width;
  int height;
  float scale;
  int cost;
  Perk *perk;
  int amountOfFrames;
  int currentFrame;
  float frameTime;
  float frameSpeed;
  Rectangle frameRec;
  bool consumed;
}PerkBuy;

typedef struct{
  Vector2 pos;
  float width;
  float height;
  int money;
  float rotation;
  float speed;
  Vector2 velocity;
  int health;
  int maxHealth;
  Texture2D *texture;
  Weapon *weapon;
  bool ads;
  int amountOfFrames;
  int currentFrame;
  float frameTime;
  float frameSpeed;
  Rectangle frameRec;
}Player;

typedef struct{
  Vector2 pos;
  float width;
  float height;
  float speed;
  Vector2 velocity;
  int damage;
  int health;
  Texture2D *texture;
  float attackCooldown;
  float attackTimer;
  int amountOfFrames;
  int currentFrame;
  float frameTime;
  float frameSpeed;
  Rectangle frameRec;
  bool active;
}Enemy;

typedef struct{
  int amount;
  Vector2 pos;
}EnemySpawn;

typedef struct{
  Vector2 pos;
  Vector2 previousPos;
  Vector2 dir;
  int damage;
  float speed;
  float range;
  float length;
  float size;
  float distanceTraveled;
  bool active;
  char *type;
}Projectile;

typedef struct{
  int roundNumber;
  int enemyCount;
  float breakTime;
  float breakTimer;
  bool inBreak;
  bool allEnemiesSpawned;
}RoundManager;

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
  //ASTAR ALGO
  int gCost;
  int hCost;
  int fCost;
  struct Tile *parent;
  struct Tile *next;
}Tile;

typedef struct{
  Tile *front;
  Tile *rear;
  int size;
}PriorityQueue;

typedef struct{
  int id;
  float startX;
  float endX;
  float startY;
  float endY;
  int tileCount;
  Tile *tileArr;
  int solidTileCount;
  Tile *solidTileArr;
}Chunk;

typedef struct{
  Vector2 pos;
  int data;
  float durationTime;
  float durationTimer;
  bool active;
  Texture2D *texture;
  int amountOfFrames;
  int currentFrame;
  float frameTime;
  float frameSpeed;
  Rectangle frameRec;
  char *type;
}Pickup;

#endif
