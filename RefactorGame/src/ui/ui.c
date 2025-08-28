#include "ui.h"

extern int ENEMYCOUNT;
extern int ALIVEENEMIES;
extern bool DEBUGMODE;
extern bool ENABLEPLAYERHITBOX;
extern bool ENABLEENEMYHITBOX;
extern bool ENABLESOLIDTILEHITBOX;

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
    DrawText(TextFormat("%d", (int)roundManager->breakTimer), SCREENWIDTH - 50, 125, 40, RED);
  }


  //DEBUGGING
  DrawText(TextFormat("Enemy count: %d", ENEMYCOUNT), 30, 80, 40, BLACK);
  DrawText(TextFormat("Alive enemies: %d", ALIVEENEMIES), 30, 130, 40, BLACK);
  DrawText(TextFormat("%d", roundManager->inBreak), 30, 180, 40, BLACK);
}

//copilot was here
void drawUIForDebugMode() {
  if(DEBUGMODE){
    DrawRectangle(SCREENWIDTH - 200, 0, SCREENWIDTH, SCREENHEIGHT, BLUE);
    DrawText("Debug Panel", SCREENWIDTH - 180, 30, 25, BLACK);

    int buttonWidth = 20;
    int buttonHeight = 20;
    int spacing = 20;
    int startX = SCREENWIDTH - buttonWidth - 5;
    int labelX = startX - 170;
    int startY = 100;

    Rectangle playerButtonRec = { startX, startY, buttonWidth, buttonHeight };
    Rectangle enemyButtonRec = { startX, startY + (buttonHeight + spacing), buttonWidth, buttonHeight };
    Rectangle tileButtonRec   = { startX, startY + 2 * (buttonHeight + spacing), buttonWidth, buttonHeight };

    DrawText("Player Hitbox:", labelX, playerButtonRec.y, 20, BLACK);
    DrawText("Enemy Hitbox:", labelX, enemyButtonRec.y, 20, BLACK);
    DrawText("Solid Tile Hitbox:", labelX, tileButtonRec.y, 20, BLACK);

    DrawRectangleRec(playerButtonRec, ENABLEPLAYERHITBOX ? GREEN : WHITE);
    DrawRectangleRec(enemyButtonRec, ENABLEENEMYHITBOX ? GREEN : WHITE);
    DrawRectangleRec(tileButtonRec, ENABLESOLIDTILEHITBOX ? GREEN : WHITE);

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetMousePosition();
        Rectangle mouseClick = { mousePos.x, mousePos.y, 1, 1 };

        if (CheckCollisionRecs(playerButtonRec, mouseClick)) {
            ENABLEPLAYERHITBOX = !ENABLEPLAYERHITBOX;
        } else if (CheckCollisionRecs(enemyButtonRec, mouseClick)) {
            ENABLEENEMYHITBOX = !ENABLEENEMYHITBOX;
        } else if (CheckCollisionRecs(tileButtonRec, mouseClick)) {
            ENABLESOLIDTILEHITBOX = !ENABLESOLIDTILEHITBOX;
        }
    }
  }
}


