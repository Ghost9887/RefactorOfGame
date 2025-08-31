#include "perk.h"

void initPerkArr(Perk *perkArr, TextureManager *textureManager){
  perkArr[0] = createHealthPerk(textureManager);
  perkArr[1] = createSpeedPerk(textureManager);
}

Perk *findPerkById(int id, Perk *perkArr){
  return &perkArr[id];
}
