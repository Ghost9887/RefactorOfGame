#include "common.h"
#include "mapEditor.h"
#include "textureManager.h"
#include "user.h"
#include "tile.h"

int main(){
  
  InitWindow(SCREENWIDTH, SCREENHEIGHT, "Map Editor");
  SetTargetFPS(TARGETFPS);

  //Objects
  //****************************************************************
    Camera2D camera = { 0 };
    initCamera(&camera);

    TextureManager textureManager;
    loadAllTextures(&textureManager);
    
    User user;
    user = createUser();

    Tile tileArr[MAXTILES];
    Texture2D tileTextureArr[AMOUNTOFTILETEXTURES];
    initTileArr(tileArr);
    initTileTextureArr(tileTextureArr, &textureManager);
  //****************************************************************

  while(!WindowShouldClose()){
    BeginDrawing();

      BeginMode2D(camera);

      ClearBackground(BLACK);

      updateMapEditor(&camera, tileArr, tileTextureArr);

      DrawText("Test", 300, 300, 50, WHITE);
     
      EndMode2D();
    
    EndDrawing();
  }
  
  CloseWindow();

  return 0;
}
