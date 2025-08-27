#include "ui.h"


void selectTexture(User *user, Rectangle *textureRec, int id, Texture2D *tileTextureArr){
  Vector2 pos = GetMousePosition();
  int posX = (int)pos.x / CELLSIZE * CELLSIZE;
  int posY = (int)pos.y / CELLSIZE * CELLSIZE;
  Rectangle userClick = { posX, posY, CELLSIZE , CELLSIZE };
  if(CheckCollisionRecs(userClick, *textureRec)){
    user->selectedTexture = &tileTextureArr[id];
    user->textureId = id;
  }
}

void drawUserMode(User *user){
  if(user->mode == PAINT){
    DrawText("Paint", SCREENWIDTH - 150, 30, 40, BLUE);
  }
  else if(user->mode == SOLID){
    DrawText("Solid", SCREENWIDTH - 150, 30, 40, BLUE);
  }
}

void drawExportButton(Tile *tileArr){
  Rectangle rec = { 10, 10, 80, 40 };
  DrawRectangleRec(rec, BLACK);
  DrawText("Export", rec.x + 5, rec.y + 7, 20, BLUE);

  //check input
  if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
    Vector2 mousePos = GetMousePosition();
    Rectangle mouseClick = { mousePos.x, mousePos.y, 30, 30 };
    if(CheckCollisionRecs(rec, mouseClick)){
      exportMap(tileArr);
    }
  }
}

void drawTexturesToSelect(Texture2D *tileTextureArr, User *user){
  int height = 200;
  DrawRectangle(0, SCREENHEIGHT - height, SCREENWIDTH, SCREENHEIGHT, BLACK);
  Vector2 mousePos = GetMousePosition();
  
  int offset = SCREENHEIGHT - height;

  for(int i = 0; i < AMOUNTOFTILETEXTURES; i++){
    Rectangle source = { 0, 0, CELLSIZE, CELLSIZE };
    Vector2 pos = { i * CELLSIZE, offset };
    DrawTextureRec(tileTextureArr[i], source, pos, WHITE);
    Rectangle textureRec = { pos.x, pos.y, CELLSIZE, CELLSIZE };
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
      selectTexture(user, &textureRec, i, tileTextureArr);
    }
  }
  /* FIX THIS LATER WE DONT HAVE THAT MANY TILES YET
  int maxTexturesRow = 37;
  int maxTexturesColumn = 7;

  for(int y = 0; y < maxTexturesColumn; y++){
    for(int x = 0; x < maxTexturesRow; x++){
      for(int i = 0; i < AMOUNTOFTILETEXTURES; i++){
        Rectangle source = { 0, 0, CELLSIZE, CELLSIZE };
        Vector2 pos = { x * CELLSIZE, y * CELLSIZE + offset };
        DrawTextureRec(tileTextureArr[x], source, pos, WHITE);
      }
    }
  }
  */
}

//fixes the bug where when selecting a texture it would instantly paint it under the rectangle 
void userInteractingWithUI(User *user){
  Vector2 mousePos = GetMousePosition();
  //bottom bar location
  if(mousePos.y >= 600){
    user->interactingWithUI = true;
    }
  //save button location fine for now just looks ugly
  else if(mousePos.y >= 10 && mousePos.y <= 40 && mousePos.x >= 10 && mousePos.x <= 80){
    user->interactingWithUI = true;
  }
  else{
    user->interactingWithUI = false;
  }
}

void updateUI(Texture2D *tileTextureArr, User *user, Tile *tileArr){
  drawTexturesToSelect(tileTextureArr, user);
  drawUserMode(user);
  userInteractingWithUI(user);
  drawExportButton(tileArr);
}
