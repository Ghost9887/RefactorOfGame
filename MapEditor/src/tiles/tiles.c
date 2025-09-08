#include "tile.h"

void initTileArr(Tile *tileArr){
  for(int i = 0; i < MAXTILES; i++){
    tileArr[i].id = i + 1;
    tileArr[i].textureId = -1;
    tileArr[i].pos = (Vector2){ -1, -1 };
    tileArr[i].active = false;
    tileArr[i].solid = false;
    tileArr[i].playerSpawn = false;
    tileArr[i].weaponBuy = false;
    tileArr[i].weaponIndex = -1;
    tileArr[i].next = NULL;
  }
}

void initTileTextureArr(Texture2D *tileTextureArr, TextureManager *textureManager){
  tileTextureArr[0] = textureManager->tile1; 
  tileTextureArr[1] = textureManager->tile2;
  tileTextureArr[2] = textureManager->tile3;
  tileTextureArr[3] = textureManager->tile4;
  tileTextureArr[4] = textureManager->tile5;
  tileTextureArr[5] = textureManager->tile6;
  tileTextureArr[6] = textureManager->tile7;
  tileTextureArr[7] = textureManager->tile8;
  tileTextureArr[8] = textureManager->tile9;
  tileTextureArr[9] = textureManager->tile10;
  tileTextureArr[10] = textureManager->tile11;
  tileTextureArr[11] = textureManager->tile12;
  tileTextureArr[12] = textureManager->tile13;
  tileTextureArr[13] = textureManager->tile14;
  tileTextureArr[14] = textureManager->tile15;
  tileTextureArr[15] = textureManager->player;
  tileTextureArr[16] = textureManager->enemy;
}

void initWeaponTextureArr(Texture2D *weaponTextureArr, TextureManager *textureManager){
  weaponTextureArr[0] = textureManager->pistol;
  weaponTextureArr[1] = textureManager->ar;
  weaponTextureArr[2] = textureManager->rpg;
  weaponTextureArr[3] = textureManager->shotgun;
}

void initPerkTextureArr(Texture2D *perkTextureArr, TextureManager *textureManager){
  perkTextureArr[0] = textureManager->healthPerk;
  perkTextureArr[1] = textureManager->speedPerk;
}
