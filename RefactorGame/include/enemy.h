#ifndef ENEMY_H
#define ENEMY_H

#include "common.h"
#include "basic_enemy.h"
#include "enemySpawn.h"
#include "pickup.h"
  
  void initEnemyArr(Enemy *enemyArr);
  void spawnEnemies(Enemy *enemyArr, TextureManager *textureManager, RoundManager *roundManager, EnemySpawn *enemySpawnArr);
  void updateEnemies(Enemy *enemyArr, Player *player, RoundManager *roundManager, TextureManager *textureManager, Pickup *pickupArr, EnemySpawn *enemySpawnArr);
  void checkEnemyCollisionWithTile(Enemy *enemyArr, Tile *tile);

#endif
