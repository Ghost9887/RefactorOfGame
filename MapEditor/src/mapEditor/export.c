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
    fprintf(file, "{%d}{%d}{{%d,%d},{%d},{%d},{%d},{%d},{%d}{%d},{%d}{%d}}",
    tileArr[i].id,
    tileArr[i].textureId,
    (int)tileArr[i].pos.x,
    (int)tileArr[i].pos.y,
    tileArr[i].active,
    tileArr[i].solid,
    tileArr[i].playerSpawn,
    tileArr[i].enemySpawn,
    tileArr[i].weaponBuy,
    tileArr[i].weaponIndex,
    tileArr[i].perkBuy,
    tileArr[i].perkIndex
    );
    if(i < MAXTILES - 1){
      fprintf(file, ";");
    }
  }
  fclose(file);
}

void importMap(Tile *tileArr){
  FILE *file = fopen("../RefactorGame/assets/map1.map", "r");
  if(file == NULL){
    printf("Failed to open map file");
  }

  char *buffer = malloc(sizeof(char) * 2000000);
  if(fgets(buffer, 2000000, file) == NULL){
    printf("Failed to read file");
    fclose(file);
    free(buffer);
    return;
  }
  fclose(file);
  char *token = strtok(buffer, ";");
  int index = 0;
  while(token != NULL && index < MAXTILES){
    int id, textureId, posX, posY, active, solid, playerSpawn, enemySpawn, weaponBuy, weaponIndex, perkBuy, perkIndex;
    sscanf(token, "{%d}{%d}{{%d,%d},{%d},{%d},{%d},{%d},{%d}{%d},{%d}{%d}}", &id, &textureId, &posX, &posY, &active, &solid, 
           &playerSpawn, &enemySpawn, &weaponBuy, &weaponIndex, &perkBuy, &perkIndex);
    tileArr[index].id = id;
    tileArr[index].textureId = textureId;
    tileArr[index].pos.x = posX;
    tileArr[index].pos.y = posY;
    tileArr[index].active = active;
    tileArr[index].solid = solid;
    tileArr[index].playerSpawn = playerSpawn;
    tileArr[index].enemySpawn = enemySpawn;
    tileArr[index].weaponBuy = weaponBuy;
    tileArr[index].weaponIndex = weaponIndex;
    tileArr[index].perkBuy = perkBuy;
    tileArr[index].perkIndex = perkIndex;
    token = strtok(NULL, ";");
    index++;
  }
  printf("Imported Map successfully");
  free(buffer);
}

