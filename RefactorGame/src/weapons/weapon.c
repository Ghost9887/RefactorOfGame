#include "weapon.h"

Weapon createEmptyWeapon(){
  Weapon weapon;
  weapon.id = -1;
  weapon.pos = (Vector2){ 0, 0 };
  weapon.width = 0.0f;
  weapon.height = 0.0f;
  weapon.damage = 0;
  weapon.scale = 0.0f;
  weapon.weaponCost = 0;
  weapon.ammoCost = 0;
  weapon.range = 0;
  weapon.spread = 0.0f;
  weapon.maxMagCapacity = 0;
  weapon.maxReserveCapacity = 0;
  weapon.magCapacity = 0;
  weapon.reserveCapacity = 0;
  weapon.reloadTime = 0.0f;
  weapon.reloadTimer = 0.0f;
  weapon.name = "";
  return weapon;
}

void initWeaponArr(Weapon *weaponArr, TextureManager *textureManager){
  weaponArr[0] = createPistol(textureManager);
  weaponArr[1] = createAR(textureManager);
}

void initWeaponHolster(Weapon *weaponHolster, Weapon *weaponArr){
  weaponHolster[0] = weaponArr[0];
  weaponHolster[1] = createEmptyWeapon();
  weaponHolster[2] = createEmptyWeapon();
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

void checkReload(Weapon *weapon){
  if(IsKeyPressed(KEY_R) || weapon->reloadTimer > 0.01f || weapon->magCapacity <= 0){
    if (weapon->reserveCapacity > 0 && weapon->magCapacity < weapon->maxMagCapacity) {
      if (weapon->reloadTimer <= 0.01f) {
        weapon->reloadTimer = weapon->reloadTime;
        } else {
          weapon->reloadTimer -= GetFrameTime();
          if (weapon->reloadTimer <= 0.01f) {
            int ammoToLoad = weapon->maxMagCapacity - weapon->magCapacity;
          if (weapon->reserveCapacity < ammoToLoad) {
            ammoToLoad = weapon->reserveCapacity;
          }
          weapon->magCapacity += ammoToLoad;
          weapon->reserveCapacity -= ammoToLoad;
          weapon->reloadTimer = 0.0f;
        }
      }
    }
  }
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
  if(weapon->fireRateTimer < 0.01f && weapon->magCapacity > 0){
    return true;
  }
  return false;
}

int checkIfWeaponIsInHolster(int id, Weapon *weaponHolster){
  for(int i = 0; i < MAXWEAPONS; i++){
    if(weaponHolster[i].id == id){
      return i;
    }
  }
  return -1;
}

int checkIfEmptySlotInHolster(Weapon *weaponHolster){
  for(int i = 0; i < MAXWEAPONS; i++){
    if(weaponHolster[i].id == -1){
      return i;
    }
  }
  return -1;
}

int findIndexOfWeaponHolster(Weapon *weaponHolster, Player *player){
  for(int i = 0; i < MAXWEAPONS; i++){
    if(player->weapon->id == weaponHolster[i].id){
      return i;
    }
  }
  return -1;
}

Weapon *findWeaponById(int id, Weapon *weaponArr){
  return &weaponArr[id];
}

void switchWeapons(Weapon *weaponHolster, Player *player){
  if(IsKeyPressed(KEY_ONE)){
    if(player->weapon->reloadTimer > 0.0f){
      player->weapon->reloadTimer = 0.0f;
    }
    player->weapon = &weaponHolster[0];
  }
  else if(IsKeyPressed(KEY_TWO) && weaponHolster[1].id != -1){
    if(player->weapon->reloadTimer > 0.0f){
      player->weapon->reloadTimer = 0.0f;
    }
    player->weapon = &weaponHolster[1];
  }
  else if(IsKeyPressed(KEY_THREE) && weaponHolster[2].id != -1){
    if(player->weapon->reloadTimer > 0.0f){
      player->weapon->reloadTimer = 0.0f;
    }
    player->weapon = &weaponHolster[2];
  }
}

//only take one because only one will always be active in the players hands
void updateWeapons(Player *player, Weapon *weaponHolster){
  drawWeapon(player->weapon, player);
  weaponCooldown(player->weapon);
  checkReload(player->weapon);
  switchWeapons(weaponHolster, player);
}
