#include "common.h"
#include "texture_manager.h"
#include "player.h"
#include "camera.h"
#include "ui.h"
#include "enemy.h"
#include "enemySpawn.h"
#include "weapon.h"
#include "projectile.h"
#include "roundManager.h"
#include "tile.h"
#include "chunk.h"
#include "map.h"
#include "debugMode.h"
#include "weaponBuy.h"
#include "pickup.h"
#include "perk.h"
#include "perkBuy.h"

//GLOBAL VARIABLES
//ENEMY
int ENEMYCOUNT = 0;
int ALIVEENEMIES = 0;
int AMOUNTOFENEMYSPAWNS = 0;

//debug mode
bool DEBUGMODE = false;
bool ENABLEPLAYERHITBOX = false;
bool ENABLEENEMYHITBOX = false;
bool ENABLESOLIDTILEHITBOX = false;
bool ENABLEWEAPONBUYHITBOX = false;
bool ENABLEPERKBUYHITBOX = false;
bool ENABLECHUNKHITBOX = false;
bool DRAWFULLMAP = false;

//weapon buys
int AMOUNTOFWEAPONBUYS = 0;

//perk buys
int AMOUNTOFPERKBUYS = 0;

void updateGameState(Player *player, Camera2D *camera, Enemy* enemyArr, 
                     Projectile *projectileArr, RoundManager *roundManager, TextureManager *textureManager,
                     Tile *tileArr, Texture2D *tileTextureArr, Weapon *weaponHolster, WeaponBuy *weaponBuyArr,
                     Weapon *weaponArr, Pickup *pickupArr, PerkBuy *perkBuyArr, EnemySpawn *enemySpawnArr, Chunk *chunkArr);

int main(){
  
  InitWindow(SCREENWIDTH, SCREENHEIGHT, "Game");
  SetTargetFPS(TARGETFPS);
  HideCursor();

  Camera2D camera;
  initCamera(&camera);

  //GAME OBJECTS
  //****************************************************************************
  //USING FIXED ARRAYS FOR EVERYTHING EXCEPT TILES NOT SURE IF THIS IS THE BEST WAY IN C
  TextureManager textureManager;
  loadAllTextures(&textureManager);

  printf("before tileArr\n");
  Tile *tileArr = (Tile*)malloc(sizeof(Tile) * MAXTILES);
  Texture2D tileTextureArr[AMOUNTOFTILETEXTURES];
  initTileArr(tileArr);
  initTileTextureArr(tileTextureArr, &textureManager);

  printf("after init all tiels/textures arr\n");

  Enemy enemyArr[MAXSPAWNENEMIES];
  initEnemyArr(enemyArr);

  EnemySpawn enemySpawnArr[MAXENEMYSPAWNS];
  initEnemySpawnArr(enemySpawnArr);

  Weapon weaponArr[AMOUNTOFWEAPONS];
  initWeaponArr(weaponArr, &textureManager);

  Weapon weaponHolster[MAXWEAPONS];
  initWeaponHolster(weaponHolster, weaponArr);

  WeaponBuy weaponBuyArr[MAXWEAPONBUYS];
  initWeaponBuyArr(weaponBuyArr);

  Projectile projectileArr[MAXPROJECTILES];
  initProjectileArr(projectileArr);

  RoundManager roundManager = createRoundManager();

  Chunk chunkArr[AMOUNTOFCHUNKS];

  Pickup pickupArr[MAXPICKUPS];
  initPickupArr(pickupArr);

  Perk perkArr[AMOUNTOFPERKS];
  initPerkArr(perkArr, &textureManager);

  PerkBuy perkBuyArr[MAXPERKBUYS];
  initPerkBuyArr(perkBuyArr);

  Player player = createPlayer(&textureManager);
  player.weapon = &weaponHolster[0];
  //****************************************************************************

  //LOAD MAP******************************
  printf("before import map\n");
  importMap(tileArr);
  printf("after import map\n");
  //**************************************

  //POPULATE THE CHUNKS*******************
  printf("before init chunk\n");
  initChunkArr(chunkArr, tileArr);
  printf("after init chunkn\n");
  //**************************************

  //SPAWN OBJECTS*************************
  spawnObjects(tileArr, &player, weaponArr, weaponBuyArr, perkArr, perkBuyArr, enemySpawnArr);
  //**************************************
  
  printf("perkBuy count: %d\n", AMOUNTOFPERKBUYS);
  printf("enemyspawn count: %d\n", AMOUNTOFENEMYSPAWNS);
  
  //Toggle Full Screen
  ToggleFullscreen();
    
  while(!WindowShouldClose()){

    BeginDrawing();

      ClearBackground(GREEN);
   
      BeginMode2D(camera);
        
        updateGameState(&player, &camera, enemyArr, projectileArr, &roundManager,
                        &textureManager, tileArr, tileTextureArr, weaponHolster, weaponBuyArr,
                        weaponArr, pickupArr, perkBuyArr, enemySpawnArr, chunkArr);
      
        updateDebugMode(&player, enemyArr, tileArr, weaponBuyArr, perkBuyArr, chunkArr);

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
                     Weapon *weaponArr, Pickup *pickupArr, PerkBuy *perkBuyArr, EnemySpawn *enemySpawnArr, Chunk *chunkArr){
  
  //in order of drawing / operations
  updateMap(tileArr, tileTextureArr, player, enemyArr, projectileArr, chunkArr, camera);

  updateEnemies(enemyArr, player, roundManager, textureManager, pickupArr, enemySpawnArr);

  updateRoundManager(roundManager);
  
  updatePlayer(player, camera, projectileArr, enemyArr, tileArr);

  updateWeapons(player, weaponHolster);

  updateWeaponBuy(weaponBuyArr, weaponArr, weaponHolster, player);

  updatePickups(pickupArr, player);

  updatePerkBuys(perkBuyArr, player);

  updateCamera(camera, player);

  updateProjectile(projectileArr, enemyArr, player, tileArr);

}

