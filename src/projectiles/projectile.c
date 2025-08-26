#include "projectile.h"

void addProjectileToArr(Projectile *projectileArr, Projectile *projectile){
  for(int i = 0; i < MAXPROJECTILES; i++){
    if(!projectileArr[i].active){
      projectileArr[i] = *projectile;
      break;
    }
  }
}

void createProjectile(Projectile *projectileArr, Player *player, float offset){
    Projectile projectile;

    float angleDeg = player->weapon->rotation + offset;
    float angleRad = angleDeg * (3.14159265f / 180.0f);
    float muzzleDistance = player->width * 0.4f;

    projectile.pos = (Vector2) { player->pos.x + player->width / 2 + cosf(angleRad) * muzzleDistance, player->pos.y + player->height / 2 + sinf(angleRad) * muzzleDistance };
    projectile.previousPos;
    projectile.dir = (Vector2) { cosf(angleRad), sinf(angleRad) };
    projectile.length = 20.0f;
    projectile.damage = player->weapon->damage;
    projectile.speed = player->weapon->projectileSpeed;
    projectile.size = 5.0f;
    projectile.range = player->weapon->range;
    projectile.distanceTraveled = 0.0f + projectile.length;
    projectile.active = true;
    addProjectileToArr(projectileArr, &projectile);
}

void initProjectileArr(Projectile *projectileArr){
   for (int i = 0; i < MAXPROJECTILES; i++) {
    projectileArr[i].active = false;
    projectileArr[i].speed = 0.0f;
    projectileArr[i].damage = 0;
    projectileArr[i].range = 0.0f;
    projectileArr[i].distanceTraveled = 0.0f;
    projectileArr[i].pos = (Vector2){ 0, 0 };
  }
}

void moveProjectile(Projectile *projectile){
  float deltaTime = GetFrameTime();
  projectile->previousPos = projectile->pos;
  projectile->pos.x += projectile->dir.x * projectile->speed * deltaTime;
  projectile->pos.y += projectile->dir.y * projectile->speed * deltaTime;
  float dx = projectile->pos.x - projectile->previousPos.x;
  float dy = projectile->pos.y - projectile->previousPos.y;
  projectile->distanceTraveled += sqrtf(dx * dx + dy * dy);
}

void drawProjectile(Projectile *projectile){
    Vector2 end = {
        projectile->pos.x + projectile->dir.x * projectile->length,
        projectile->pos.y + projectile->dir.y * projectile->length
    };
    DrawLineEx(projectile->pos, end, 2.0f, BLUE);
}

void destroyProjectile(Projectile *projectile){
  projectile->active = false;
  projectile->speed = 0.0f;
}

void checkCollisionWithEnemy(Projectile *projectile, Enemy *enemyArr){
  for(int i = 0; i < MAXSPAWNENEMIES; i++){
    if(enemyArr[i].active){
      Rectangle enemyRect = { enemyArr[i].pos.x, enemyArr[i].pos.y, enemyArr[i].width, enemyArr[i].height };
      if(CheckCollisionPointRec(projectile->pos, enemyRect)){
        enemyArr[i].health -= projectile->damage;
        destroyProjectile(projectile);
        break;
      }
    }
  }
}

void updateProjectile(Projectile *projectileArr, Enemy *enemyArr){
  for(int i = 0; i < MAXPROJECTILES; i++){
    if(projectileArr[i].active){
      if(projectileArr[i].distanceTraveled >= projectileArr[i].range){
        destroyProjectile(&projectileArr[i]);
      }
      drawProjectile(&projectileArr[i]);
      moveProjectile(&projectileArr[i]);
      checkCollisionWithEnemy(&projectileArr[i], enemyArr);
    }
  }
}
