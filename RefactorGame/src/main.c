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
#include "map.h"
#include "debugMode.h"
#include "weaponBuy.h"
#include "pickup.h"
#include "perk.h"
#include "perkBuy.h"
#include "chunk.h"

//GLOBAL VARIABLES
//ENEMY
int ENEMYCOUNT = 0;
int ALIVEENEMIES = 0;
int AMOUNTOFENEMYSPAWNS = 0;

//TILES
int AMOUNTOFTILES = 0;
int AMOUNTOFSOLIDTILES = 0;

//debug mode
bool DEBUGMODE = false;
bool ENABLEPLAYERHITBOX = false;
bool ENABLEENEMYHITBOX = false;
bool ENABLESOLIDTILEHITBOX = false;
bool ENABLEWEAPONBUYHITBOX = false;
bool ENABLEPERKBUYHITBOX = false;
bool ENABLECHUNKHITBOX = false;

//weapon buys
int AMOUNTOFWEAPONBUYS = 0;

//perk buys
int AMOUNTOFPERKBUYS = 0;

void updateGameState(Player *player, Camera2D *camera, Enemy* enemyArr, 
                     Projectile *projectileArr, RoundManager *roundManager, TextureManager *textureManager,
                     Tile *tileArr, Texture2D *tileTextureArr, Weapon *weaponHolster, WeaponBuy *weaponBuyArr,
                     Weapon *weaponArr, Pickup *pickupArr, PerkBuy *perkBuyArr, EnemySpawn *enemySpawnArr,
                     Chunk *chunkArr, Tile *solidTileArr);

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

  //adds the appropriate tiles to the arrays
  getAmountOfTiles();
  Tile *tileArr = (Tile*)malloc(sizeof(Tile) * AMOUNTOFTILES);
  Tile *solidTileArr = (Tile*)malloc(sizeof(Tile) * AMOUNTOFSOLIDTILES);
  Texture2D tileTextureArr[AMOUNTOFTILETEXTURES];
  initTileArr(tileArr);
  initSolidTileArr(solidTileArr);
  initTileTextureArr(tileTextureArr, &textureManager);

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
  importMap(tileArr, solidTileArr);
  //**************************************

  //CHUNK THE MAP*************************
  Chunk chunkArr[AMOUNTOFCHUNKS];
  initChunkArr(chunkArr, tileArr);
  //**************************************
  
  //SPAWN OBJECTS*************************
  spawnObjects(tileArr, &player, weaponArr, weaponBuyArr, perkArr, perkBuyArr, enemySpawnArr);
  //**************************************
  
  //Toggle Full Screen
  ToggleFullscreen();
    
  while(!WindowShouldClose()){

    BeginDrawing();

      ClearBackground(GREEN);
   
      BeginMode2D(camera);
        
        updateGameState(&player, &camera, enemyArr, projectileArr, &roundManager,
                        &textureManager, tileArr, tileTextureArr, weaponHolster, weaponBuyArr,
                        weaponArr, pickupArr, perkBuyArr, enemySpawnArr, chunkArr, solidTileArr);
      
        updateDebugMode(&player, enemyArr, tileArr, solidTileArr, weaponBuyArr, perkBuyArr, chunkArr);

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
                     Weapon *weaponArr, Pickup *pickupArr, PerkBuy *perkBuyArr, EnemySpawn *enemySpawnArr,
                     Chunk *chunkArr, Tile *solidTileArr){
  
  //in order of drawing / operations
  updateMap(tileArr, tileTextureArr, player, enemyArr, projectileArr, chunkArr, camera, solidTileArr);

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

