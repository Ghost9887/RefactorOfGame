#include "ui.h"

extern int ENEMYCOUNT;
extern int ALIVEENEMIES;

void drawUI(Player *player, RoundManager *roundManager){
  //Draw FPS
  DrawText(TextFormat("%d", GetFPS()), SCREENWIDTH - 40, 30, 20, BLUE);

  //Draw Player Health
  DrawText(TextFormat("%d", player->health), 30, 30, 40, RED);

  //Draw Ammo
  DrawText(TextFormat("%d / %d", player->weapon->magCapacity, player->weapon->reserveCapacity), 30, SCREENHEIGHT - 50, 30, BLACK);

  //Draw Round Info
  DrawText(TextFormat("%d", roundManager->roundNumber), SCREENWIDTH - 50, 75, 40, RED);
  if(roundManager->inBreak){
    DrawText(TextFormat("%f", roundManager->breakTimer), SCREENWIDTH - 50, 125, 40, RED);
  }


  //DEBUGGING
  DrawText(TextFormat("Enemy count: %d", ENEMYCOUNT), 30, 80, 40, BLACK);
  DrawText(TextFormat("Alive enemies: %d", ALIVEENEMIES), 30, 130, 40, BLACK);
  DrawText(TextFormat("%d", roundManager->inBreak), 30, 180, 40, BLACK);

}
