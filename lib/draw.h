#ifndef __DRAW_SOKOBAN_H__
#define __DRAW_SOKOBAN_H__

#include <stdio.h>
#include <string.h>
#include "types.h"
#include "screen.h"
#include "util.h"

void drawMap(GameState*);
void drawBoxes(Boxes*);
void drawObject(Object*);
void drawIimeBar(GameState*);
void drawHelpBar(GameState *gameState);

static int centerWidth = 0;
static int centerHeight = 0;

void drawBoxes(Boxes *boxes) {
    
  for(int i = 0; i < boxes->lenght; i++) {
    
    gotoxy(centerWidth + boxes->list[i].x, centerHeight + boxes->list[i].y);
    
    if(boxes->list[i].enable)
      textcolor(BGC_IGREEN);
    else 
      textcolor(BGC_IRED);
  
    printf("%c", boxes->list[i].body);
    reset_video();
  }
}

void drawMap(GameState *gameState) {

  Screen screen = getScreenSize();
  centerWidth  = screen.centerWidth - gameState->currrentMap.width / 2;
  centerHeight = screen.centerHeight - gameState->currrentMap.height / 2;
  

  for(int y = 0; y < gameState->currrentMap.height; y++) {
    
    enum  {
      LINE_STRING_WORLD = 1,
      LINE_STRING_LEVEL = 2,
    };

    if(y == LINE_STRING_WORLD || y == LINE_STRING_LEVEL) {

      gotoxy(centerWidth + 1, centerHeight + y + 1);
      textcolor(IYELLOW);
      printf("%s", gameState->currrentMap.field[y]);
      reset_video();
      continue;

    }

    for(int x = 0; x < gameState->currrentMap.width; x++) {
      
      gotoxy(centerWidth + x + 1, centerHeight + y + 1);
    
      if (gameState->currrentMap.field[y][x] == TARGET) {
        textcolor(IGREEN);
        printf("%c", gameState->currrentMap.field[y][x]);
        reset_video();
      }
      // DRAW WALL
      else if (gameState->currrentMap.field[y][x] == WALL) {
        textcolor(BGC_CYAN);
        printf("%c", gameState->currrentMap.field[y][x]);
        reset_video();
      }
      // DRAW ANY
      else {
        printf("%c", gameState->currrentMap.field[y][x]);
      }
    }
  }
}

void drawObject(Object *object) {
  
  gotoxy(centerWidth + object->x, centerHeight + object->y);
  textcolor(IYELLOW);
  printf("%c", object->body);
  reset_video();

}

void drawIimeBar(GameState *gameState) {

  Screen screen = getScreenSize();
  
  int stopwatch = time(0) - gameState->time;
  char* textTime = "Time: ";
  char* labelTime = (char*) calloc(strlen(textTime) + numberLength(stopwatch), sizeof(char));
  
  sprintf(labelTime, "%s%ds", textTime, stopwatch);

  int x  = screen.centerWidth - strlen(labelTime) / 2.5;
  int y = screen.centerHeight + gameState->currrentMap.height / 1.5;

  gotoxy(x, y);
  printf("%s", labelTime);
  
  free(labelTime);
}

void drawHelpBar(GameState *gameState) {
  
  Screen screen = getScreenSize();
  const float MARGIN_X = 6.0;
  const float MARGIN_Y = 2.0;
  
  const char* helpText = "\033[36;1m'Menu'\033[0;0m - \033[32;1mENTER\033[0;0m |\
 \033[36;1m'Restart'\033[0;0m - \033[32;1mR\033[0;0m";
  
  int x = screen.centerWidth - strlen(helpText) / MARGIN_X;
  int y = screen.centerHeight - gameState->currrentMap.height / MARGIN_Y;

  gotoxy(x, y);
  textcolor(ICYAN);
  textcolor(ICYAN);
  printf("%s", helpText);
  reset_video();
  
}

#endif //__DRAW_SOKOBAN_H__