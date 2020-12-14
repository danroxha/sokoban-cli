#ifndef __DRAW_SOKOBAN_H__
#define __DRAW_SOKOBAN_H__

#include <stdio.h>
#include <string.h>
#include "../lib/types.h"
#include "../lib/screen.h"
#include "../lib/util.h"

void draw(GameState*);
void drawMap(GameState*);
void drawBoxes(Boxes*);
void drawGoals(Goals*);
void drawObject(Object*, char*, bool);
void drawIimeBar(GameState*);
void drawHelpBar(GameState*);
void drawBannerHowToPlay(void);

static int centerWidth = 0;
static int centerHeight = 0;

void draw(GameState *gameState){

  drawHelpBar(gameState);
  drawMap(gameState);
  drawGoals(gameState->goals);
  drawBoxes(gameState->boxes);
  drawObject(gameState->character, BGC_IYELLOW, false);

}

void drawBoxes(Boxes *boxes) {
    
  for(int i = 0; i < boxes->lenght; i++) {
    
    gotoxy(centerWidth + boxes->list[i].x, centerHeight + boxes->list[i].y);
    
    if(boxes->list[i].enable)
      textcolor(BGC_IGREEN);
    else 
      textcolor(BGC_IRED);
  
    printf(" ");
    reset_video();
  }
}

void drawGoals(Goals *goals) {
  
  for(int i = 0; i < goals->lenght; i++) {
   drawObject(&goals->list[i], IGREEN, true);
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

      // DRAW WALL
      if (gameState->currrentMap.field[y][x] == WALL) {
        textcolor(BGC_CYAN);
        printf(" ");
        reset_video();
      }
      // DRAW ANY
      else {
        printf(" ");
      }
    }
  }
}

void drawObject(Object *object,char *color, bool enableChar) {
  
  gotoxy(centerWidth + object->x, centerHeight + object->y);
  textcolor(color);
  
  if(enableChar)
    printf("%c", object->body);
  else
    printf(" ");

  reset_video();

}

void drawTimeBar(GameState *gameState) {

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

void drawBannerHowToPlay(void) {
	
	Screen screen = getScreenSize();
  
  const char* tutorial[] = {
    "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",
    "█░████▀▄▄▀█░███░███▄░▄█▀▄▄▀███▀▄▄▀█░██░▄▄▀█░██░█",
    "█░▄▄░█░██░█▄▀░▀▄████░██░██░███░▀▀░█░██░▀▀░█░▀▀░█",
    "█▄██▄██▄▄███▄█▄█████▄███▄▄████░████▄▄█▄██▄█▀▀▀▄█",
    "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀",
    "      Use the arrows to move the character      ",
    "      and the r key to restart the level.       ",
    "             \033[33;1m↑                        ",
    "           ←   →               r                ",
    "             ↓\033[0m                           ", 
    "           \033[34;1mArrows\033[0m           \033[34;1mRestart\033[0m",
    "                                                ",
    "                                                ",
    "            \033[0;34;5mPress ENTER to return\033[0m",
  };

  const float MARGIN_X = 6.0;
  const float MARGIN_Y = 4.0;

  int size =  (int)sizeof(tutorial) / sizeof(char*);
  int verticalAlign   = screen.centerWidth - strlen(tutorial[0]) / MARGIN_X;
  int horizontalAlign = screen.height / MARGIN_Y;

  for(int i = 0; i < size; i++) {
    gotoxy(verticalAlign, horizontalAlign + i);
    printf("%s", tutorial[i]);
  }

  reset_video();

}


#endif //__DRAW_SOKOBAN_H__
