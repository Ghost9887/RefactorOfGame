#include "weapon.h"
#include "pistol.h"

void initWeaponArr(Weapon *weaponArr, TextureManager *textureManager){
  weaponArr[0] = createPistol(textureManager);
}

void drawWeapon(Weapon *weapon, Player *player){
  Rectangle source = weapon->frameRec;
  float handOffset = player->width * 0.6f;
  Vector2 weaponPos = {
    player->pos.x + player->width / 2 + cosf(player->rotation * DEG2RAD) * handOffset,
    player->pos.y + player->height / 2 + sinf(player->rotation * DEG2RAD) * handOffset
  };
  Rectangle dest = {
  weaponPos.x,
  weaponPos.y,
  weapon->frameRec.width * weapon->scale,
  weapon->frameRec.height * weapon->scale,
  };
  Vector2 pivot = {
  weapon->frameRec.width * weapon->scale / 2.0f,
  weapon->frameRec.height * weapon->scale / 2.0f
  };
  weapon->rotation = player->rotation;
  DrawTexturePro(*weapon->texture, source, dest, pivot, weapon->rotation, WHITE);
}

void weaponCooldown(Weapon *weapon){
  if(weapon->fireRateTimer <= 0.1f){
    weapon->fireRateTimer = 0.0f;
  }
  else{
    weapon->fireRateTimer -= GetFrameTime();
  }
}

bool checkIfWeaponCanShoot(Weapon *weapon){
  if(weapon->fireRateTimer < 0.01f){
    return true;
  }
  return false;
}

//only take one because only one will always be active in the players hands
void updateWeapons(Player *player){
  drawWeapon(player->weapon, player);
  weaponCooldown(player->weapon);
}
