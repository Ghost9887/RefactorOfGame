#include "camera.h"

void initCamera(Camera2D *camera){
  camera->rotation = 0.0f;
  camera->target = (Vector2){ 0, 0 };
  //puts the camera to the middle of the screen
  camera->offset = (Vector2){ SCREENWIDTH / 2 , SCREENHEIGHT / 2 };
  camera->zoom = 1.0f;
}

//makes the camera follow the player
void updateCamera(Camera2D *camera, Player *player){ 
  camera->target = (Vector2){ player->pos.x + player->width / 2, player->pos.y + player->height / 2 }; 
}
