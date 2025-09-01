#include "rpg.h"

extern int AMOUNTOFTILES;

Weapon createRPG(TextureManager *textureManager){
  Weapon rpg;
  rpg.id = 2;
  rpg.pos = (Vector2){ 0, 0 };
  rpg.width = 32;
  rpg.height = 32;
  rpg.rotation = 0.0f;
  rpg.scale = 1.5f;
  rpg.damage = 200;
  rpg.projectileSpeed = 300.0f;
  rpg.range = 500.0f;
  rpg.spread = 3.0f;
  rpg.weaponCost = 100;
  rpg.ammoCost = 10;
  rpg.maxMagCapacity = 1;
  rpg.maxReserveCapacity = 4;
  rpg.magCapacity = rpg.maxMagCapacity;
  rpg.reserveCapacity = rpg.maxReserveCapacity;
  rpg.reloadTime = 5.0f;
  rpg.reloadTimer = 0.0f;
  rpg.texture = &textureManager->rpgTexture;
  rpg.fireRate = 1.0f;
  rpg.fireRateTimer = 0.0f;
  rpg.frameRec = (Rectangle){ 0, 0, rpg.width, rpg.height };
  rpg.name = "RPG";
  rpg.type = "explosive";
  return rpg;
}

//defenitely not effecient but works for now
bool hasLineOfSight(Vector2 from, Vector2 to, Tile *tileArr) {
  for (int i = 0; i < AMOUNTOFTILES; i++) {
    Rectangle tileRec = { tileArr[i].pos.x, tileArr[i].pos.y, CELLSIZE, CELLSIZE };
    //maybe??
    Rectangle line = { from.x, from.y, to.x, to.y };
    if (tileArr[i].solid && CheckCollisionRecs(line, tileRec)) {
      return false;
    }
  }
  return true;
}

void splashDamage(Projectile *projectile, Enemy *enemyArr, Player *player, Tile *tileArr){
  Vector2 center = { projectile->pos.x + projectile->size / 2.0f, projectile->pos.y + projectile->size / 2.0f };
  float damage = (float)projectile->damage;
  float radius = 200.0f;
  for (int i = 0; i < MAXSPAWNENEMIES; i++) {
    Vector2 enemyPos = enemyArr[i].pos;
    float dx = center.x - enemyPos.x;
    float dy = center.y - enemyPos.y;
    float dist = sqrtf(dx * dx + dy * dy);
    if (dist <= radius && hasLineOfSight(center, enemyPos, tileArr)) {
      float actualDamage = damage * (1.0f - (dist / radius));
      enemyArr[i].health -= actualDamage;
      if (enemyArr[i].health > 0) {
        player->money += 10;
      } else {
        player->money += 80;
      }
    }
  }
  
  //explosionAnimation(center.x, center.y, radius);
  DrawCircle(center.x, center.y, radius, YELLOW);
}




