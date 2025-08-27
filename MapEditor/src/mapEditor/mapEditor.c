#include "mapEditor.h"

void drawGrid(){
  for(int y = 0; y < ROWCOUNT; y++){
    for(int x = 0; x < ROWCOUNT; x++){
      //prevents form overdrawing a line
      if(x + 1 != ROWCOUNT){
        DrawLine(x * CELLSIZE, y * CELLSIZE, x * CELLSIZE + CELLSIZE, y * CELLSIZE, BLACK);
      }else{
        DrawLine(x * CELLSIZE, y * CELLSIZE, x * CELLSIZE, y * CELLSIZE, BLACK);
      }
    }
  }

  for(int x = 0; x < COLUMNCOUNT; x++){
    for(int y = 0; y < COLUMNCOUNT; y++){
      //prevents overdrawing a line
      if(y + 1 != ROWCOUNT){
        DrawLine(x * CELLSIZE, y * CELLSIZE, x * CELLSIZE, y * CELLSIZE + CELLSIZE, BLACK);
      }else{
        DrawLine(x * CELLSIZE, y * CELLSIZE, x * CELLSIZE, y * CELLSIZE, BLACK);
      }
    }
  }
}

void placeTile(Tile *tileArr, Texture2D *tileTextureArr, Camera2D *camera, User *user){
  if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !IsKeyDown(KEY_LEFT_SHIFT)){
    Vector2 mousePos =  GetScreenToWorld2D(GetMousePosition(), *camera);
    //we use the mouse position to determine the tile position
    //bit of a genius
    for(int i = 0; i < MAXTILES; i++){
      if(!tileArr[i].active && mousePos.x >= 0 && mousePos.y >= 0 && mousePos.x <= ROWCOUNT * CELLSIZE - CELLSIZE && mousePos.y <= COLUMNCOUNT * CELLSIZE - CELLSIZE){
        tileArr[i].pos.x = (int)mousePos.x / CELLSIZE * CELLSIZE;
        tileArr[i].pos.y = (int)mousePos.y / CELLSIZE * CELLSIZE;
        tileArr[i].texture = user->selectedTexture;
        tileArr[i].active = true;
        break;
      }
    }
  }
}

void deleteTile(Tile *tileArr, Camera2D *camera){
  if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
    Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), *camera);
    int posX = (int)mousePos.x / CELLSIZE * CELLSIZE;
    int posY = (int)mousePos.y / CELLSIZE * CELLSIZE;
    for(int i = 0; i < MAXTILES; i++){
      if(tileArr[i].active && tileArr[i].pos.x == posX && tileArr[i].pos.y == posY){
        tileArr[i].pos.x = 0;
        tileArr[i].pos.y = 0;
        tileArr[i].active = false;
      }
    }
  }
}

void drawTile(Tile *tileArr){
  for(int i = 0; i < MAXTILES; i++){
    if(tileArr[i].active){
      DrawTexture(*tileArr[i].texture, tileArr[i].pos.x, tileArr[i].pos.y, WHITE);
    }
  }
}

void updateMapEditor(Camera2D *camera, Tile *tileArr, Texture2D *tileTextureArr, User *user){
  cameraMovement(camera);
  drawGrid();
  placeTile(tileArr, tileTextureArr, camera, user);
  deleteTile(tileArr, camera);
  drawTile(tileArr);
}



