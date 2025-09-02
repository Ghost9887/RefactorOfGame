#include "enemy.h"

extern int ENEMYCOUNT;
extern int ALIVEENEMIES;
extern int AMOUNTOFENEMYSPAWNS;

bool checkIfEnemyCanAttack(Enemy *enemy);

Enemy createEmptyEnemy(){
  Enemy enemy;
  enemy.pos = (Vector2){ 0, 0 };
  enemy.velocity = (Vector2){ 0, 0 };
  enemy.width = 0;
  enemy.height = 0;
  enemy.speed = 0.0f;
  enemy.damage = 0;
  enemy.texture = NULL;
  enemy.active = false;
  return enemy;
}

void initEnemyArr(Enemy *enemyArr){
  for(int i = 0; i < MAXSPAWNENEMIES; i++){
    enemyArr[i] = createEmptyEnemy();
  }
}

void spawnEnemies(Enemy *enemyArr, TextureManager *textureManager, RoundManager *roundManager, EnemySpawn *enemySpawnArr){
  if(!roundManager->inBreak && !roundManager->allEnemiesSpawned){
    //create one at a time
    for(int i = 0; i < MAXSPAWNENEMIES; i++){
      if(!enemyArr[i].active){
        //find the enemy spawn with the lowest amount of enemies that have spawned there and spawn a enemy there
        int temp = INT_MAX;
        int index = 0;
        for(int j = 0; j < AMOUNTOFENEMYSPAWNS; j++){
          if(enemySpawnArr[j].amount < temp){
          temp = enemySpawnArr[j].amount;
          index = j;
          }
        }
        enemyArr[i] = createBasicEnemy(textureManager, enemySpawnArr[index].pos.x, enemySpawnArr[index].pos.y);
        enemySpawnArr[index].amount++;
        ENEMYCOUNT++; 
        ALIVEENEMIES++;
        break;
      }
    }
  }
}

void drawEnemy(Enemy *enemy){
  DrawTextureRec(*enemy->texture, enemy->frameRec, enemy->pos, WHITE); 
}

void updateAnimation(Enemy *enemy){
  enemy->frameTime += GetFrameTime();
  if (enemy->frameTime >= enemy->frameSpeed) {
    enemy->frameTime = 0.0f;
    enemy->currentFrame++;
    if (enemy->currentFrame > 2) enemy->currentFrame = 0;
    enemy->frameRec.y = (float)enemy->currentFrame * enemy->frameRec.width;
  }
}

void enemyMovement(Enemy *enemy, Player *player){
  float deltaTime = GetFrameTime();
  float dx = player->pos.x - enemy->pos.x;
  float dy = player->pos.y - enemy->pos.y;
  float length = sqrtf(dx * dx + dy * dy);

  if (length < 0.1f) return;

  float dirX = dx / length;
  float dirY = dy / length;

  //not sure how this works but it does took me 3 hours of trying so im leaving it for now 
  enemy->pos.y += fabs(dirY) * enemy->velocity.y;
  enemy->pos.x += fabs(dirX) * enemy->velocity.x;
  if(dirX > 0) enemy->velocity.x = enemy->speed * deltaTime;
  if(dirX < 0) enemy->velocity.x = -enemy->speed * deltaTime;
  if(dirY > 0) enemy->velocity.y = enemy->speed * deltaTime;
  if(dirY < 0) enemy->velocity.y = -enemy->speed * deltaTime;
}

void checkCollisionWithPlayer(Enemy *enemy, Player *player){
  Rectangle enemyRect = { enemy->pos.x, enemy->pos.y, enemy->width, enemy->height };
  Rectangle playerRect = { player->pos.x, player->pos.y, player->width, player->height };
  if(CheckCollisionRecs(enemyRect, playerRect) && checkIfEnemyCanAttack(enemy)){
    player->health -= enemy->damage;
    enemy->attackTimer = enemy->attackCooldown; 
  }
}

void attackCooldown(Enemy *enemy){
  if(enemy->attackTimer <= 0.01f){
    enemy->attackTimer = 0.0f;
  }
  else{
    enemy->attackTimer -= GetFrameTime();
  }
}

bool checkIfEnemyCanAttack(Enemy *enemy){
  if(enemy->attackTimer < 0.01f){
    return true;
  }
  return false;
}

void destroyEnemy(Enemy *enemy, Player *player, Pickup *pickupArr, TextureManager *textureManager){
  //chance to spawn a pickup
  int randNumber = GetRandomValue(1, 6);
  if(randNumber == 5){
    int pickupNumber = GetRandomValue(1, AMOUNTOFPICKUPS);
    switch(pickupNumber){
      case 1: 
        spawnPickup(pickupArr, "ammo", enemy, player, textureManager);
        break;
      case 2:
        spawnPickup(pickupArr, "health", enemy, player, textureManager);
        break;
      default:
        break;
    }
  }
  enemy->active = false;
  enemy->speed = 0.0f;
  player->money += 80;
  ALIVEENEMIES--;
}

void checkIfEnemyIsDead(Enemy *enemy, Player *player, Pickup *pickupArr, TextureManager *textureManager){
  if(enemy->health <= 0) destroyEnemy(enemy, player, pickupArr, textureManager);
}

void checkEnemyCollisionWithTile(Enemy *enemy, Tile *tile){
  Rectangle tileRec = { tile->pos.x, tile->pos.y, CELLSIZE, CELLSIZE };
  Rectangle futureEnemyXRec = {
    enemy->pos.x + enemy->velocity.x,
    enemy->pos.y,
    enemy->width,
    enemy->height
  };
  if (CheckCollisionRecs(futureEnemyXRec, tileRec)){ 
    enemy->velocity.x = 0.0f;
  }
  Rectangle futureEnemyYRec = {
    enemy->pos.x,
    enemy->pos.y + enemy->velocity.y,
    enemy->width,
    enemy->height
  };
  if (CheckCollisionRecs(futureEnemyYRec, tileRec)){ 
    enemy->velocity.y = 0.0f;
  }
}

void updateEnemies(Enemy *enemyArr, Player *player, RoundManager *roundManager, TextureManager *textureManager, Pickup *pickupArr, EnemySpawn *enemySpawnArr){
  for(int i = 0; i < MAXSPAWNENEMIES; i++){
    if(enemyArr[i].active){
      checkIfEnemyIsDead(&enemyArr[i], player, pickupArr, textureManager);
      enemyMovement(&enemyArr[i], player);
      drawEnemy(&enemyArr[i]);
      updateAnimation(&enemyArr[i]);
      checkCollisionWithPlayer(&enemyArr[i], player);
      attackCooldown(&enemyArr[i]);
    }
  }
  spawnEnemies(enemyArr, textureManager, roundManager, enemySpawnArr);
}
