#include "mapEditor.h"

Tile createTile(float x, float y){
  Tile tile;
  tile.pos = (Vector2){ x, y };
  tile.active = true;
  tile.solid = false;
  tile.playerSpawn = false;
  tile.enemySpawn = false;
  tile.weaponBuy = false;
  tile.weaponIndex = -1;
  tile.perkBuy = false;
  tile.perkIndex = -1;
  return tile;
}

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

int *findNeigbouringTiles(Tile *tileArr, Tile *originalTile) {
  int *tiles = malloc(sizeof(int) * 4);
  int dx[4] = { 0, CELLSIZE, 0, -CELLSIZE };
  int dy[4] = { -CELLSIZE, 0, CELLSIZE, 0 };
  for(int i = 0; i < 4; i++){
    int x = originalTile->pos.x + dx[i];
    int y = originalTile->pos.y + dy[i];
    int index = tileExists(x, y, tileArr);
    if (index == -1) {
      for (int j = 0; j < MAXTILES; j++) {
        if (!tileArr[j].active) {
          tileArr[j] = createTile(x, y);
          tiles[i] = j;
          break;
        }
      }
    } 
    else{
      tiles[i] = -1;
    }
  }
  return tiles;
}

int *findNeigbouringTilesWithTheSameTexture(Tile *tileArr, Tile *originalTile){
  int *tiles = malloc(sizeof(int) * 4);
  int dx[4] = { 0, CELLSIZE, 0, -CELLSIZE };
  int dy[4] = { -CELLSIZE, 0, CELLSIZE, 0 };
  for(int i = 0; i < 4; i++){
    int x = originalTile->pos.x + dx[i];
    int y = originalTile->pos.y + dy[i];
    int index = tileExists(x, y, tileArr);
    if(index > -1 && tileArr[index].textureId == originalTile->textureId){
      tiles[i] = index;
    }
    else{
      tiles[i] = -1;
    }
  }
  return tiles;
}


void bucketTool(Tile *tileArr, Camera2D *camera, User *user){
  if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !IsKeyDown(KEY_LEFT_SHIFT) && !user->interactingWithUI){
    if(user->mode == BUCKET){
      Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), *camera);
      int posX = ((int)mousePos.x / CELLSIZE) * CELLSIZE;
      int posY = ((int)mousePos.y / CELLSIZE) * CELLSIZE;
      int indexOfTile = tileExists(posX, posY, tileArr);
      Queue q = createQueue();
      if(indexOfTile == -1){
        for(int i = 0; i < MAXTILES; i++){
          if(!tileArr[i].active){
            tileArr[i] = createTile(posX, posY);
            enqueue(&q, &tileArr[i]);
            break;
          }
        }
        while(getSize(&q) > 0){
          printf("queue size: %d\n", getSize(&q));
          Tile *temp = dequeue(&q);
          temp->textureId = user->textureId;
          int *tiles = findNeigbouringTiles(tileArr, temp);
          for(int i = 0; i < 4; i++){
            if(tiles[i] != -1){
              enqueue(&q, &tileArr[tiles[i]]);
            }
          }
          free(tiles);
        }
      }
    }
  }
  //deletes all tiles with the same texture(inverse of the up function)
  else if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && !IsKeyDown(KEY_LEFT_SHIFT) && !user->interactingWithUI){
   if(user->mode == BUCKET){
      Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), *camera);
      int posX = ((int)mousePos.x / CELLSIZE) * CELLSIZE;
      int posY = ((int)mousePos.y / CELLSIZE) * CELLSIZE;
      int indexOfTile = tileExists(posX, posY, tileArr);
      Queue q = createQueue();
      if(indexOfTile != -1){
        enqueue(&q, &tileArr[indexOfTile]);
        while(getSize(&q) > 0){
          Tile *temp = dequeue(&q);
          int *tiles = findNeigbouringTilesWithTheSameTexture(tileArr, temp);
          for(int i = 0; i < 4; i++){
            if(tiles[i] != -1){
              enqueue(&q, &tileArr[tiles[i]]);
            }
          }
          temp->active = false;
          temp->textureId = -1;
          free(tiles);
        }
      }
    }
  }
}

