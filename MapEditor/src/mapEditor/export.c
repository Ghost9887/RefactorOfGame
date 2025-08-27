#include "export.h"

//special imports
#include <stdlib.h>
#include <string.h>

void exportMap(Tile *tileArr){
  FILE *file = fopen("../RefactorGame/assets/map1.map", "w");
  if(file == NULL){
    printf("Failed to open map file");
    return;
  }
  for(int i = 0; i < MAXTILES; i++){
    fprintf(file, "%d{{%d, %d},{%d},{%d}}",
    tileArr[i].id,
    (int)tileArr[i].pos.x,
    (int)tileArr[i].pos.y,
    tileArr[i].active,
    tileArr[i].solid
    );
    if(i < MAXTILES - 1){
      fprintf(file, ";");
    }
  }
  fclose(file);
  CloseWindow();
}

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

