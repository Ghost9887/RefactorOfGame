#include "user.h"

User createUser(Texture2D *tileTextureArr){
  User user;
  user.selectedTexture = &tileTextureArr[0];
  user.textureId = 0;
  user.interactingWithUI = false;
  user.mode = PAINT;
  return user;
}

void switchMode(User *user){
  if(IsKeyPressed(KEY_ONE)) user->mode = PAINT;
  else if(IsKeyPressed(KEY_TWO)) user->mode = SOLID;
  else if(IsKeyPressed(KEY_THREE)) user->mode = PLAYERSPAWN;
  else if(IsKeyPressed(KEY_FOUR)) user->mode = ENEMYSPAWN;
  else if(IsKeyPressed(KEY_FIVE)) user->mode = WEAPONBUY;
  else if(IsKeyPressed(KEY_SIX)) user->mode = PERKBUY;
}

