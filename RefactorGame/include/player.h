#ifndef PLAYER_H
#define PLAYER_H

#include "common.h"
#include "projectile.h"
#include "shotgun.h"

  Player createPlayer(TextureManager *textureManager); 
  void updatePlayer(Player *player, Camera2D *camera, Projectile *projectileArr, Enemy *enemyArr, Tile *tileArr);
  void checkPlayerCollisionWithTile(Player *player, Tile *tile);
  void playerADS(Player *player, Enemy *enemyArr, Chunk *chunkArr, int chunks);
  
#endif
