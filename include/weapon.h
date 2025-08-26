#ifndef WEAPON_H
#define WEAPON_H

#include "common.h"
  
  void initWeaponArr(Weapon *weaponArr, TextureManager *textureManager);
  bool checkIfWeaponCanShoot(Weapon *weapon);
  void updateWeapons(Player *player);

#endif 
