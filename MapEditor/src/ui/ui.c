#include "ui.h"


void selectTexture(User *user, Rectangle *textureRec, int id, Texture2D *tileTextureArr){
  Vector2 pos = GetMousePosition();
  int posX = (int)pos.x / CELLSIZE * CELLSIZE;
  int posY = (int)pos.y / CELLSIZE * CELLSIZE;
  Rectangle userClick = { posX, posY, CELLSIZE , CELLSIZE };
  if(CheckCollisionRecs(userClick, *textureRec)){
    user->selectedTexture = &tileTextureArr[id];
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
  if(mousePos.y >= 600){
    user->interactingWithUI = true;
  }else{
    user->interactingWithUI = false;
  }
}

void updateUI(Texture2D *tileTextureArr, User *user){
  drawTexturesToSelect(tileTextureArr, user);
  drawUserMode(user);
  userInteractingWithUI(user);
}
