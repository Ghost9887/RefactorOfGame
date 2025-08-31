#ifndef PICKUP_H
#define PICKUP_H

#include "common.h"
#include "ammoPickup.h"
#include "healthPickup.h"

  void updatePickups(Pickup *pickupArr, Player *player);
  void spawnPickup(Pickup *pickupArr, char *type, Enemy *enemy, Player *player, TextureManager *textureManager);
  void initPickupArr(Pickup *pickupArr);

#endif
