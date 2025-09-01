#include "enemySpawn.h"

extern int AMOUNTOFENEMYSPAWNS;

EnemySpawn createEmptyEnemySpawn(){
  EnemySpawn enemySpawn;
  enemySpawn.amount = 0;
  enemySpawn.pos = (Vector2){ 0, 0 };
  return enemySpawn;
}

void initEnemySpawnArr(EnemySpawn *enemySpawnArr){
  for(int i = 0; i < MAXENEMYSPAWNS; i++){
    enemySpawnArr[i] = createEmptyEnemySpawn();
  }
}

void createEnemySpawn(float x, float y, EnemySpawn *enemySpawnArr){
  EnemySpawn enemySpawn;
  enemySpawn.amount = 0;
  enemySpawn.pos = (Vector2){ x, y };
  enemySpawnArr[AMOUNTOFENEMYSPAWNS] = enemySpawn;
}
