#ifndef SHOTGUN_H
#define SHOTGUN_H

#include "common.h"
#include "projectile.h"

  Weapon createShotgun(TextureManager *textureManager);
  void spreadShot(Projectile *projectileArr, Player *player);

#endif
