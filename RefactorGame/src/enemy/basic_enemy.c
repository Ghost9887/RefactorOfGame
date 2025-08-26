#include "basic_enemy.h"

Enemy createBasicEnemy(TextureManager *textureManager, float x, float y){
  Enemy enemy;
  enemy.pos = (Vector2){ x, y };
  enemy.width = 64;
  enemy.height = 64;
  enemy.speed = 100.0f;
  enemy.damage = 25;
  enemy.health = 100;
  enemy.texture = &textureManager->basicEnemyTexture;
  enemy.attackCooldown = 1.5f;
  enemy.attackTimer = 0.0f;
  enemy.amountOfFrames = 2;
  enemy.currentFrame = 0;
  enemy.frameTime = 0.0f;
  enemy.frameSpeed = 0.3f;
  enemy.frameRec = (Rectangle){ 0, 0, 64, 64 };
  enemy.active = true;
  return enemy;
}
