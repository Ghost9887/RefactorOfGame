#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "common.h"
#include "rpg.h"

  void createProjectile(Projectile *projectileArr, Player *player, float offset, char *type);
  void initProjectileArr(Projectile *projectileArr);
  void updateProjectile(Projectile *projectileArr, Enemy *enemyArr, Player *player, Tile *tileArr);
  void checkProjectileCollisionWithTile(Projectile *projectileArr, Chunk *chunk, Enemy *enemyArr, Player *player, Tile *tileArr);

#endif
