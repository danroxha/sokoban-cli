#ifndef __DRAW_SOKOBAN_H__
#define __DRAW_SOKOBAN_H__

#include <stdio.h>
#include "types.h"
#include "screen.h"

void drawMap(GameState*);
void drawBoxes(Boxes*);
void drawObject(Object*);

void drawBoxes(Boxes *boxes) {
  for(int i = 0; i < boxes->lenght; i++) {
    gotoxy(boxes->list[i].x, boxes->list[i].y);
    if(boxes->list[i].enable) {
      printf("\x1b[37;42;1m");
    }
    else {
      printf("\x1b[41;1m");
    }
    printf("%c", boxes->list[i].body);
    printf("\x1b[0m");
  }
}

void drawMap(GameState *gameState) {

  for(int i = 0; i < gameState->currrentMap.height; i++)
    for(int j = 0; j < gameState->currrentMap.width; j++) {
   
      if (gameState->currrentMap.field[i][j] == TARGET) {
        printf("\x1b[32;1m");
        printf("%c", gameState->currrentMap.field[i][j]);
        printf("\x1b[0m");
      }
      // DRAW WALL
      else if (gameState->currrentMap.field[i][j] == WALL) {
        printf("\x1b[46m");
        printf("%c", gameState->currrentMap.field[i][j]);
        printf("\x1b[0m");
      }
      // DRAW ANY
      else {
        printf("%c", gameState->currrentMap.field[i][j]);
      }
    }

    gotoxy(gameState->character->x, gameState->character->y);
}

void drawObject(Object *object) {
  
  gotoxy(object->x, object->y);
  printf("\x1b[33;1m");
  printf("%c", object->body);

}


#endif //__DRAW_SOKOBAN_H__