#include "mapEditor.h"

void drawGrid(){
  for(int y = 0; y < ROWCOUNT; y++){
    for(int x = 0; x < ROWCOUNT; x++){
      DrawLine(x * CELLSIZE, y * CELLSIZE, x * CELLSIZE + CELLSIZE, y * CELLSIZE,WHITE);
    }
  }

  for(int x = 0; x < COLUMNCOUNT; x++){
    for(int y = 0; y < COLUMNCOUNT; y++){
      DrawLine(x * CELLSIZE, y * CELLSIZE, x * CELLSIZE, y * CELLSIZE + CELLSIZE, WHITE);
    }
  }
}

void placeTile(Tile *tileArr, Texture2D *tileTextureArr, Camera2D *camera){
  if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !IsKeyDown(KEY_LEFT_SHIFT)){
    Vector2 mousePos =  GetScreenToWorld2D(GetMousePosition(), *camera);
    //we use the mouse position to determine the tile position
    //bit of a genius
    for(int i = 0; i < MAXTILES; i++){
      if(!tileArr[i].active){
        tileArr[i].pos.x = (int)mousePos.x / CELLSIZE * CELLSIZE;
        tileArr[i].pos.y = (int)mousePos.y / CELLSIZE * CELLSIZE;
        tileArr[i].texture = &tileTextureArr[0];
        tileArr[i].active = true;
        break;
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

void updateMapEditor(Camera2D *camera, Tile *tileArr, Texture2D *tileTextureArr){
  cameraMovement(camera);
  drawGrid();
  placeTile(tileArr, tileTextureArr, camera);
  drawTile(tileArr);
}



