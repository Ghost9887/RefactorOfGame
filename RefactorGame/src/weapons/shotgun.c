#include "shotgun.h"

Weapon createShotgun(TextureManager *textureManager){
  Weapon shotgun;
  shotgun.id = 3;
  shotgun.pos = (Vector2){ 0, 0 };
  shotgun.width = 32;
  shotgun.height = 32;
  shotgun.rotation = 0.0f;
  shotgun.scale = 0.7f;
  shotgun.damage = 30;
  shotgun.projectileSpeed = 700.0f;
  shotgun.range = 400.0f;
  shotgun.spread = 0.0f;
  shotgun.weaponCost = 50;
  shotgun.ammoCost = 10;
  shotgun.maxMagCapacity = 10;
  shotgun.magCapacity = shotgun.maxMagCapacity;
  shotgun.maxReserveCapacity = 50;
  shotgun.reserveCapacity = shotgun.maxReserveCapacity;
  shotgun.reloadTime = 1.5f;
  shotgun.reloadTimer = 0.0f;
  shotgun.texture = &textureManager->shotgunTexture;
  shotgun.fireRate = 0.4f;
  shotgun.fireRateTimer = 0.0f;
  shotgun.frameRec = (Rectangle){ 0, 0, shotgun.width, shotgun.height };
  shotgun.name = "shotgun";
  shotgun.type = "spread";
  return shotgun;
}

void spreadShot(Projectile *projectileArr, Player *player){
  float spreadAngle = 5.0f; 
  int shots = 5;
  int center = shots / 2;
  for (int i = 0; i < shots; i++) {
    float angleOffset = (i - center) * spreadAngle;
    createProjectile(projectileArr, player, angleOffset, "ballistic");
  }
}
