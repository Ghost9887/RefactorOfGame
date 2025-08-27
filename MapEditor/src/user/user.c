#include "user.h"


User createUser(Texture2D *tileTextureArr){
  User user;
  user.selectedTexture = &tileTextureArr[0];
  return user;
}
