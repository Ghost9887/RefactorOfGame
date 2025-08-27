#include "tile.h"

void initTileArr(Tile *tileArr){

  for(int i = 0; i < MAXTILES; i++){
    tileArr[i].id = i;
    tileArr[i].pos = (Vector2){ 0, 0 };
    tileArr[i].active = false;
  }

}

void initTileTextureArr(Texture2D *tileTextureArr, TextureManager *textureManager){
  tileTextureArr[0] = textureManager->tile1; 
  tileTextureArr[1] = textureManager->tile2;
  tileTextureArr[2] = textureManager->tile3;
  tileTextureArr[3] = textureManager->tile4;
}
