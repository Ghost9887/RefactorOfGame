#ifndef CHUNK_H
#define CHUNK_H

#include "common.h"

  void initChunkArr(Chunk *chunkArr, Tile *tileArr);
  int findChunksInCameraView(int *arr, Chunk *chunkArr, Camera2D *camera);
  int findChunksForEnemy(int *arr, Chunk *chunkArr, Enemy *enemy);
  void freeAllChunks(Chunk *chunkArr);

#endif
