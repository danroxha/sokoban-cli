#ifndef __SETTING_SOKOBAN_H__
#define __SETTING_SOKOBAN_H__

#include <stdlib.h>
#include "types.h"


void configCharacter(Object*, GameState*);
void configBoxes(Boxes*, GameState*);
void configGoals(Goals*, GameState*);
void configGameState(GameState*);



void configCharacter(Object *character, GameState *gameState) {
  
  character->body = DOLL;

  for (int y = 0; y < gameState->currrentMap.height; y++) 
    for (int x = 0; x < gameState->currrentMap.width; x++) {
      if (gameState->currrentMap.field[y][x] == DOLL) {
        character->x = x + 1;
        character->y = y + 1;
        gameState->currrentMap.field[y][x] = ' ';
        break;
      }
    }
}

void configBoxes(Boxes *boxes, GameState *gameState) {
  
  boxes->list   = NULL;
  boxes->lenght = 0;

 for (int y = 0; y < gameState->currrentMap.height; y++) 
    for (int x = 0; x < gameState->currrentMap.width; x++) {
      if(gameState->currrentMap.field[y][x] == BOX) {
        boxes->lenght++;
      }
    }

  boxes->list = (Box*) calloc(boxes->lenght, sizeof(Box));

  for(int i = 0; i < boxes->lenght; i++) {
    boxes->list[i].body = BOX;
    boxes->list[i].enable = false;
    boxes->list[i].id = rand();
  }

  int index = 0;

  for (int y = 0; y < gameState->currrentMap.height; y++) 
    for (int x = 0; x < gameState->currrentMap.width; x++) {
      if(gameState->currrentMap.field[y][x] == BOX) {
        boxes->list[index].x = x + 1;
        boxes->list[index].y = y + 1;
        gameState->currrentMap.field[y][x] = ' ';
        index++;
      }
    }
}

void configGoals(Goals *goals, GameState *gameState) {
  
  goals->lenght = 0;
  if(goals->list)
    free(goals->list);

  for(int y = 0; y < gameState->currrentMap.height; y++) {
    for(int x = 0; x < gameState->currrentMap.width; x++) {
      if(gameState->currrentMap.field[y][x] == TARGET) {
        goals->lenght++;
        goals->list = (Object*) realloc(goals->list, goals->lenght * sizeof(Object));
        goals->list[goals->lenght - 1].body = TARGET;
        goals->list[goals->lenght - 1].x = x + 1;
        goals->list[goals->lenght - 1].y = y + 1;
      }
    }
  }
}

void configGameState(GameState *gameState) {
  gameState->gameOver = false;
}
#endif // __SETTING_SOKOBAN_H__