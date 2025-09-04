#include "perkBuy.h"

extern int AMOUNTOFPERKBUYS;

PerkBuy createEmptyPerkBuy(){
  PerkBuy perkBuy;
  perkBuy.id = -1;
  perkBuy.pos = (Vector2){ 0, 0 };
  perkBuy.width = 0;
  perkBuy.height = 0;
  perkBuy.scale = 0.0f;
  perkBuy.perk;
  perkBuy.amountOfFrames = 0;
  perkBuy.currentFrame = 0;
  perkBuy.frameTime = 0.0f;
  perkBuy.frameSpeed = 0.0f;
  perkBuy.frameRec = (Rectangle){ 0, 0, 0, 0 }; 
  return perkBuy;
}

void createPerkBuy(PerkBuy *perkBuyArr, Perk *perkArr, int id, float x, float y){
  PerkBuy perkBuy;
  perkBuy.id = id;
  perkBuy.pos = (Vector2){ x, y };
  perkBuy.width = 32.0f;
  perkBuy.height = 32.0f;
  perkBuy.scale = 3.0f;
  perkBuy.perk = findPerkById(id, perkArr);
  perkBuy.cost = perkBuy.perk->cost;
  perkBuy.amountOfFrames = 6;
  perkBuy.currentFrame = 0;
  perkBuy.frameTime = 0.0f;
  perkBuy.frameSpeed = 0.5f;
  perkBuy.frameRec = (Rectangle) { 0, 0, perkBuy.width, perkBuy.height };
  perkBuy.consumed = false;
  perkBuyArr[AMOUNTOFPERKBUYS] = perkBuy;
}

void initPerkBuyArr(PerkBuy *perkBuyArr){
  for(int i = 0; i < MAXPERKBUYS; i++){
    perkBuyArr[i] = createEmptyPerkBuy();
  }
}

void drawPerkBuy(PerkBuy *perkBuy){
  Rectangle source = perkBuy->frameRec;
  Rectangle destRec = { perkBuy->pos.x, perkBuy->pos.y, perkBuy->width * perkBuy->scale, perkBuy->height * perkBuy->scale };
  Vector2 origin = { 0, 0 };
  float rotation = 0.0f;
  DrawTexturePro(*perkBuy->perk->texture, source, destRec, origin, rotation, WHITE);
}

void updateAnimationPerkBuy(PerkBuy *perkBuy){
  perkBuy->frameTime += GetFrameTime();
  if (perkBuy->frameTime >= perkBuy->frameSpeed) {
    perkBuy->frameTime = 0.0f;
    perkBuy->currentFrame++;
    if (perkBuy->currentFrame > perkBuy->amountOfFrames) perkBuy->currentFrame = 0;
    perkBuy->frameRec.y = (float)perkBuy->currentFrame * perkBuy->frameRec.height;
  } 
}

void drawTextPerkBuyRec(PerkBuy *perkBuy, Color colour){
  DrawText(TextFormat("%s", perkBuy->perk->name), perkBuy->pos.x, perkBuy->pos.y - 50, 20, BLACK);
  DrawText(TextFormat("%d", perkBuy->cost), perkBuy->pos.x, perkBuy->pos.y - 30, 20, colour);
}


void consumePerk(PerkBuy *perkBuy, Player *player){
  if(perkBuy->consumed == false){
    Rectangle perkBuyRec = { perkBuy->pos.x, perkBuy->pos.y, perkBuy->width * perkBuy->scale, perkBuy->height *perkBuy->scale };
    Rectangle playerRec = { player->pos.x, player->pos.y, player->width, player->height };
    if(CheckCollisionRecs(perkBuyRec, playerRec)){
      if(player->money >= perkBuy->cost){
        drawTextPerkBuyRec(perkBuy, GREEN);
        if(IsKeyPressed(KEY_E)){
          perkBuy->consumed = true;
          if(strcmp(perkBuy->perk->name, "Health Perk") == 0){
            player->maxHealth = perkBuy->perk->data;
            player->health = player->maxHealth;
          }
          else if(strcmp(perkBuy->perk->name, "Speed Perk") == 0){
            player->speed = perkBuy->perk->data;
          }
          player->money -= perkBuy->cost;
        }
      }else{
        drawTextPerkBuyRec(perkBuy, RED);
      }
    }
  }
}

//runs only one for loop per frame
void updatePerkBuys(PerkBuy *perkBuyArr, Player *player){
  for(int i = 0; i < AMOUNTOFPERKBUYS; i++){
    drawPerkBuy(&perkBuyArr[i]);
    updateAnimationPerkBuy(&perkBuyArr[i]);
    consumePerk(&perkBuyArr[i], player);
  }
}
