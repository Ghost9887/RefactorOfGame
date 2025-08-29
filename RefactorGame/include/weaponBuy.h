#ifndef WEAPONBUY_H
#define WEAPONBUY_H

#include "common.h"
#include "weapon.h"
#include "ui.h"

  void initWeaponBuyArr(WeaponBuy *weaponBuyArr, Weapon *weaponArr);
  void updateWeaponBuy(WeaponBuy *weaponBuyArr, Weapon *weaponArr, Weapon *weaponHolster, Player *player);

#endif
