#ifndef PLAYER_H
#define PLAYER_H

#include "common.h"
#include "projectile.h"

  Player createPlayer(TextureManager *textureManager); 
  void updatePlayer(Player *player, Camera2D *camera, Projectile *projectileArr, Enemy *enemyArr, Tile *tileArr);
  void checkPlayerCollisionWithTile(Player *player, Tile *tile);
  
#endif
