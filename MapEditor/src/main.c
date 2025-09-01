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
    Texture2D weaponTextureArr[AMOUNTOFWEAPONS];
    Texture2D perkTextureArr[AMOUNTOFPERKS];
    initTileArr(tileArr);
    initTileTextureArr(tileTextureArr, &textureManager);
    initWeaponTextureArr(weaponTextureArr, &textureManager);
    initPerkTextureArr(perkTextureArr, &textureManager);
  
    User user;
    user = createUser(tileTextureArr);
  //****************************************************************
  
  //IMPORT THE MAP
  importMap(tileArr);

  //Toggle Full Screen
  ToggleFullscreen();

  while(!WindowShouldClose()){

    BeginDrawing();

      BeginMode2D(camera);

      ClearBackground(WHITE);

      updateMapEditor(&camera, tileArr, tileTextureArr, weaponTextureArr, perkTextureArr, &user);

      EndMode2D();

    updateUI(tileTextureArr, &user, tileArr);
   
    EndDrawing();
  }
  
  CloseWindow();

  return 0;
}
