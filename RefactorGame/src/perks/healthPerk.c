#include "healthPerk.h"

Perk createHealthPerk(TextureManager *textureManager){
  Perk healthPerk;
  healthPerk.id = 0;
  healthPerk.data = 150;
  healthPerk.cost = 300;
  healthPerk.name = "Health Perk";
  healthPerk.texture = &textureManager->healthPerkTexture;
  return healthPerk;
}
