#ifndef WEAPON_H
#define WEAPON_H

#include "common.h"
#include "pistol.h"
#include "ar.h"
  
  void initWeaponArr(Weapon *weaponArr, TextureManager *textureManager);
  void initWeaponHolster(Weapon *weaponHolster, Weapon *weaponArr);
  bool checkIfWeaponCanShoot(Weapon *weapon);
  int checkIfWeaponIsInHolster(int id, Weapon *weaponHolster);
  int checkIfEmptySlotInHolster(Weapon *weaponHolster);
  int findIndexOfWeaponHolster(Weapon *weaponHolster, Player *player);
  Weapon *findWeaponById(int id, Weapon *weaponArr);
  void updateWeapons(Player *player, Weapon *weaponHolster);

#endif 
