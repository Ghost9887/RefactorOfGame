#include "texture_manager.h"

void loadAllTextures(TextureManager *textureManager){
  textureManager->playerTexture = LoadTexture("assets/player/player.png");
  textureManager->basicEnemyTexture = LoadTexture("assets/enemy/basic_enemy.png");
  textureManager->pistolTexture = LoadTexture("assets/weapons/pistol.png");
}
