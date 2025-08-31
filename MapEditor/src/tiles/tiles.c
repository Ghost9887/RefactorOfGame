#include "tile.h"

void initTileArr(Tile *tileArr){
  for(int i = 0; i < MAXTILES; i++){
    tileArr[i].id = -1;
    tileArr[i].pos = (Vector2){ 0, 0 };
    tileArr[i].active = false;
    tileArr[i].solid = false;
    tileArr[i].playerSpawn = false;
    tileArr[i].weaponBuy = false;
    tileArr[i].weaponIndex = -1;
  }
}

void initTileTextureArr(Texture2D *tileTextureArr, TextureManager *textureManager){
  tileTextureArr[0] = textureManager->tile1; 
  tileTextureArr[1] = textureManager->tile2;
  tileTextureArr[2] = textureManager->tile3;
  tileTextureArr[3] = textureManager->tile4;
  tileTextureArr[4] = textureManager->player;
}

void initWeaponTextureArr(Texture2D *weaponTextureArr, TextureManager *textureManager){
  weaponTextureArr[0] = textureManager->pistol;
  weaponTextureArr[1] = textureManager->ar;
  weaponTextureArr[2] = textureManager->rpg;
}

void initPerkTextureArr(Texture2D *perkTextureArr, TextureManager *textureManager){
  perkTextureArr[0] = textureManager->healthPerk;
  perkTextureArr[1] = textureManager->speedPerk;
}
