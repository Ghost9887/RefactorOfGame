#include "ar.h"

Weapon createAR(TextureManager *textureManager){
  Weapon ar;
  ar.pos = (Vector2){ 0, 0 };
  ar.width = 32;
  ar.height = 32;
  ar.rotation = 0.0f;
  ar.scale = 1.0f;
  ar.damage = 60;
  ar.projectileSpeed = 500.0f;
  ar.range = 400.0f;
  ar.maxMagCapacity = 35;
  ar.magCapacity = ar.maxMagCapacity;
  ar.maxReserveCapacity = 175;
  ar.reserveCapacity = ar.maxReserveCapacity;
  ar.reloadTime = 2.0f;
  ar.reloadTimer = 0.0f;
  ar.texture = &textureManager->arTexture;
  ar.fireRate = 0.4;
  ar.fireRateTimer = 0.0f;
  ar.frameRec = (Rectangle){ 0, 0, ar.width, ar.height };
  return ar;
}
