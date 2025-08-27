#include "common.h"
#include "mapEditor.h"
#include "textureManager.h"
#include "user.h"
#include "tile.h"
#include "ui.h"
#include "export.h"

int main(){
  
  InitWindow(SCREENWIDTH, SCREENHEIGHT, "Map Editor");
  SetTargetFPS(TARGETFPS);

  //Objects
  //****************************************************************
    Camera2D camera = { 0 };
    initCamera(&camera);

    TextureManager textureManager;
    loadAllTextures(&textureManager);

    Tile tileArr[MAXTILES];
    Texture2D tileTextureArr[AMOUNTOFTILETEXTURES];
    initTileArr(tileArr);
    initTileTextureArr(tileTextureArr, &textureManager);
  
    User user;
    user = createUser(tileTextureArr);
  //****************************************************************
  
  //IMPORT THE MAP
  importMap(tileArr, tileTextureArr);

  while(!WindowShouldClose()){
    BeginDrawing();

      BeginMode2D(camera);

      ClearBackground(WHITE);

      updateMapEditor(&camera, tileArr, tileTextureArr, &user);

      EndMode2D();

    updateUI(tileTextureArr, &user, tileArr);
    
    EndDrawing();
  }
  
  CloseWindow();

  return 0;
}
