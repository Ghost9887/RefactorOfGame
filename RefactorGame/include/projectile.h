#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "common.h"

  void createProjectile(Projectile *projectileArr, Player *player, float offset);
  void initProjectileArr(Projectile *projectileArr);
  void updateProjectile(Projectile *projectileArr, Enemy *enemyArr);
  void checkProjectileCollisionWithTile(Projectile *projectileArr, Tile *tile);

#endif
