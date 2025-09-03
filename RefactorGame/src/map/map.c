#include "map.h"

//special imports
#include <stdlib.h>
#include <string.h>

extern int AMOUNTOFTILES;
extern int AMOUNTOFWEAPONBUYS;
extern int AMOUNTOFPERKBUYS;
extern int AMOUNTOFENEMYSPAWNS;
extern bool DRAWFULLMAP;

int getAmountOfTiles(){
  FILE *file = fopen("../RefactorGame/assets/map1.map", "r");
  if(file == NULL){
    printf("Failed to open file");
    return -1;
  }
  char buffer[500000];
  if(fgets(buffer, sizeof(buffer), file) == NULL){
    printf("Failed to read file");
    fclose(file);
    return -1;
  }
  fclose(file);
  char *token = strtok(buffer, ";");
  int index = 0;
  while(token != NULL && index < MAXTILES){
    int id, posX, posY, active, solid, playerSpawn, enemySpawn, weaponBuy, weaponIndex, perkBuy, perkIndex;
    sscanf(token, "%d{{%d,%d},{%d},{%d},{%d},{%d},{%d}{%d},{%d}{%d}}", &id, &posX, &posY, &active, &solid, 
           &playerSpawn, &enemySpawn, &weaponBuy, &weaponIndex, &perkBuy, &perkIndex);
    if(active == true){
      index++;
    }
    token = strtok(NULL, ";");
  }
  printf("\n%d\n", index);
  return index;
}

void importMap(Tile *tileArr){
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

void drawTiles(Tile *tileArr, Texture2D *tileTextureArr, Player *player, Enemy *enemyArr, Projectile *projectileArr, Chunk *chunkArr, Camera2D *camera){ 
  if(!DRAWFULLMAP){
    int arr[AMOUNTOFCHUNKS];
    int chunkCount = findChunksInCameraView(arr, chunkArr, camera);
    for(int i = 0; i < chunkCount; i++){
      int chunkIndex = arr[i];
      for(int j = 0; j < chunkArr[chunkIndex].tileCount; j++){
        DrawTexture(tileTextureArr[chunkArr[chunkIndex].tileArr[j].id], chunkArr[chunkIndex].tileArr[j].pos.x, chunkArr[chunkIndex].tileArr[j].pos.y, WHITE);
        //check for collision so here so we dont have to iterate through another loop
        if(chunkArr[chunkIndex].tileArr[j].solid){
          checkPlayerCollisionWithTile(player, &chunkArr[chunkIndex].solidTileArr[j]);
          checkEnemyCollisionWithTile(enemyArr, &chunkArr[chunkIndex].solidTileArr[j]);
          checkProjectileCollisionWithTile(projectileArr, &chunkArr[chunkIndex].solidTileArr[j], enemyArr, player, tileArr);
        }
      }
    }
    playerADS(player, enemyArr, chunkArr, chunkCount);
  }else{
    for(int i = 0; i < AMOUNTOFTILES; i++){
      DrawTexture(tileTextureArr[tileArr[i].id], tileArr[i].pos.x, tileArr[i].pos.y, WHITE);  
    }
  }
}

void checkCollisionWithTiles(Enemy *enemyArr, Chunk *chunkArr){
  int arr[AMOUNTOFCHUNKS];
  for(int i = 0; i < MAXSPAWNENEMIES; i++){
    int chunkCount = findChunksForEnemy(arr, chunkArr, &enemyArr[i]);
    for(int j = 0; j < chunkCount; j++){
      int chunkIndex = arr[j];
      for(int k = 0; k < chunkArr[chunkIndex].solidTileCount; k++){
        checkEnemyCollisionWithTile(&enemyArr[i], &chunkArr[chunkIndex].solidTileArr[k]);
      }
    }
  }
}

void updateMap(Tile *tileArr, Texture2D *tileTextureArr, Player *player, Enemy *enemyArr, Projectile *projectileArr, Chunk *chunkArr, Camera2D *camera){
  drawTiles(tileArr, tileTextureArr, player, enemyArr, projectileArr, chunkArr, camera);
  checkCollisionWithTiles(enemyArr, chunkArr);
}
