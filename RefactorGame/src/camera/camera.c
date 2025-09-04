#include "camera.h"

extern bool DEBUGMODE;

void initCamera(Camera2D *camera){
  camera->rotation = 0.0f;
  camera->target = (Vector2){ 0, 0 };
  //puts the camera to the middle of the screen
  camera->offset = (Vector2){ SCREENWIDTH / 2 , SCREENHEIGHT / 2 };
  camera->zoom = 2.0f;
}

//makes the camera follow the player
void followPlayer(Camera2D *camera, Player *player){ 
  if(!DEBUGMODE){
    camera->offset = (Vector2){ SCREENWIDTH / 2, SCREENHEIGHT / 2 };
    camera->zoom = 2.0f;
    camera->target = (Vector2){ player->pos.x + player->width / 2, player->pos.y + player->height / 2 }; 
  }
}

void cameraMovementInDebugMode(Camera2D *camera){
  if(DEBUGMODE){
    float wheel = GetMouseWheelMove();
    if (wheel != 0){
      Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), *camera);
      camera->offset = GetMousePosition();
      camera->target = mouseWorldPos;
      float scale = 0.2f*wheel;
      camera->zoom = Clamp(expf(logf(camera->zoom)+scale), 0.125f, 64.0f);
    }
    //dragging
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && IsKeyDown(KEY_LEFT_SHIFT)){
      Vector2 delta = GetMouseDelta();
      delta = Vector2Scale(delta, -1.0f/camera->zoom);
      camera->target = Vector2Add(camera->target, delta);
    }
  }
}

void updateCamera(Camera2D *camera, Player *player){
  cameraMovementInDebugMode(camera);
  followPlayer(camera, player);
}
