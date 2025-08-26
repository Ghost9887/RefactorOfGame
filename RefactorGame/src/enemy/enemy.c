#include "enemy.h"

extern int ENEMYCOUNT;
extern int ALIVEENEMIES;

bool checkIfEnemyCanAttack(Enemy *enemy);

Enemy createEmptyEnemy(){
  Enemy enemy;
  enemy.pos = (Vector2){ 0, 0 };
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

void spawnEnemies(Enemy *enemyArr, TextureManager *textureManager, RoundManager *roundManager){
  if(!roundManager->inBreak && !roundManager->allEnemiesSpawned){
    //create one at a time
    for(int i = 0; i < MAXSPAWNENEMIES; i++){
      if(!enemyArr[i].active){
        //will change to spawn points later
        float x = (float)GetRandomValue(0, SCREENWIDTH);
        float y = (float)GetRandomValue(0, SCREENHEIGHT);
        enemyArr[i] = createBasicEnemy(textureManager, x, y);
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
  enemy->pos.x += dirX * enemy->speed * deltaTime;
  enemy->pos.y += dirY * enemy->speed * deltaTime;
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

void destroyEnemy(Enemy *enemy){
  enemy->active = false;
  enemy->speed = 0.0f;
  ALIVEENEMIES--;
}

void checkIfEnemyIsDead(Enemy *enemy){
  if(enemy->health <= 0) destroyEnemy(enemy);
}

void updateEnemies(Enemy *enemyArr, Player *player, RoundManager *roundManager, TextureManager *textureManager){
  for(int i = 0; i < MAXSPAWNENEMIES; i++){
    if(enemyArr[i].active){
      checkIfEnemyIsDead(&enemyArr[i]);
      enemyMovement(&enemyArr[i], player);
      drawEnemy(&enemyArr[i]);
      updateAnimation(&enemyArr[i]);
      checkCollisionWithPlayer(&enemyArr[i], player);
      attackCooldown(&enemyArr[i]);
    }
  }
  spawnEnemies(enemyArr, textureManager, roundManager);
}
