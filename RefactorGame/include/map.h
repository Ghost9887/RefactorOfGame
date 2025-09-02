#ifndef MAP_H
#define MAP_H

#include "common.h"
#include "player.h"
#include "enemy.h"
#include "weaponBuy.h"
#include "perkBuy.h"
#include "enemySpawn.h"
#include "chunk.h"

  void getAmountOfTiles();
  void importMap(Tile *tileArr, Tile *solidTileArr);
  void updateMap(Tile *tileArr, Texture2D *tileTextureArr, Player *player, Enemy *enemyArr, Projectile *projectileArr, Chunk *chunkArr, Camera2D *camera, Tile *solidTileArr);
  void spawnObjects(Tile *tileArr, Player *player, Weapon *weaponBuy, WeaponBuy *weaponBuyArr, Perk *perkArr, PerkBuy *perkBuyArr, EnemySpawn *enemySpawnArr);

#endif
