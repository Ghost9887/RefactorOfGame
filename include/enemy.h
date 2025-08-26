#ifndef ENEMY_H
#define ENEMY_H

#include "common.h"
#include "basic_enemy.h"
  
  void initEnemyArr(Enemy *enemyArr);
  void spawnEnemies(Enemy *enemyArr, TextureManager *textureManager);
  void updateEnemies(Enemy *enemyArr, Player *player);

#endif
