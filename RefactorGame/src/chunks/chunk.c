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
  chunk.solidTileCount = 0;

  chunk.tileArr = malloc(sizeof(Tile) * CHUNKSIZE * CHUNKSIZE);

  int solidCount = 0;
  //chunk the tile arr into smaller arrays
  for(int i = 0; i < MAXTILES; i++){
    if((int)tileArr[i].pos.x >= startX && (int)tileArr[i].pos.x < endX){
      if((int)tileArr[i].pos.y >= startY && (int)tileArr[i].pos.y < endY && tileArr[i].active){
        chunk.tileArr[chunk.tileCount] = tileArr[i];
        printf("x: %d, y: %d\n", (int)chunk.tileArr[chunk.tileCount].pos.x, (int)chunk.tileArr[chunk.tileCount].pos.y);
        if(tileArr[i].solid){
          solidCount++;
        }
        chunk.tileCount++;
      }
    }
  }
  printf("tile count: %d, chunk id: %d\n", chunk.tileCount, chunk.id);
  printf("solid tile count: %d\n", solidCount);
  chunk.solidTileArr = malloc(sizeof(Tile) * solidCount);

  for (int i = 0; i < MAXTILES; i++) {
  if ((int)tileArr[i].pos.x >= startX && (int)tileArr[i].pos.x < endX &&
      (int)tileArr[i].pos.y >= startY && (int)tileArr[i].pos.y < endY &&
      tileArr[i].solid && tileArr[i].active) {
    chunk.solidTileArr[chunk.solidTileCount++] = tileArr[i];
  }
}

  return chunk;
}

void initChunkArr(Chunk *chunkArr, Tile *tileArr){
  int id = 0;
  for (int y = 0; y < 3; y++) {
    for (int x = 0; x < 3; x++) {
      int startX = x * (CHUNKSIZE * CELLSIZE);
      int endX = (x + 1) * (CHUNKSIZE * CELLSIZE);
      printf("startX: %d, endX: %d\n", startX, endX);
      int startY = y * (CHUNKSIZE * CELLSIZE);
      int endY = (y + 1) * (CHUNKSIZE * CELLSIZE);
      printf("startY: %d, endY: %d\n", startY, endY);
      chunkArr[id] = createChunk(id, startX, endX, startY, endY, tileArr);
      id++;
    }
  }
}

void freeAllChunks(Chunk *chunkArr){
  for(int i = 0; i < AMOUNTOFCHUNKS; i++){
    free(chunkArr[i].tileArr);
    free(chunkArr[i].solidTileArr);
  }
}

int findChunksForEnemy(int *visibleChunks, Chunk *chunkArr, Enemy *enemy){
  float padding = 30;
  Rectangle enemyRec = {
    enemy->pos.x - padding,
    enemy->pos.y - padding,
    padding * 2,
    padding * 2
  };
  int count = 0;
  for(int i = 0; i < AMOUNTOFCHUNKS; i++){
    Rectangle chunkRec = {
      chunkArr[i].startX,
      chunkArr[i].startY,
      chunkArr[i].endX - chunkArr[i].startX,
      chunkArr[i].endY - chunkArr[i].startY
    };
    if (CheckCollisionRecs(enemyRec, chunkRec)) {
      visibleChunks[count] = chunkArr[i].id;
      count++;
    }
  }
  return count;
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
    Rectangle chunkRec = {
      chunkArr[i].startX,
      chunkArr[i].startY,
      chunkArr[i].endX - chunkArr[i].startX,
      chunkArr[i].endY - chunkArr[i].startY
    };
    if (CheckCollisionRecs(cameraView, chunkRec)) {
      visibleChunks[count] = chunkArr[i].id;
      count++;
      }
    }
  return count;
}


