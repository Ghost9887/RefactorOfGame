#ifndef WEAPONBUY_H
#define WEAPONBUY_H

#include "common.h"
#include "weapon.h"
#include "ui.h"

  void createWeaponBuy(WeaponBuy *weaponBuyArr, Weapon *weaponArr, int id, float x, float y);
  void initWeaponBuyArr(WeaponBuy *weaponBuyArr);
  void updateWeaponBuy(WeaponBuy *weaponBuyArr, Weapon *weaponArr, Weapon *weaponHolster, Player *player);

#endif
