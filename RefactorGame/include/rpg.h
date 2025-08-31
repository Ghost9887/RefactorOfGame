#ifndef RPG_H
#define RPG_H

#include "common.h"

  Weapon createRPG(TextureManager *textureManager);
  void splashDamage(Projectile *projectile, Enemy *enemyArr, Enemy *enemy, Player *player);

#endif
