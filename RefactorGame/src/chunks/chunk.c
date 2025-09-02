#include "chunk.h"

extern int AMOUNTOFTILES;

Chunk createChunk(int id, int startX, int endX, int startY, int endY, Tile *tileArr){
  Chunk chunk;
  chunk.id = id;
  chunk.startX = startX;
  chunk.endX = endX;
  chunk.startY = startY;
  chunk.endY = endY;
  chunk.tileCount = 0;

  chunk.tileArr = malloc(sizeof(Tile) * CHUNKSIZE * CHUNKSIZE);
  //chunk the tile arr into smaller arrays
  for(int i = 0; i < AMOUNTOFTILES; i++){
    if(tileArr[i].pos.x >= startX && tileArr[i].pos.x < endX){
      if(tileArr[i].pos.y >= startY && tileArr[i].pos.y < endY){
        chunk.tileArr[chunk.tileCount] = tileArr[i];
        chunk.tileCount++;
      }
    }
  }
  return chunk;
}

void initChunkArr(Chunk *chunkArr, Tile *tileArr){
  int id = 0;
  for (int y = 0; y < 3; y++) {
    for (int x = 0; x < 3; x++) {
      float startX = x * (CHUNKSIZE * CELLSIZE);
      float endX = (x + 1) * (CHUNKSIZE * CELLSIZE);
      float startY = y * (CHUNKSIZE * CELLSIZE);
      float endY = (y + 1) * (CHUNKSIZE * CELLSIZE);
      chunkArr[id] = createChunk(id, startX, endX, startY, endY, tileArr);
      id++;
    }
  }
}

int findChunksInCameraView(int *visibleChunks, Chunk *chunkArr, Camera2D *camera) {
  float padding = 25;
   Rectangle cameraView = {
    camera->target.x - SCREENWIDTH / 2 - padding,
    camera->target.y - SCREENHEIGHT / 2 - padding,
    SCREENWIDTH + padding,
    SCREENHEIGHT + padding
  };
  int count = 0;
  for (int i = 0; i < AMOUNTOFCHUNKS; i++) {
    Rectangle chunkRect = {
      chunkArr[i].startX,
      chunkArr[i].startY,
      chunkArr[i].endX - chunkArr[i].startX,
      chunkArr[i].endY - chunkArr[i].startY
    };
    if (CheckCollisionRecs(cameraView, chunkRect)) {
      visibleChunks[count] = chunkArr[i].id;
      count++;
      }
    }
  return count;
}








