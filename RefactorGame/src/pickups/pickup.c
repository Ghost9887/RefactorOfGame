#include "pickup.h"

Pickup createEmptyPickup(){
  Pickup pickup;
  pickup.pos = (Vector2){ 0, 0};
  pickup.data = 0;
  pickup.durationTime = 0.0f;
  pickup.durationTimer = 0.0f;
  pickup.texture;
  pickup.active = false;
  pickup.frameRec = (Rectangle){ 0, 0, 0, 0 };
  pickup.type = "";
  return pickup;
}

void initPickupArr(Pickup *pickupArr){
  for(int i = 0; i < MAXPICKUPS; i++){
    pickupArr[i] = createEmptyPickup();
  }
}

void drawPickup(Pickup *pickup){
  DrawTextureRec(*pickup->texture, pickup->frameRec, pickup->pos, WHITE);
}

void updateAnimationPickup(Pickup *pickup){
 pickup->frameTime += GetFrameTime();
  if (pickup->frameTime >= pickup->frameSpeed) {
      pickup->frameTime = 0.0f;
      pickup->currentFrame++;
      if (pickup->currentFrame > pickup->amountOfFrames) pickup->currentFrame = 0;
      pickup->frameRec.y = (float)pickup->currentFrame * pickup->frameRec.width;
  }
}

void spawnPickup(Pickup *pickupArr, char *type, Enemy *enemy, Player *player, TextureManager *textureManager){
  for(int i = 0; i < MAXPICKUPS; i++){
    if(!pickupArr[i].active){
      if(strcmp(type, "ammo") == 0){
        pickupArr[i] = createAmmoPickup(textureManager, enemy->pos.x, enemy->pos.y, player);
        break;
      }
      else if(strcmp(type, "health") == 0){
        pickupArr[i] = createHealthPickup(textureManager, enemy->pos.x, enemy->pos.y);
        break;
      }
    }
  }
}

void checkIfPickupDestroy(Pickup *pickup){
  if(pickup->durationTimer <= 0.01f){
    pickup->active = false;
  }
  else{
    pickup->durationTimer -= GetFrameTime();
  }
}

void consumePickup(Pickup *pickup, Player *player){
  Rectangle playerRec = { player->pos.x, player->pos.y, player->width, player->height };
  Rectangle pickupRec = { pickup->pos.x, pickup->pos.y, 32, 32 };
  if(CheckCollisionRecs(playerRec, pickupRec)){
    if(strcmp(pickup->type, "ammo") == 0){
      if(player->weapon->reserveCapacity + pickup->data <= player->weapon->maxReserveCapacity){
        player->weapon->reserveCapacity += pickup->data;
      }
      else{
        player->weapon->reserveCapacity = player->weapon->maxReserveCapacity;
      }
    }
    else if(strcmp(pickup->type, "health") == 0){
      if(player->health + pickup->data <= player->maxHealth){
        player->health += pickup->data;
      }
      else{
        player->health = player->maxHealth;
      }
    }
    pickup->active = false;
  }
}

void updatePickups(Pickup *pickupArr, Player *player){
  for(int i = 0; i < MAXPICKUPS; i++){
    if(pickupArr[i].active){
      drawPickup(&pickupArr[i]);
      updateAnimationPickup(&pickupArr[i]);
      checkIfPickupDestroy(&pickupArr[i]);
      consumePickup(&pickupArr[i], player);
    }
  }
}
