#include "ui.h"

void drawUI(Player *player){
  //Draw FPS
  DrawText(TextFormat("%d", GetFPS()), SCREENWIDTH - 40, 30, 20, BLUE);

  //Draw Player Health
  DrawText(TextFormat("%d", player->health), 30, 30, 40, RED);

  //Draw Ammo
  DrawText(TextFormat("%d / %d", player->weapon->magCapacity, player->weapon->reserveCapacity), 30, SCREENHEIGHT - 50, 30, BLACK);
}
