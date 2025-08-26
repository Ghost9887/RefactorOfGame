#include "common.h"
#include "texture_manager.h"
#include "player.h"
#include "camera.h"
#include "ui.h"
#include "enemy.h"
#include "weapon.h"
#include "projectile.h"
#include "roundManager.h"

//GLOBAL VARIABLES
//ENEMY
int ENEMYCOUNT = 0;
int ALIVEENEMIES = 0;

void updateGameState(Player *player, Camera2D *camera, Enemy* enemyArr, 
                     Projectile *projectileArr, RoundManager *roundManager, TextureManager *textureManager);

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
  
  Player player = createPlayer(&textureManager);
  player.weapon = &weaponArr[0];
  //****************************************************************************
  
    
  while(!WindowShouldClose()){
    BeginDrawing();

      ClearBackground(WHITE);
      
      drawUI(&player, &roundManager);
    
      BeginMode2D(camera);
        
        DrawRectangle(500, 500, 50, 50, RED);

        updateGameState(&player, &camera, enemyArr, projectileArr, &roundManager, &textureManager);

      EndMode2D();

    EndDrawing();
  }
  
  CloseWindow();

  return 0;
}

void updateGameState(Player *player, Camera2D *camera, Enemy *enemyArr, 
                     Projectile *projectileArr, RoundManager *roundManager, TextureManager *textureManager){
  
  //in order of drawing / operations
  updateEnemies(enemyArr, player, roundManager, textureManager);

  updateRoundManager(roundManager);
  
  updatePlayer(player, camera, projectileArr, enemyArr);

  updateCamera(camera, player);

  updateWeapons(player);

  updateProjectile(projectileArr, enemyArr);

}

