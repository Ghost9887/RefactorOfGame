#include "textureManager.h"


void loadAllTextures(TextureManager *textureManager){
  textureManager->tile1 = LoadTexture("../RefactorGame/assets/tiles/tile1.png");
  textureManager->tile2 = LoadTexture("../RefactorGame/assets/tiles/tile2.png");
  textureManager->tile3 = LoadTexture("../RefactorGame/assets/tiles/tile3.png");
  textureManager->tile4 = LoadTexture("../RefactorGame/assets/tiles/tile4.png");
  
  textureManager->tile5 = LoadTexture("../RefactorGame/assets/tiles/tile5.png");
  textureManager->tile6 = LoadTexture("../RefactorGame/assets/tiles/tile6.png");
  textureManager->tile7 = LoadTexture("../RefactorGame/assets/tiles/tile7.png");
  textureManager->tile8 = LoadTexture("../RefactorGame/assets/tiles/tile8.png");

  textureManager->tile9 = LoadTexture("../RefactorGame/assets/tiles/tile9.png");
  textureManager->tile10 = LoadTexture("../RefactorGame/assets/tiles/tile10.png");
  textureManager->tile11 = LoadTexture("../RefactorGame/assets/tiles/tile11.png");
  textureManager->tile12 = LoadTexture("../RefactorGame/assets/tiles/tile12.png");

  textureManager->tile13 = LoadTexture("../RefactorGame/assets/tiles/tile13.png");
  textureManager->tile14 = LoadTexture("../RefactorGame/assets/tiles/tile14.png");
  textureManager->tile15 = LoadTexture("../RefactorGame/assets/tiles/tile15.png");

  textureManager->player = LoadTexture("../RefactorGame/assets/tiles/player.png");
  textureManager->enemy = LoadTexture("../RefactorGame/assets/tiles/enemy.png");
  textureManager->pistol = LoadTexture("../RefactorGame/assets/tiles/pistol.png");
  textureManager->ar = LoadTexture("../RefactorGame/assets/tiles/ar.png");
  textureManager->rpg = LoadTexture("../RefactorGame/assets/tiles/rpg.png");
  textureManager->shotgun = LoadTexture("../RefactorGame/assets/tiles/shotgun.png");
  textureManager->healthPerk = LoadTexture("../RefactorGame/assets/tiles/health.png");
  textureManager->speedPerk = LoadTexture("../RefactorGame/assets/tiles/speed.png");
}

