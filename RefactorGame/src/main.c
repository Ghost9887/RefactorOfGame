#include "common.h"
#include "texture_manager.h"
#include "player.h"
#include "camera.h"
#include "ui.h"
#include "enemy.h"
#include "weapon.h"
#include "projectile.h"

void updateGameState(Player *player, Camera2D *camera, Enemy* enemyArr, Projectile *projectileArr);

int main(){
  
  InitWindow(SCREENWIDTH, SCREENHEIGHT, "Game");
  SetTargetFPS(TARGETFPS);
  HideCursor();

  Camera2D camera;
  initCamera(&camera);
  
  //Texture Manager
  TextureManager textureManager;
  loadAllTextures(&textureManager);

  Enemy enemyArr[MAXSPAWNENEMIES];
  initEnemyArr(enemyArr);
  spawnEnemies(enemyArr, &textureManager);

  Weapon weaponArr[AMOUNTOFWEAPONS];
  initWeaponArr(weaponArr, &textureManager);

  Projectile projectileArr[MAXPROJECTILES];
  initProjectileArr(projectileArr);
  
  Player player = createPlayer(&textureManager);
  player.weapon = &weaponArr[0];
    
  while(!WindowShouldClose()){
    BeginDrawing();

      ClearBackground(WHITE);
      
      drawUI(&player);
    
      BeginMode2D(camera);
        
        DrawRectangle(500, 500, 50, 50, RED);

        updateGameState(&player, &camera, enemyArr, projectileArr);

      EndMode2D();

    EndDrawing();
  }
  
  CloseWindow();

  return 0;
}

void updateGameState(Player *player, Camera2D *camera, Enemy *enemyArr, Projectile *projectileArr){
  
  //in order of drawing
  updateEnemies(enemyArr, player);

  updatePlayer(player, camera, projectileArr, enemyArr);

  updateCamera(camera, player);

  updateWeapons(player);

  updateProjectile(projectileArr, enemyArr);

}

