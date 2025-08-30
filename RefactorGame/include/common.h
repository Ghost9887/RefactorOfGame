#ifndef COMMON_H
#define COMMON_H

#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//game constants
#define SCREENWIDTH (GetScreenWidth())
#define SCREENHEIGHT (GetScreenHeight())
#define TARGETFPS 0

//enemy constants
#define MAXSPAWNENEMIES 40

//projectile constants
#define MAXPROJECTILES 100

//weapon constants
#define AMOUNTOFWEAPONS 2
#define MAXWEAPONS 3 //max amount of weapons the player can have on him
#define MAXWEAPONBUYS 20

//tile constants
#define MAXTILES 10000
#define AMOUNTOFTILETEXTURES 4
#define CELLSIZE 32 // size of a tile 

typedef struct{
  Texture2D playerTexture;
  Texture2D basicEnemyTexture;
  Texture2D pistolTexture;
  Texture2D arTexture;
  Texture2D tile1;
  Texture2D tile2;
  Texture2D tile3;
  Texture2D tile4;
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
  Vector2 pos;
  float width;
  float height;
  int money;
  float rotation;
  float speed;
  Vector2 velocity;
  int health;
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
}Projectile;

typedef struct{
  int roundNumber;
  int enemyCount;
  float breakTime;
  float breakTimer;
  bool inBreak;
  bool allEnemiesSpawned;
}RoundManager;

typedef struct{
  int id;
  Vector2 pos;
  bool active;
  bool solid;
  bool playerSpawn;
  bool weaponBuy;
  int weaponIndex;
}Tile;

#endif
