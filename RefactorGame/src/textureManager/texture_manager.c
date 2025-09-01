#include "texture_manager.h"

void loadAllTextures(TextureManager *textureManager){
  textureManager->playerTexture = LoadTexture("assets/player/player.png");
  textureManager->basicEnemyTexture = LoadTexture("assets/enemy/basic_enemy.png");
  textureManager->pistolTexture = LoadTexture("assets/weapons/pistol.png");
  textureManager->arTexture = LoadTexture("assets/weapons/ar.png");
  textureManager->rpgTexture = LoadTexture("assets/weapons/rpg.png");
  textureManager->shotgunTexture = LoadTexture("assets/weapons/shotgun.png");
  textureManager->tile1 = LoadTexture("assets/tiles/tile1.png");
  textureManager->tile2 = LoadTexture("assets/tiles/tile2.png");
  textureManager->tile3 = LoadTexture("assets/tiles/tile3.png");
  textureManager->tile4 = LoadTexture("assets/tiles/tile4.png");
  textureManager->tile5 = LoadTexture("assets/tiles/tile5.png");
  textureManager->tile6 = LoadTexture("assets/tiles/tile6.png");
  textureManager->tile7 = LoadTexture("assets/tiles/tile7.png");
  textureManager->tile8 = LoadTexture("assets/tiles/tile8.png");
  textureManager->tile9 = LoadTexture("assets/tiles/tile9.png");
  textureManager->tile10 = LoadTexture("assets/tiles/tile10.png");
  textureManager->tile11 = LoadTexture("assets/tiles/tile11.png");
  textureManager->tile12 = LoadTexture("assets/tiles/tile12.png");
  textureManager->tile13 = LoadTexture("assets/tiles/tile13.png");
  textureManager->tile14 = LoadTexture("assets/tiles/tile14.png");
  textureManager->tile15 = LoadTexture("assets/tiles/tile15.png");
  textureManager->ammoPickupTexture = LoadTexture("assets/pickups/ammo.png");
  textureManager->healthPickupTexture = LoadTexture("assets/pickups/health.png");
  textureManager->healthPerkTexture = LoadTexture("assets/perks/health.png");
  textureManager->speedPerkTexture = LoadTexture("assets/perks/speed.png");
}
