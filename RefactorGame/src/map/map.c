#include "map.h"

//special imports
#include <stdlib.h>
#include <string.h>

extern int AMOUNTOFTILES;

int getAmountOfTiles(){
  FILE *file = fopen("../RefactorGame/assets/map1.map", "r");
  if(file == NULL){
    printf("Failed to open file");
    return -1;
  }
  char buffer[100000];
  if(fgets(buffer, sizeof(buffer), file) == NULL){
    printf("Failed to read file");
    fclose(file);
    return -1;
  }
  fclose(file);
  char *token = strtok(buffer, ";");
  int index = 0;
  while(token != NULL && index < MAXTILES){
    int id, posX, posY, active, solid;
    sscanf(token, "%d{{%d,%d},{%d},{%d}}", &id, &posX, &posY, &active, &solid);
    if(active == true){
      index++;
    }
    token = strtok(NULL, ";");
  }
  printf("%d", index);
  return index;
}

void importMap(Tile *tileArr){
 FILE *file = fopen("../RefactorGame/assets/map1.map", "r");
  if(file == NULL){
    printf("Failed to open map file");
    return;
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
  while(token != NULL && index < AMOUNTOFTILES){
    int id, posX, posY, active, solid;
    sscanf(token, "%d{{%d,%d},{%d},{%d}}", &id, &posX, &posY, &active, &solid);
    tileArr[index].id = id;
    tileArr[index].pos.x = posX;
    tileArr[index].pos.y = posY;
    tileArr[index].active = active;
    tileArr[index].solid = solid;
    token = strtok(NULL, ";");
    index++;
  }
  printf("Imported Map successfully");
}

void drawTiles(Tile *tileArr, Texture2D *tileTextureArr){
for(int i = 0; i < AMOUNTOFTILES; i++){
    if(tileArr[i].active){
      DrawTexture(tileTextureArr[tileArr[i].id], tileArr[i].pos.x, tileArr[i].pos.y, WHITE);
    }
  }
}

void updateMap(Tile *tileArr, Texture2D *tileTextureArr){
  drawTiles(tileArr, tileTextureArr);
}
