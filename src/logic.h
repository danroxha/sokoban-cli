#ifndef __LOGIC_SOKOBAN_H__
#define __LOGIC_SOKOBAN_H__

#include <stdbool.h>
#include "../lib/types.h"

bool checkCollisionBetweenBoxes(Boxes*);
bool checkPuzzleSolution(GameState*);
void handleBoxesOnTarget(Boxes*, Goals*);


bool checkCollisionBetweenBoxes(Boxes *boxes) {
  
  for(int i = 0; i < boxes->lenght; i++) {
    for(int j = 0; j < boxes->lenght; j++) {
      if(boxes->list[i].x && boxes->list[j].x && boxes->list[i].y 
      && boxes->list[j].y && boxes->list[i].id != boxes->list[j].id) {
        return true;
      }
    }
  }

  return false;
}

bool checkPuzzleSolution(GameState *gameState) {
  
  int completePuzzle = 0;
  
  for(int i = 0; i < gameState->boxes->lenght; i++) {
    if(gameState->boxes->list[i].enable)
      completePuzzle++;
  }

  return completePuzzle == gameState->boxes->lenght;

}

void handleBoxesOnTarget(Boxes *boxes, Goals *goals) {

  for(int i = 0; i < boxes->lenght; i++) {
    
    boxes->list[i].enable = false;

    for(int j = 0; j < goals->lenght; j++) {
      if(boxes->list[i].x == goals->list[j].x && boxes->list[i].y == goals->list[j].y) {
        boxes->list[i].enable = true;
      }
    }
  }
}

#endif // __LOGIC_SOKOBAN_H__