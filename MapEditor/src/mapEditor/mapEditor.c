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

int tileExists(int x, int y, Tile *tileArr){
  for(int i = 0; i < MAXTILES; i++){
    if(tileArr[i].active && tileArr[i].pos.x == x && tileArr[i].pos.y == y){
      return i;
    }
  }
  return -1;
}

void placeTile(Tile *tileArr, Texture2D *tileTextureArr, Camera2D *camera, User *user){
  if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !IsKeyDown(KEY_LEFT_SHIFT)){
    Vector2 mousePos =  GetScreenToWorld2D(GetMousePosition(), *camera);
    //we use the mouse position to determine the tile position
    //bit of a genius
    int posX = ((int)mousePos.x / CELLSIZE) * CELLSIZE;
    int posY = ((int)mousePos.y / CELLSIZE) * CELLSIZE;
    if(user->mode == PAINT || user->mode == SOLID){
    for(int i = 0; i < MAXTILES; i++){
        //getting a bit long maybe rethink my life
        if(!tileArr[i].active && mousePos.x >= 0 && mousePos.y >= 0 && mousePos.x <= ROWCOUNT * CELLSIZE - CELLSIZE && 
          mousePos.y <= COLUMNCOUNT * CELLSIZE - CELLSIZE && !user->interactingWithUI && tileExists(posX, posY, tileArr) == -1){
          tileArr[i].id = user->textureId;
          tileArr[i].pos.x = posX; 
          tileArr[i].pos.y = posY;
          tileArr[i].active = true;
          tileArr[i].solid = (user->mode == SOLID);
          tileArr[i].playerSpawn = false;
        break;      
        }
      }
    }
    else if(user->mode == PLAYERSPAWN && mousePos.y >= 0 && mousePos.x <= ROWCOUNT * CELLSIZE - CELLSIZE && mousePos.y <= COLUMNCOUNT * CELLSIZE - CELLSIZE && !user->interactingWithUI){
      int indexOfTile = tileExists(posX, posY, tileArr);
      printf("%d", indexOfTile);
      if(indexOfTile != -1){
        if(!tileArr[indexOfTile].solid){
          tileArr[indexOfTile].playerSpawn = true;
        }
        else{
          //flash to warn that you cant place a palyer spawn there
          DrawRectangle(tileArr[indexOfTile].pos.x, tileArr[indexOfTile].pos.y, CELLSIZE, CELLSIZE, RED);
        }
      }
    }
  }
}

void deleteTile(Tile *tileArr, Camera2D *camera){
  if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
    Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), *camera);
    int posX = ((int)mousePos.x / CELLSIZE) * CELLSIZE;
    int posY = ((int)mousePos.y / CELLSIZE) * CELLSIZE;
    int index = tileExists(posX, posY, tileArr);
    if(index != -1){
      tileArr[index].pos.x = 0;
      tileArr[index].pos.y = 0;
      tileArr[index].active = false;
    }
  }
}

void drawTile(Tile *tileArr, Texture2D *tileTextureArr){
  for(int i = 0; i < MAXTILES; i++){
    if(tileArr[i].active){
      DrawTexture(tileTextureArr[tileArr[i].id], tileArr[i].pos.x, tileArr[i].pos.y, WHITE);
      if(tileArr[i].solid){
        //outline solid tiles
        DrawRectangleLines(tileArr[i].pos.x, tileArr[i].pos.y, CELLSIZE, CELLSIZE, RED);
      }
      if(tileArr[i].playerSpawn){
        DrawTexture(tileTextureArr[4], tileArr[i].pos.x, tileArr[i].pos.y, WHITE);
      }
      DrawText(TextFormat("%d", tileArr[i].id), tileArr[i].pos.x + CELLSIZE / 2, tileArr[i].pos.y + CELLSIZE / 2, 5, BLUE);
    }
  }
}

void updateMapEditor(Camera2D *camera, Tile *tileArr, Texture2D *tileTextureArr, User *user){
  cameraMovement(camera);
  drawGrid();
  placeTile(tileArr, tileTextureArr, camera, user);
  deleteTile(tileArr, camera);
  drawTile(tileArr, tileTextureArr);
  switchMode(user);
}



