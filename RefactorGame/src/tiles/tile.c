#include "tile.h"

Tile createEmptyTile(){
  Tile tile;
  tile.pos = (Vector2){ 0, 0 };
  tile.active = false;
  tile.solid = false;
}

void initTileArr(Tile *tileArr){
  for(int i = 0; i < MAXTILES; i++){
    tileArr[i] = createEmptyTile();
  }
}

void initTileTextureArr(Texture2D *tileTextureArr, TextureManager *textureManager){
  tileTextureArr[0] = textureManager->tile1;
  tileTextureArr[1] = textureManager->tile2;
  tileTextureArr[2] = textureManager->tile3;
  tileTextureArr[3] = textureManager->tile4;
}
