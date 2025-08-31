#include "ar.h"

Weapon createAR(TextureManager *textureManager){
  Weapon ar;
  ar.id = 1;
  ar.pos = (Vector2){ 0, 0 };
  ar.width = 32;
  ar.height = 32;
  ar.rotation = 0.0f;
  ar.scale = 1.0f;
  ar.damage = 60;
  ar.projectileSpeed = 500.0f;
  ar.range = 800.0f;
  ar.spread = 10.0f;
  ar.weaponCost = 100;
  ar.ammoCost = 10;
  ar.maxMagCapacity = 35;
  ar.magCapacity = ar.maxMagCapacity;
  ar.maxReserveCapacity = 175;
  ar.reserveCapacity = ar.maxReserveCapacity;
  ar.reloadTime = 2.0f;
  ar.reloadTimer = 0.0f;
  ar.texture = &textureManager->arTexture;
  ar.fireRate = 0.2;
  ar.fireRateTimer = 0.0f;
  ar.frameRec = (Rectangle){ 0, 0, ar.width, ar.height };
  ar.name = "ar";
  ar.type = "ballistic";
  return ar;
}
