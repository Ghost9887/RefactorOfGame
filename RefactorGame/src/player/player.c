#include "player.h"
#include "weapon.h"
#include "enemy.h"

extern int AMOUNTOFTILES;

float getRotationOfPlayer(Player *player, Camera2D *camera);

Player createPlayer(TextureManager *textureManager){
  Player player;
  player.pos = (Vector2){ 0, 0 };
  player.width = 50.0f; // make it smaller for the hitbox so its more forgiving
  player.height = 50.0f;
  player.money = 0;
  player.rotation = 0.0f;
  player.speed = 150.0f;
  player.velocity = (Vector2){ 0, 0 };
  player.health = 100;
  player.maxHealth = 100;
  player.texture = &textureManager->playerTexture;
  player.weapon;
  player.ads = false;
  //animations
  player.amountOfFrames = 2;
  player.currentFrame = 0;
  player.frameTime = 0.0f;
  player.frameSpeed = 0.3f;
  player.frameRec = (Rectangle){ 0.0f, 0.0f, 64.0f, 64.0f };
  return player;
}

void updatePlayerAnimation(Player *player){
  player->frameTime += GetFrameTime();
  if (player->frameTime >= player->frameSpeed) {
      player->frameTime = 0.0f;
      player->currentFrame++;
      if (player->currentFrame > player->amountOfFrames) player->currentFrame = 0;
      player->frameRec.y = (float)player->currentFrame * player->frameRec.height;
  }
}

void playerMovement(Player *player){
    float deltaTime = GetFrameTime();

    if (IsKeyDown(KEY_A)){
      player->pos.x += player->velocity.x;
      player->velocity.x = -player->speed * deltaTime;
    }
    if (IsKeyDown(KEY_D)){ 
      player->pos.x += player->velocity.x;
      player->velocity.x = player->speed *deltaTime;
    }
    if (IsKeyDown(KEY_W)){ 
      player->pos.y += player->velocity.y;
      player->velocity.y = -player->speed * deltaTime;
    }
    if (IsKeyDown(KEY_S)){ 
      player->pos.y += player->velocity.y;
      player->velocity.y = player->speed * deltaTime;
    }
}

void drawPlayer(Player *player, Camera2D *camera){
  float rotation = getRotationOfPlayer(player, camera);
  Rectangle source = player->frameRec; 
  Rectangle dest = {
      player->pos.x + player->width / 2,
      player->pos.y + player->height / 2,
      player->frameRec.width,
      player->frameRec.height,
  };
  //pivot for the rotation (middle)
  Vector2 pivot = { player->frameRec.width / 2.0f, player->frameRec.height / 2.0f };
  player->rotation = rotation;
  DrawTexturePro(*player->texture, source, dest, pivot, rotation, WHITE);
}

//calculates where the player should be facing using the mouse pos
float getRotationOfPlayer(Player *player, Camera2D *camera){
  Vector2 mousePosition = GetScreenToWorld2D(GetMousePosition(), *camera);
  float rad = atan2(mousePosition.y - player->pos.y, mousePosition.x - player->pos.x);
  float degree = rad * (180.0f / 3.14);
  return degree;
}

void playerShoot(Player *player, Projectile *projectileArr){
  if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && checkIfWeaponCanShoot(player->weapon)){
    player->weapon->fireRateTimer = player->weapon->fireRate;
    player->weapon->magCapacity -= 1;
    float spread = (player->ads) ? 0 : GetRandomValue(-player->weapon->spread, player->weapon->spread);
    if(strcmp(player->weapon->type, "spread") == 0){
      spreadShot(projectileArr, player);
    }else{
      createProjectile(projectileArr, player, spread, player->weapon->type);
    }
  }
}

void playerADS(Player *player, Enemy *enemyArr, Chunk *chunkArr, int chunks){
  if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
    if (!player->ads) {
        player->speed -= 80;
        player->ads = true;
    }
    float rotation = player->rotation;
    float muzzleOffset = player->width * 0.4f; 
    Vector2 origin = {
      player->pos.x + player->width / 2 + cosf(rotation * DEG2RAD ) * muzzleOffset,
      player->pos.y + player->height / 2 + sinf(rotation * DEG2RAD) * muzzleOffset
    };
    float range = player->weapon->range;
    Vector2 direction = {
      cosf(rotation * DEG2RAD),
      sinf(rotation * DEG2RAD)
    };
    Vector2 hitPoint = {
      origin.x + direction.x * range,
      origin.y + direction.y * range
    };
    for (float t = 0; t < range; t++) {
      Vector2 point = {
        origin.x + direction.x * t,
        origin.y + direction.y * t
      };
      for (int j = 0; j < chunks; j++) {
        for (int k = 0; k < chunkArr[j].solidTileCount; k++) {
          Rectangle tileHitbox = {
            chunkArr[j].solidTileArr[k].pos.x,
            chunkArr[j].solidTileArr[k].pos.y,
            CELLSIZE,
            CELLSIZE
          };
          if (CheckCollisionPointRec(point, tileHitbox)) {
            hitPoint = point;
            t = range;
            DrawCircle(hitPoint.x, hitPoint.y, 3, RED);
            break;
          }
        }
      }
      for (int i = 0; i < MAXSPAWNENEMIES; i++) {
        if (enemyArr[i].active) {
          Rectangle enemyHitbox = {
            enemyArr[i].pos.x,
            enemyArr[i].pos.y,
            enemyArr[i].width,
            enemyArr[i].height
          };
          if (CheckCollisionPointRec(point, enemyHitbox)) {
            hitPoint = point;
            t = range;
            //little circle if the enemy is in the laser
            DrawCircle(hitPoint.x, hitPoint.y, 3, RED);
            break;
          }
        }
      }
    }
    DrawLineEx(origin, hitPoint, 1.0f, RED);
  }
  else {
    if(player->ads) {
      player->speed += 80;
      player->ads = false;
    }
  }
}

void checkPlayerCollisionWithTile(Player *player, Tile *tile){
    Rectangle tileRec = { tile->pos.x, tile->pos.y, CELLSIZE, CELLSIZE };
    Rectangle futurePlayerXRec = {
      player->pos.x + player->velocity.x,
      player->pos.y,
      player->width,
      player->height
    };
    if (CheckCollisionRecs(futurePlayerXRec, tileRec)) player->velocity.x = 0.0f;
    Rectangle futurePlayerYRec = {
      player->pos.x,
      player->pos.y + player->velocity.y,
      player->width,
      player->height
    };
    if (CheckCollisionRecs(futurePlayerYRec, tileRec)) player->velocity.y = 0.0f;
}

void updatePlayer(Player *player, Camera2D *camera, Projectile *projectileArr, Enemy *enemyArr, Tile *tileArr){
  drawPlayer(player, camera);
  updatePlayerAnimation(player);
  playerMovement(player);
  playerShoot(player, projectileArr);
}
