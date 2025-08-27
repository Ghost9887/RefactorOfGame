#include "map.h"

//special imports
#include <stdlib.h>
#include <string.h>

void importMap(Tile *tileArr, Texture2D *tileTextureArr){
 FILE *file = fopen("../RefactorGame/assets/map1.map", "r");
  if(file == NULL){
    printf("Failed to open map file");
  }

  char buffer[100000];
  if(fgets(buffer, sizeof(buffer), file) == NULL){
    printf("Failed to read file");
    fclose(file);
    return;
  }
  fclose(file);
  char *token = strtok(buffer, ";");
  int index = 0;
  while(token != NULL && index < MAXTILES){
    int id, posX, posY, active, solid;
    sscanf(token, "%d{{%d,%d},{%d},{%d}}", &id, &posX, &posY, &active, &solid);
    tileArr[index].id = id;
    tileArr[index].texture = &tileTextureArr[tileArr[index].id];
    tileArr[index].pos.x = posX;
    tileArr[index].pos.y = posY;
    tileArr[index].active = active;
    tileArr[index].solid = solid;
    token = strtok(NULL, ";");
    index++;
  }
  printf("Imported Map successfully");
}

void drawTiles(Tile *tileArr){
for(int i = 0; i < MAXTILES; i++){
    if(tileArr[i].active){
      DrawTexture(*tileArr[i].texture, tileArr[i].pos.x, tileArr[i].pos.y, WHITE);
      if(tileArr[i].solid){
        //outline solid tiles
        DrawRectangleLines(tileArr[i].pos.x, tileArr[i].pos.y, CELLSIZE, CELLSIZE, RED);
      }
    }
  }
}

void updateMap(Tile *tileArr){
  drawTiles(tileArr);
}
