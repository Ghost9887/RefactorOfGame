#include "textureManager.h"


void loadAllTextures(TextureManager *textureManager){
  textureManager->tile1 = LoadTexture("../RefactorGame/assets/tiles/tile1.png");
  textureManager->tile2 = LoadTexture("../RefactorGame/assets/tiles/tile2.png");
  textureManager->tile3 = LoadTexture("../RefactorGame/assets/tiles/tile3.png");
  textureManager->tile4 = LoadTexture("../RefactorGame/assets/tiles/tile4.png");
  textureManager->player = LoadTexture("../RefactorGame/assets/tiles/player.png");
}

