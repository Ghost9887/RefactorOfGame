#ifndef PERK_H
#define PERK_H

#include "common.h"
#include "healthPerk.h"
#include "speedPerk.h"

  void initPerkArr(Perk *perkArr, TextureManager *textureManager);
  Perk *findPerkById(int id, Perk *perkArr);

#endif
