#include "common.h"
#include "texture_manager.h"
#include "player.h"
#include "camera.h"
#include "ui.h"
#include "enemy.h"
#include "weapon.h"
#include "projectile.h"
#include "roundManager.h"
#include "tile.h"
#include "map.h"

//GLOBAL VARIABLES
//ENEMY
int ENEMYCOUNT = 0;
int ALIVEENEMIES = 0;

void updateGameState(Player *player, Camera2D *camera, Enemy* enemyArr, 
                     Projectile *projectileArr, RoundManager *roundManager, TextureManager *textureManager,
                     Tile *tileArr);

int main(){
  
  InitWindow(SCREENWIDTH, SCREENHEIGHT, "Game");
  SetTargetFPS(TARGETFPS);
  HideCursor();

  Camera2D camera;
  initCamera(&camera);


  //GAME OBJECTS
  //****************************************************************************
  TextureManager textureManager;
  loadAllTextures(&textureManager);

  Enemy enemyArr[MAXSPAWNENEMIES];
  initEnemyArr(enemyArr);

  Weapon weaponArr[AMOUNTOFWEAPONS];
  initWeaponArr(weaponArr, &textureManager);

  Projectile projectileArr[MAXPROJECTILES];
  initProjectileArr(projectileArr);

  RoundManager roundManager = createRoundManager();

  Tile tileArr[MAXTILES];
  Texture2D tileTextureArr[AMOUNTOFTILETEXTURES];
  initTileArr(tileArr);
  initTileTextureArr(tileTextureArr, &textureManager);
  
  Player player = createPlayer(&textureManager);
  player.weapon = &weaponArr[0];
  //****************************************************************************

  //LOAD MAP******************************
  importMap(tileArr, tileTextureArr);
  //        ******************************
    
  while(!WindowShouldClose()){
    BeginDrawing();

      ClearBackground(WHITE);
   
      BeginMode2D(camera);
        
        updateGameState(&player, &camera, enemyArr, projectileArr, &roundManager, &textureManager, tileArr);

      EndMode2D();
          
      drawUI(&player, &roundManager);

    EndDrawing();
  }
  
  CloseWindow();

  return 0;
}

void updateGameState(Player *player, Camera2D *camera, Enemy *enemyArr, 
                     Projectile *projectileArr, RoundManager *roundManager, TextureManager *textureManager,
                     Tile *tileArr){
  
  //in order of drawing / operations
  updateMap(tileArr);

  updateEnemies(enemyArr, player, roundManager, textureManager);

  updateRoundManager(roundManager);
  
  updatePlayer(player, camera, projectileArr, enemyArr);

  updateCamera(camera, player);

  updateWeapons(player);

  updateProjectile(projectileArr, enemyArr);

}

