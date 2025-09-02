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

//TODO: refactor
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
          tileArr[i].enemySpawn = false;
          tileArr[i].weaponBuy = false;
          tileArr[i].weaponIndex = -1;
          tileArr[i].perkBuy = false;
          tileArr[i].perkIndex = -1;
          printf("Tile Data: id:%d, x: %d, y: %d\n", tileArr[i].id, (int)tileArr[i].pos.x, (int)tileArr[i].pos.y);
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
    else if(user->mode == ENEMYSPAWN && mousePos.y >= 0 && mousePos.x <= ROWCOUNT * CELLSIZE - CELLSIZE && mousePos.y <= COLUMNCOUNT * CELLSIZE - CELLSIZE && !user->interactingWithUI){
      int indexOfTile = tileExists(posX, posY, tileArr);
      if(indexOfTile != -1){
        if(!tileArr[indexOfTile].solid){
          tileArr[indexOfTile].enemySpawn = true;
        }    
        else{
          //flash to warn that you cant place a enemy spawn there
          DrawRectangle(tileArr[indexOfTile].pos.x, tileArr[indexOfTile].pos.y, CELLSIZE, CELLSIZE, RED);
        }
      }
    }
    else if(user->mode == WEAPONBUY && mousePos.y >= 0 && mousePos.x <= ROWCOUNT * CELLSIZE - CELLSIZE && mousePos.y <= COLUMNCOUNT * CELLSIZE - CELLSIZE && !user->interactingWithUI){
      int indexOfTile = tileExists(posX, posY, tileArr);
      if(indexOfTile != -1){
        if(!tileArr[indexOfTile].solid && !tileArr[indexOfTile].playerSpawn && !tileArr[indexOfTile].perkBuy){
          tileArr[indexOfTile].weaponBuy = true;
          tileArr[indexOfTile].weaponIndex = user->textureId;
        }
      }
      printf("Tile Data: id:%d, weaponBuy: %d, weaponIndex: %d\n", tileArr[indexOfTile].id, tileArr[indexOfTile].weaponBuy, tileArr[indexOfTile].weaponIndex);
    }
    else if(user->mode == PERKBUY  && mousePos.y >= 0 && mousePos.x <= ROWCOUNT * CELLSIZE - CELLSIZE && mousePos.y <= COLUMNCOUNT * CELLSIZE - CELLSIZE && !user->interactingWithUI){
      int indexOfTile = tileExists(posX, posY, tileArr);
      if(indexOfTile != -1){
        if(!tileArr[indexOfTile].solid && !tileArr[indexOfTile].playerSpawn && !tileArr[indexOfTile].weaponBuy){
          tileArr[indexOfTile].perkBuy = true;
          tileArr[indexOfTile].perkIndex = user->textureId;
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

void drawTile(Tile *tileArr, Texture2D *tileTextureArr, Texture2D *weaponTextureArr, Texture2D *perkTextureArr){
  for(int i = 0; i < MAXTILES; i++){
    if(tileArr[i].active){
      DrawTexture(tileTextureArr[tileArr[i].id], tileArr[i].pos.x, tileArr[i].pos.y, WHITE);
      if(tileArr[i].solid){
        //outline solid tiles
        DrawRectangleLines(tileArr[i].pos.x, tileArr[i].pos.y, CELLSIZE, CELLSIZE, RED);
      }
      if(tileArr[i].playerSpawn){
        DrawTexture(tileTextureArr[15], tileArr[i].pos.x, tileArr[i].pos.y, WHITE);
      }
      if(tileArr[i].enemySpawn){
        Rectangle rec = { 0, 0, 32, 32 };
        DrawTextureRec(tileTextureArr[16], rec, tileArr[i].pos, WHITE);
      }
      if(tileArr[i].weaponBuy){
        //have animations so the texture sometimes put all of them
        Rectangle rec = { 0, 0, 32, 32 };
        DrawTextureRec(weaponTextureArr[tileArr[i].weaponIndex], rec, tileArr[i].pos, WHITE);
      }
      if(tileArr[i].perkBuy){
        Rectangle rec = { 0, 0, 32, 32 };
        DrawTextureRec(perkTextureArr[tileArr[i].perkIndex], rec, tileArr[i].pos, WHITE);
      }
      DrawText(TextFormat("%d", tileArr[i].id), tileArr[i].pos.x + CELLSIZE / 2, tileArr[i].pos.y + CELLSIZE / 2, 5, BLUE);
    }
  }
}

void updateMapEditor(Camera2D *camera, Tile *tileArr, Texture2D *tileTextureArr,Texture2D *weaponTextureArr, Texture2D *perkTextureArr, User *user){
  cameraMovement(camera);
  drawGrid();
  placeTile(tileArr, tileTextureArr, camera, user);
  deleteTile(tileArr, camera);
  drawTile(tileArr, tileTextureArr, weaponTextureArr, perkTextureArr);
  switchMode(user);
}



