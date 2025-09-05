#include "tile.h"

Tile createEmptyTile(int id){
  Tile tile;
  tile.id = id;
  tile.pos = (Vector2){ -1, -1 };
  tile.active = false;
  tile.solid = false;
  tile.enemySpawn = false;
  tile.weaponBuy = false;
  tile.perkBuy = false;
}

void initTileArr(Tile *tileArr){
  for(int i = 0; i < MAXTILES; i++){
    tileArr[i] = createEmptyTile(i);
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
}
