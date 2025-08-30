#ifndef MAP_H
#define MAP_H

#include "common.h"
#include "player.h"
#include "enemy.h"
#include "weaponBuy.h"

  int getAmountOfTiles();
  void importMap(Tile *tileArr);
  void updateMap(Tile *tileArr, Texture2D *tileTextureArr, Player *player, Enemy *enemyArr, Projectile *projectileArr);
  void spawnObjects(Tile *tileArr, Player *player, Weapon *weaponBuy, WeaponBuy *weaponBuyArr);

#endif
