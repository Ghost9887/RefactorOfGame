#include "pistol.h"

Weapon createPistol(TextureManager *textureManager){
  Weapon pistol;
  pistol.id = 0;
  pistol.pos = (Vector2){ 0, 0 };
  pistol.width = 32;
  pistol.height = 32;
  pistol.rotation = 0.0f;
  pistol.scale = 0.7f;
  pistol.damage = 100;
  pistol.projectileSpeed = 700.0f;
  pistol.range = 1000.0f;
  pistol.spread = 5.0f;
  pistol.weaponCost = 50;
  pistol.ammoCost = 10;
  pistol.maxMagCapacity = 1000;
  pistol.magCapacity = pistol.maxMagCapacity;
  pistol.maxReserveCapacity = 42;
  pistol.reserveCapacity = pistol.maxReserveCapacity;
  pistol.reloadTime = 1.5f;
  pistol.reloadTimer = 0.0f;
  pistol.texture = &textureManager->pistolTexture;
  pistol.fireRate = 0.2f;
  pistol.fireRateTimer = 0.0f;
  pistol.frameRec = (Rectangle){ 0, 0, pistol.width, pistol.height };
  pistol.name = "pistol";
  pistol.type = "ballistic";
  return pistol;
}
