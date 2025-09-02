#include "map.h"

//special imports
#include <stdlib.h>
#include <string.h>

extern int AMOUNTOFTILES;
extern int AMOUNTOFSOLIDTILES;
extern int AMOUNTOFWEAPONBUYS;
extern int AMOUNTOFPERKBUYS;
extern int AMOUNTOFENEMYSPAWNS;

void getAmountOfTiles(){
  FILE *file = fopen("../RefactorGame/assets/map1.map", "r");
  if(file == NULL){
    printf("Failed to open file");
    return;
  }
  char buffer[500000];
  if(fgets(buffer, sizeof(buffer), file) == NULL){
    printf("Failed to read file");
    fclose(file);
    return;
  }
  fclose(file);
  char *token = strtok(buffer, ";");
  int index = 0;
  while(token != NULL && index < MAXTILES){
    int id, posX, posY, active, solid, playerSpawn, enemySpawn, weaponBuy, weaponIndex, perkBuy, perkIndex;
    sscanf(token, "%d{{%d,%d},{%d},{%d},{%d},{%d},{%d}{%d},{%d}{%d}}", &id, &posX, &posY, &active, &solid, 
           &playerSpawn, &enemySpawn, &weaponBuy, &weaponIndex, &perkBuy, &perkIndex);
    if(active == true){
      AMOUNTOFTILES++;
      index++;
      if(solid == true){
        AMOUNTOFSOLIDTILES++;
      }
    }
    token = strtok(NULL, ";");
  }
}

void importMap(Tile *tileArr, Tile *solidTileArr){
 FILE *file = fopen("assets/map1.map", "r");
  if(file == NULL){
    printf("Failed to open map file");
    return;
  }

  char buffer[500000];
  if(fgets(buffer, sizeof(buffer), file) == NULL){
    printf("Failed to read file");
    fclose(file);
    return;
  }
  fclose(file);
  char *token = strtok(buffer, ";");
  int index = 0;
  int solidIndex = 0;
  while(token != NULL && index < AMOUNTOFTILES){
    int id, posX, posY, active, solid, playerSpawn, enemySpawn, weaponBuy, weaponIndex, perkBuy, perkIndex;
    sscanf(token, "%d{{%d,%d},{%d},{%d},{%d},{%d},{%d}{%d},{%d}{%d}}", &id, &posX, &posY, &active, &solid, 
           &playerSpawn, &enemySpawn, &weaponBuy, &weaponIndex, &perkBuy, &perkIndex);
    tileArr[index].id = id;
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
    if(tileArr[index].solid) {
    solidTileArr[solidIndex] = tileArr[index];
    solidIndex++;
    }
    token = strtok(NULL, ";");
    index++;
  }
  printf("Imported Map successfully");
}

//spawning stuff 
void spawnObjects(Tile *tileArr, Player *player, Weapon *weaponArr, WeaponBuy *weaponBuyArr, Perk *perkArr, PerkBuy *perkBuyArr, EnemySpawn *enemySpawnArr){
  for(int i = 0; i < AMOUNTOFTILES; i++){
    if(tileArr[i].playerSpawn){
      player->pos = tileArr[i].pos;
    }
    else if(tileArr[i].enemySpawn){
      createEnemySpawn(tileArr[i].pos.x, tileArr[i].pos.y, enemySpawnArr);
      AMOUNTOFENEMYSPAWNS++;
    }
    else if(tileArr[i].weaponBuy){
      createWeaponBuy(weaponBuyArr, weaponArr, tileArr[i].weaponIndex, tileArr[i].pos.x, tileArr[i].pos.y);
      AMOUNTOFWEAPONBUYS++;
    }
    else if(tileArr[i].perkBuy){
      createPerkBuy(perkBuyArr, perkArr, tileArr[i].perkIndex, tileArr[i].pos.x, tileArr[i].pos.y);
      AMOUNTOFPERKBUYS++;
    }
  } 
}

void drawTiles(Texture2D *tileTextureArr, Chunk *chunkArr, Camera2D *camera){
  int visibleChunks[AMOUNTOFCHUNKS];
  int chunkCount = findChunksInCameraView(visibleChunks, chunkArr, camera);
  for(int i = 0; i < chunkCount; i++){
    int chunkId = visibleChunks[i];
    for(int j = 0; j < chunkArr[chunkId].tileCount; j++){
        DrawTexture(tileTextureArr[chunkArr[chunkId].tileArr[j].id], chunkArr[chunkId].tileArr[j].pos.x, chunkArr[chunkId].tileArr[j].pos.y, WHITE);
    }
  }
}

void checkCollisionWithTiles(Tile *solidTileArr, Player *player, Enemy *enemyArr, Tile *tileArr, Projectile *projectileArr){
  for(int i = 0; i < AMOUNTOFSOLIDTILES; i++){
    checkPlayerCollisionWithTile(player, &solidTileArr[i]);
    checkEnemyCollisionWithTile(enemyArr, &solidTileArr[i]);
    checkProjectileCollisionWithTile(projectileArr, &solidTileArr[i], enemyArr, player, tileArr);
  }
}
  

void updateMap(Tile *tileArr, Texture2D *tileTextureArr, Player *player, Enemy *enemyArr, Projectile *projectileArr, Chunk *chunkArr, Camera2D *camera, Tile *solidTileArr){
  drawTiles(tileTextureArr, chunkArr, camera);
  checkCollisionWithTiles(solidTileArr, player, enemyArr, tileArr, projectileArr);
}
