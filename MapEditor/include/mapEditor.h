#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include "common.h"
#include "camera.h"
#include "user.h"
#include "queue.h"
#include "tile.h"

  void updateMapEditor(Camera2D *camera, Tile *tileArr, Texture2D *tileTextureArr, Texture2D *weaponTextureArr, Texture2D *perkTextureArr, User *user);
  void clearMap(Tile *tileArr);

#endif
