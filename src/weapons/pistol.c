#include "pistol.h"

Weapon createPistol(TextureManager *textureManager){
  Weapon pistol;
  pistol.pos = (Vector2){ 0, 0 };
  pistol.width = 32;
  pistol.height = 32;
  pistol.rotation = 0.0f;
  pistol.scale = 1.0f;
  pistol.damage = 25;
  pistol.projectileSpeed = 700.0f;
  pistol.range = 300.0f;
  pistol.maxMagCapacity = 6;
  pistol.magCapacity = pistol.maxMagCapacity;
  pistol.maxReserveCapacity = 42;
  pistol.reserveCapacity = pistol.maxReserveCapacity;
  pistol.reloadTime = 1.5f;
  pistol.reloadTimer = 0.0f;
  pistol.texture = &textureManager->pistolTexture;
  pistol.fireRate = 0.6f;
  pistol.fireRateTimer = 0.0f;
  pistol.frameRec = (Rectangle){ 0, 0, 32, 32 };
  return pistol;
}
