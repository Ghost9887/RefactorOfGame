#include "ammoPickup.h"

Pickup createAmmoPickup(TextureManager *textureManager, float x, float y, Player *player){
  Pickup ammoPickup;
  ammoPickup.pos = (Vector2){ x, y };
  ammoPickup.data = player->weapon->maxMagCapacity * 2;
  ammoPickup.durationTime = 30.0f;
  ammoPickup.durationTimer = 30.0f;
  ammoPickup.active = true;
  ammoPickup.texture = &textureManager->ammoPickupTexture;
  //animations
  ammoPickup.amountOfFrames = 4;
  ammoPickup.currentFrame = 0;
  ammoPickup.frameTime = 0.0f;
  ammoPickup.frameSpeed = 0.3f;
  ammoPickup.type = "ammo";
  ammoPickup.frameRec = (Rectangle){ 0.0f, 0.0f, 32.0f, 32.0f };
  return ammoPickup;
}
