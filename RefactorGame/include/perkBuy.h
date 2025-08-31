#ifndef PERKBUY_H
#define PERKBUY_H

#include "common.h"
#include "perk.h"

  void initPerkBuyArr(PerkBuy *perkBuyArr);
  void createPerkBuy(PerkBuy *perkBuyArr, Perk *perkArr, int id, float x, float y);
  void updatePerkBuys(PerkBuy *perkBuyArr, Player *player);

#endif