//TODO: refactor
void placeTile(Tile *tileArr, Texture2D *tileTextureArr, Camera2D *camera, User *user){
  if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !IsKeyDown(KEY_LEFT_SHIFT)){
    Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), *camera);
    //we use the mouse position to determine the tile position
    //bit of a genius
    int posX = ((int)mousePos.x / CELLSIZE) * CELLSIZE;
    int posY = ((int)mousePos.y / CELLSIZE) * CELLSIZE;
    if(user->mode == PAINT || user->mode == SOLID){
    for(int i = 0; i < MAXTILES; i++){
        //getting a bit long maybe rethink my life
        if(!tileArr[i].active && mousePos.x >= 0 && mousePos.y >= 0 && mousePos.x <= ROWCOUNT * CELLSIZE - CELLSIZE && 
          mousePos.y <= COLUMNCOUNT * CELLSIZE - CELLSIZE && !user->interactingWithUI && tileExists(posX, posY, tileArr) == -1){
          tileArr[i] = createTile(posX, posY);
          tileArr[i].textureId = user->textureId;
          tileArr[i].solid = (user->mode == SOLID);
          tileArr[i].next = NULL;
          printf("Tile Data: id:%d, x: %d, y: %d\n", tileArr[i].id, (int)tileArr[i].pos.x, (int)tileArr[i].pos.y);
          break;      
        }
      }
    }
    else if(user->mode == PLAYERSPAWN && mousePos.y >= 0 && mousePos.x <= ROWCOUNT * CELLSIZE - CELLSIZE && 
      mousePos.y <= COLUMNCOUNT * CELLSIZE - CELLSIZE && !user->interactingWithUI){
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
    else if(user->mode == ENEMYSPAWN && mousePos.y >= 0 && mousePos.x <= ROWCOUNT * CELLSIZE - CELLSIZE && 
      mousePos.y <= COLUMNCOUNT * CELLSIZE - CELLSIZE && !user->interactingWithUI){
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
    else if(user->mode == WEAPONBUY && mousePos.y >= 0 && mousePos.x <= ROWCOUNT * CELLSIZE - CELLSIZE && 
      mousePos.y <= COLUMNCOUNT * CELLSIZE - CELLSIZE && !user->interactingWithUI){
      int indexOfTile = tileExists(posX, posY, tileArr);
      if(indexOfTile != -1){
        if(!tileArr[indexOfTile].solid && !tileArr[indexOfTile].playerSpawn && !tileArr[indexOfTile].perkBuy){
          tileArr[indexOfTile].weaponBuy = true;
          tileArr[indexOfTile].weaponIndex = user->textureId;
        }
      }
    }
    else if(user->mode == PERKBUY  && mousePos.y >= 0 && mousePos.x <= ROWCOUNT * CELLSIZE - CELLSIZE && 
      mousePos.y <= COLUMNCOUNT * CELLSIZE - CELLSIZE && !user->interactingWithUI){
      int indexOfTile = tileExists(posX, posY, tileArr);
      if(indexOfTile != -1){
        if(!tileArr[indexOfTile].solid && !tileArr[indexOfTile].playerSpawn && !tileArr[indexOfTile].weaponBuy){
          tileArr[indexOfTile].perkBuy = true;
          tileArr[indexOfTile].perkIndex = user->textureId;
        }else{
          DrawRectangle(tileArr[indexOfTile].pos.x, tileArr[indexOfTile].pos.y, CELLSIZE, CELLSIZE, RED);
        }
      }
    }
  }
}

void deleteTile(Tile *tileArr, Camera2D *camera, User *user){
  if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && user->mode != BUCKET){
    Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), *camera);
    int posX = ((int)mousePos.x / CELLSIZE) * CELLSIZE;
    int posY = ((int)mousePos.y / CELLSIZE) * CELLSIZE;
    int index = tileExists(posX, posY, tileArr);
    if(index != -1){
      tileArr[index].pos.x = 0;
      tileArr[index].pos.y = 0;
      tileArr[index].active = false;
      tileArr[index].textureId = -1;
   }
  }
}

void drawTile(Tile *tileArr, Texture2D *tileTextureArr, Texture2D *weaponTextureArr, Texture2D *perkTextureArr){
  for(int i = 0; i < MAXTILES; i++){
    if(tileArr[i].active){
      DrawTexture(tileTextureArr[tileArr[i].textureId], tileArr[i].pos.x, tileArr[i].pos.y, WHITE);
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
      DrawText(TextFormat("%d", tileArr[i].textureId), tileArr[i].pos.x + CELLSIZE / 2, tileArr[i].pos.y + CELLSIZE / 2, 5, BLUE);
    }
  }
}

void clearMap(Tile *tileArr){
  initTileArr(tileArr);
}

void updateMapEditor(Camera2D *camera, Tile *tileArr, Texture2D *tileTextureArr,Texture2D *weaponTextureArr, Texture2D *perkTextureArr, User *user){
  cameraMovement(camera);
  drawGrid();
  placeTile(tileArr, tileTextureArr, camera, user);
  bucketTool(tileArr, camera, user);
  deleteTile(tileArr, camera, user);
  drawTile(tileArr, tileTextureArr, weaponTextureArr, perkTextureArr);
  switchMode(user);
}



