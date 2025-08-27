#include "common.h"
#include "mapEditor.h"

int main(){
  
  InitWindow(SCREENWIDTH, SCREENHEIGHT, "Map Editor");
  SetTargetFPS(TARGETFPS);

  //Objects
  //****************************************************************
    Camera2D camera = { 0 };
    initCamera(&camera);
  //****************************************************************

  while(!WindowShouldClose()){
    BeginDrawing();
      BeginMode2D(camera);
      ClearBackground(WHITE);
      updateMapEditor(&camera);
      DrawText("Test", 300, 300, 50, BLACK);
      EndMode2D();
    EndDrawing();
  }
  
  CloseWindow();

  return 0;
}
