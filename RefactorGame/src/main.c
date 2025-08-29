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
#include "debugMode.h"
#include "weaponBuy.h"

//GLOBAL VARIABLES
//ENEMY
int ENEMYCOUNT = 0;
int ALIVEENEMIES = 0;

//TILES
int AMOUNTOFTILES = 0;

//debug mode
bool DEBUGMODE = false;
bool ENABLEPLAYERHITBOX = false;
bool ENABLEENEMYHITBOX = false;
bool ENABLESOLIDTILEHITBOX = false;
bool ENABLEWEAPONBUYHITBOX = false;


void updateGameState(Player *player, Camera2D *camera, Enemy* enemyArr, 
                     Projectile *projectileArr, RoundManager *roundManager, TextureManager *textureManager,
                     Tile *tileArr, Texture2D *tileTextureArr, Weapon *weaponHolster, WeaponBuy *weaponBuyArr,
                     Weapon *weaponArr);

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

  Weapon weaponHolster[MAXWEAPONS];
  initWeaponHolster(weaponHolster, weaponArr);

  WeaponBuy weaponBuyArr[AMOUNTOFWEAPONS];
  initWeaponBuyArr(weaponBuyArr, weaponArr);
  
  Projectile projectileArr[MAXPROJECTILES];
  initProjectileArr(projectileArr);

  RoundManager roundManager = createRoundManager();

  AMOUNTOFTILES = getAmountOfTiles();
  Tile *tileArr = (Tile*)malloc(sizeof(Tile) * AMOUNTOFTILES);
  Texture2D tileTextureArr[AMOUNTOFTILETEXTURES];
  initTileArr(tileArr);
  initTileTextureArr(tileTextureArr, &textureManager);

  Player player = createPlayer(&textureManager);
  player.weapon = &weaponHolster[0];
  //****************************************************************************

  //LOAD MAP******************************
  importMap(tileArr);
  //**************************************
  
  //SPAWN OBJECTS*************************
  spawnObjects(tileArr, &player);
  //**************************************
  
  //Toggle Full Screen
  ToggleFullscreen();
    
  while(!WindowShouldClose()){

    BeginDrawing();

      ClearBackground(WHITE);
   
      BeginMode2D(camera);
        
        updateGameState(&player, &camera, enemyArr, projectileArr, &roundManager,
                        &textureManager, tileArr, tileTextureArr, weaponHolster, weaponBuyArr,
                        weaponArr);
      
        updateDebugMode(&player, enemyArr, tileArr, weaponBuyArr);

      EndMode2D();
          
      drawUI(&player, &roundManager);
      
      drawUIForDebugMode();

    EndDrawing();
  }
  
  CloseWindow();
  free(tileArr);
  return 0;
}

void updateGameState(Player *player, Camera2D *camera, Enemy *enemyArr, 
                     Projectile *projectileArr, RoundManager *roundManager, TextureManager *textureManager,
                     Tile *tileArr, Texture2D *tileTextureArr, Weapon *weaponHolster, WeaponBuy *weaponBuyArr,
                     Weapon *weaponArr){
  
  //in order of drawing / operations
  updateMap(tileArr, tileTextureArr, player, enemyArr, projectileArr);

  updateEnemies(enemyArr, player, roundManager, textureManager);

  updateRoundManager(roundManager);
  
  updatePlayer(player, camera, projectileArr, enemyArr, tileArr);

  updateWeapons(player, weaponHolster);

  updateWeaponBuy(weaponBuyArr, weaponArr, weaponHolster, player);

  updateCamera(camera, player);

  updateProjectile(projectileArr, enemyArr, player);

}

