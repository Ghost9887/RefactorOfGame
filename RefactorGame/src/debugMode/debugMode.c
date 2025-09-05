#include "debugMode.h"

extern bool DEBUGMODE;
extern bool ENABLEPLAYERHITBOX;
extern bool ENABLEENEMYHITBOX;
extern bool ENABLESOLIDTILEHITBOX;
extern bool ENABLEWEAPONBUYHITBOX;
extern bool ENABLEPERKBUYHITBOX;
extern bool ENABLECHUNKHITBOX;
extern int AMOUNTOFWEAPONBUYS;
extern int AMOUNTOFPERKBUYS;

void enableDebugMode(){
  if(IsKeyPressed(KEY_I)){
    DEBUGMODE = !DEBUGMODE; 
  }
}

void drawDebugStuff(Player *player, Enemy *enemyArr, Tile *tileArr, WeaponBuy *weaponBuyArr, PerkBuy *perkBuyArr, Chunk *chunkArr){
  if(ENABLEPLAYERHITBOX){
    DrawRectangleLines(player->pos.x, player->pos.y, player->width, player->height, RED);
  }
  if(ENABLEENEMYHITBOX){
    for(int i = 0; i < MAXSPAWNENEMIES; i++){
      if(enemyArr[i].active){
        DrawRectangleLines(enemyArr[i].pos.x, enemyArr[i].pos.y, enemyArr[i].width, enemyArr[i].height, RED);
      }
    }
  }
  if(ENABLESOLIDTILEHITBOX){
    for(int i = 0; i < MAXTILES; i++){
      if(tileArr[i].active && tileArr[i].solid){
        DrawRectangleLines(tileArr[i].pos.x, tileArr[i].pos.y, CELLSIZE, CELLSIZE, RED);
      }
    }
  }
  if(ENABLEWEAPONBUYHITBOX){
    for(int i = 0; i < AMOUNTOFWEAPONBUYS; i++){
      DrawRectangleLines(weaponBuyArr[i].pos.x, weaponBuyArr[i].pos.y, weaponBuyArr[i].width, weaponBuyArr[i].height, RED);
    }
  }
  if(ENABLEPERKBUYHITBOX){
    for(int i = 0; i < AMOUNTOFPERKBUYS; i++){
      DrawRectangleLines(perkBuyArr[i].pos.x, perkBuyArr[i].pos.y, perkBuyArr[i].width * perkBuyArr[i].scale, perkBuyArr[i].height * perkBuyArr[i].scale, RED);
    }
  }
  if(ENABLECHUNKHITBOX){
    for(int i = 0; i < AMOUNTOFCHUNKS; i++){
      DrawRectangleLines(chunkArr[i].startX, chunkArr[i].startY, 1600, 1600, RED);
    }
  }
}

void updateDebugMode(Player *player, Enemy *enemyArr, Tile *tileArr, WeaponBuy *weaponBuyArr, PerkBuy *perkBuyArr, Chunk *chunkArr){
  enableDebugMode();
  drawDebugStuff(player, enemyArr, tileArr, weaponBuyArr, perkBuyArr, chunkArr);
}
