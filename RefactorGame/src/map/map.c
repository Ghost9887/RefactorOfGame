#include "map.h"

//special imports
#include <stdlib.h>
#include <string.h>

extern int AMOUNTOFTILES;
extern int AMOUNTOFSOLIDTILES;
extern int AMOUNTOFWEAPONBUYS;
extern int AMOUNTOFPERKBUYS;
extern int AMOUNTOFENEMYSPAWNS;
extern bool DRAWFULLMAP;

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

void drawTiles(Texture2D *tileTextureArr, Chunk *chunkArr, Camera2D *camera, Tile *tileArr, Player *player, Projectile *projectileArr, Enemy *enemyArr){
  if(!DRAWFULLMAP){
    int visibleChunks[AMOUNTOFCHUNKS];
    int chunkCount = findChunksInCameraView(visibleChunks, chunkArr, camera);
    for(int i = 0; i < chunkCount; i++){
      int chunkId = visibleChunks[i];
      for(int j = 0; j < chunkArr[chunkId].tileCount; j++){
        DrawTexture(tileTextureArr[chunkArr[chunkId].tileArr[j].id], chunkArr[chunkId].tileArr[j].pos.x, chunkArr[chunkId].tileArr[j].pos.y, WHITE);
        if(chunkArr[chunkId].tileArr[j].solid){
          checkPlayerCollisionWithTile(player, &chunkArr[chunkId].tileArr[j]);
          checkProjectileCollisionWithTile(projectileArr, &chunkArr[chunkId].tileArr[j], enemyArr, player, tileArr);
        }
      }
    }
  }else{
    for(int i = 0; i < AMOUNTOFTILES; i++){
      DrawTexture(tileTextureArr[tileArr[i].id], tileArr[i].pos.x, tileArr[i].pos.y, WHITE);
    }
  }
}

//the enemies always need to check so they dont go through walls
//TODO: add tile caching still very slooooow
void checkCollisionWithTiles(Tile *solidTileArr, Enemy *enemyArr, Chunk *chunkArr){
  for(int i = 0; i < MAXSPAWNENEMIES; i++){
    int visibleChunks[AMOUNTOFCHUNKS];
    int chunkCount = findChunksForEnemy(visibleChunks, chunkArr, &enemyArr[i]);
    for(int x = 0; x < chunkCount; x++){
      int chunkId = visibleChunks[x];
      for(int j = 0; j < chunkArr[chunkId].solidTileCount; j++){
        checkEnemyCollisionWithTile(&enemyArr[i], &chunkArr[chunkId].solidTileArr[j]);
      }
    }
  }
}
  

void updateMap(Tile *tileArr, Texture2D *tileTextureArr, Player *player, Enemy *enemyArr, Projectile *projectileArr, Chunk *chunkArr, Camera2D *camera, Tile *solidTileArr){
  drawTiles(tileTextureArr, chunkArr, camera, tileArr, player, projectileArr, enemyArr);
  checkCollisionWithTiles(solidTileArr, enemyArr, chunkArr);
}
