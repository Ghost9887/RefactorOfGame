#include "texture_manager.h"

void loadAllTextures(TextureManager *textureManager){
  textureManager->playerTexture = LoadTexture("assets/player/player.png");
  textureManager->basicEnemyTexture = LoadTexture("assets/enemy/basic_enemy.png");
  textureManager->pistolTexture = LoadTexture("assets/weapons/pistol.png");
  textureManager->arTexture = LoadTexture("assets/weapons/ar.png");
  textureManager->rpgTexture = LoadTexture("assets/weapons/rpg.png");
  textureManager->tile1 = LoadTexture("assets/tiles/tile1.png");
  textureManager->tile2 = LoadTexture("assets/tiles/tile2.png");
  textureManager->tile3 = LoadTexture("assets/tiles/tile3.png");
  textureManager->tile4 = LoadTexture("assets/tiles/tile4.png");
}
