#include "roundManager.h"

extern int ENEMYCOUNT;
extern int ALIVEENEMIES;

RoundManager createRoundManager(){
  RoundManager roundManager;
  roundManager.roundNumber = 1;
  roundManager.enemyCount = 6;
  roundManager.breakTime = 2.0f;
  roundManager.breakTimer = 0.0f;
  roundManager.inBreak = false;
  roundManager.allEnemiesSpawned = false;
  return roundManager;
}

void startRound(RoundManager *roundManager){
    roundManager->roundNumber++;
    roundManager->enemyCount += 6;
    roundManager->inBreak = false;
    roundManager->allEnemiesSpawned = false;
}

void checkIfAllEnemiesHaveSpawned(RoundManager *roundManager){
  if(roundManager->enemyCount == ENEMYCOUNT){
    roundManager->allEnemiesSpawned = true;
  }
}

//only check if all enemies have spawned otherwise theres no need
void checkIfRoundShouldEnd(RoundManager *roundManager){
  if(roundManager->allEnemiesSpawned){
    if(ALIVEENEMIES == 0 && !roundManager->inBreak){
      roundManager->inBreak = true;
      roundManager->breakTimer = roundManager->breakTime;
      ENEMYCOUNT = 0;
    }
  }
}

//checks if we should count down the time in break
void roundTimer(RoundManager *roundManager){
  if(roundManager->inBreak && roundManager->breakTimer >= 0.01f){
    roundManager->breakTimer -= GetFrameTime();
  }
  else if(roundManager->inBreak && roundManager->breakTimer <= 0.1f){
    roundManager->breakTimer = 0.0f;
    startRound(roundManager);
  }
}

void updateRoundManager(RoundManager *roundManager){
  checkIfRoundShouldEnd(roundManager);
  roundTimer(roundManager);
  checkIfAllEnemiesHaveSpawned(roundManager);
}
