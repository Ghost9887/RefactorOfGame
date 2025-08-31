#include "healthPickup.h"

Pickup createHealthPickup(TextureManager *textureManager, float x, float y){
  Pickup healthPickup;
  healthPickup.pos = (Vector2){ x, y };
  healthPickup.data = 20;
  healthPickup.durationTime = 30.0f;
  healthPickup.durationTimer = 30.0f;
  healthPickup.active = true;
  healthPickup.texture = &textureManager->healthPickupTexture;
  //animations
  healthPickup.amountOfFrames = 2;
  healthPickup.currentFrame = 0;
  healthPickup.frameTime = 0.0f;
  healthPickup.frameSpeed = 0.3f;
  healthPickup.type = "health";
  healthPickup.frameRec = (Rectangle){ 0.0f, 0.0f, 32.0f, 32.0f };
  return healthPickup;
}

