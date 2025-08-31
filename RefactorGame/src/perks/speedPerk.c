#include "speedPerk.h"

Perk createSpeedPerk(TextureManager *textureManager){
  Perk speedPerk;
  speedPerk.id = 1;
  speedPerk.data = (float)200;
  speedPerk.cost = 200;
  speedPerk.name = "Speed Perk";
  speedPerk.texture = &textureManager->speedPerkTexture;
  return speedPerk;
}
