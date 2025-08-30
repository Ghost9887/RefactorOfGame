#include "weaponBuy.h"

extern int AMOUNTOFWEAPONBUYS;

WeaponBuy createEmptyWeaponBuy(){
  WeaponBuy weaponBuy;
  weaponBuy.id = -1;
  weaponBuy.pos = (Vector2){ 0, 0 };
  weaponBuy.width = 32;
  weaponBuy.height = 32;
  weaponBuy.scale = 1.0f;
  weaponBuy.weapon;
  weaponBuy.frameRec = (Rectangle){ 0, 0, 32, 32 };
  return weaponBuy;
}

void createWeaponBuy(WeaponBuy *weaponBuyArr, Weapon *weaponArr, int id, float x, float y){
  WeaponBuy weaponBuy;
  weaponBuy.id = id;
  weaponBuy.pos = (Vector2){ x, y };
  weaponBuy.width = 32;
  weaponBuy.height = 32;
  weaponBuy.scale = 1.0f;
  weaponBuy.weapon = findWeaponById(id, weaponArr);
  weaponBuy.frameRec = (Rectangle){ 0, 0, weaponBuy.width, weaponBuy.height };
  weaponBuyArr[AMOUNTOFWEAPONBUYS] = weaponBuy;
}

void initWeaponBuyArr(WeaponBuy *weaponBuyArr){
  for(int i = 0; i < MAXWEAPONBUYS; i++){
    weaponBuyArr[i] = createEmptyWeaponBuy();   
  }
}

void drawWeaponBuy(WeaponBuy *weaponBuy){
  DrawTextureRec(*weaponBuy->weapon->texture, weaponBuy->frameRec, weaponBuy->pos, WHITE);
}

//TODO: make it prettier
void drawWeaponBuyText(WeaponBuy *weaponBuy, Color colour, int price) {
    DrawText(TextFormat("%s", weaponBuy->weapon->name), weaponBuy->pos.x, weaponBuy->pos.y - 50, 20, BLACK);
    DrawText(TextFormat("%d", price), weaponBuy->pos.x, weaponBuy->pos.y - 30, 20, colour);
}

//TODO: check and maybe refactor brain was mush when wrighting this
void buyWeaponBuy(WeaponBuy *weaponBuy, Weapon *weaponArr, Weapon *weaponHolster, Player *player) {
  Rectangle playerRec = { player->pos.x, player->pos.y, player->width, player->height };
  Rectangle weaponBuyRec = { weaponBuy->pos.x, weaponBuy->pos.y, weaponBuy->width, weaponBuy->height };
  if(CheckCollisionRecs(playerRec, weaponBuyRec)){
    //check if we have the weapon in our holster already
    int indexOfWeaponInHolster = checkIfWeaponIsInHolster(weaponBuy->weapon->id, weaponHolster);
    if(indexOfWeaponInHolster != -1){
      if(player->money >= weaponBuy->weapon->ammoCost){
        drawWeaponBuyText(weaponBuy, GREEN, weaponBuy->weapon->ammoCost);
        //only buy ammo if we dont have max amount of ammo already
        if(weaponHolster[indexOfWeaponInHolster].reserveCapacity < weaponHolster[indexOfWeaponInHolster].maxReserveCapacity &&
          IsKeyPressed(KEY_E)) {
          weaponHolster[indexOfWeaponInHolster].reserveCapacity = weaponHolster[indexOfWeaponInHolster].maxReserveCapacity;
          player->money -= weaponHolster[indexOfWeaponInHolster].ammoCost;
        }
      }else{
        drawWeaponBuyText(weaponBuy, RED, weaponBuy->weapon->ammoCost);
      }
    }else{
      Color colour = (player->money >= weaponBuy->weapon->weaponCost) ? GREEN : RED;
      drawWeaponBuyText(weaponBuy, colour, weaponBuy->weapon->weaponCost);
      if(player->money >= weaponBuy->weapon->weaponCost && IsKeyPressed(KEY_E)){
        //check if we have a empty slot in our holster
        int indexToPutInHolster = checkIfEmptySlotInHolster(weaponHolster);
        if(indexToPutInHolster != -1){
          weaponHolster[indexToPutInHolster] = *weaponBuy->weapon;
          player->weapon = &weaponHolster[indexToPutInHolster];
          player->money -= weaponBuy->weapon->weaponCost;
        }else{
          //otherwise replace our current weapon
          int indexOfWeaponInHolster = findIndexOfWeaponHolster(weaponHolster, player);
          weaponHolster[indexOfWeaponInHolster] = *weaponBuy->weapon;
          *player->weapon = weaponHolster[indexOfWeaponInHolster];
          player->money -= weaponBuy->weapon->weaponCost;
        }
      }
    }
  }
}

void updateWeaponBuy(WeaponBuy *weaponBuyArr, Weapon *weaponArr, Weapon *weaponHolster, Player *player){
  for(int i = 0; i < AMOUNTOFWEAPONBUYS; i++){
    drawWeaponBuy(&weaponBuyArr[i]);
    buyWeaponBuy(&weaponBuyArr[i], weaponArr, weaponHolster, player);
  }
}
