#include "rpg.h"

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

void splashDamage(Projectile *projectile, Enemy *enemyArr, Enemy *enemy, Player *player){
  float posX = enemy->pos.x + enemy->width / 2.0f;
  float posY = enemy->pos.y + enemy->height / 2.0f;
  float damage = (float)projectile->damage;
  float radius = 200.0f;
  for (int i = 0; i < MAXSPAWNENEMIES; i++) {
    float dx = posX - enemyArr[i].pos.x;
    float dy = posY - enemyArr[i].pos.y;
    float length = fabs(sqrtf(dx * dx + dy * dy));
    if (length <= radius) {
      float actualDamage = damage * (1.0f - (length / radius));
      //TODO: money is inconsistent fix later
      enemyArr[i].health -= actualDamage;
      if(enemyArr[i].health > 0){
        player->money += 10;
      }else{
        player->money += 80;
      }
    }
  }
  enemy->health -= damage;
  DrawCircle(posX, posY, radius, YELLOW);
}



