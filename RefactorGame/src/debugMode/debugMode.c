#include "debugMode.h"

extern bool DEBUGMODE;
extern bool ENABLEPLAYERHITBOX;
extern bool ENABLEENEMYHITBOX;
extern bool ENABLESOLIDTILEHITBOX;
extern int AMOUNTOFTILES;

void enableDebugMode(){
  if(IsKeyPressed(KEY_I)){
    DEBUGMODE = !DEBUGMODE; 
  }
}

void drawDebugStuff(Player *player, Enemy *enemyArr, Tile *tileArr){
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
    for(int i = 0; i < AMOUNTOFTILES; i++){
      if(tileArr[i].active && tileArr[i].solid){
        DrawRectangleLines(tileArr[i].pos.x, tileArr[i].pos.y, CELLSIZE, CELLSIZE, RED);
      }
    }
  }
}

void updateDebugMode(Player *player, Enemy *enemyArr, Tile *tileArr){
  enableDebugMode();
  drawDebugStuff(player, enemyArr, tileArr);
}
