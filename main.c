#include <stdio.h>
#include <stdbool.h>
#include "lib/keyboard.h"
#include "lib/types.h"
#include "lib/screen.h"
#include "src/game.h"
#include "src/menu.h"


int main() {

  Cursor cursor = {.x=0, .y=0, .pointer='>'};
  Program program = {.running=true};
  Screen statusScreenOld = getScreenSize();

  int menuOption = 0;
  
  init_keyboard();
  nocursor();
  clear();
  

  
  drawMenu(&cursor, &menuOption);

  do {

    Screen statusScreenNew = getScreenSize();

      if(diffScreen(&statusScreenOld, &statusScreenNew)) {
        statusScreenOld = statusScreenNew;
        clear();
        drawMenu(&cursor, &menuOption);
      }
      
    if(kbhit()) {

      int key = readch();

      if(key == CTRL_C)
        break;

      if(key == KEY_ARROW_UP) cursor.y--;
      if(key == KEY_ARROW_DOWN) cursor.y++;
      if(key == KEY_ENTER) {
        switch(menuOption){
          case MENU_CONTINUE: {
            game();
            break;
          }
          case MENU_NEW_GAME: {
            removeSaveState("savestate/");
            game();
            break;
          }
          case MENU_HOW_TO_PLAY: {
            howToPlay();
            break;
          }
          case MENU_EXIT: {
            program.running = false;
            break;
          }
        }	
      }
        
      drawMenu(&cursor, &menuOption);
    }
    
    gotoxy(cursor.x, cursor.y);
    textcolor(IRED);
    printf("%c", cursor.pointer);
    reset_video();

  }
  while(program.running);
  
  close_keyboard();
  showcursor();
  clear();
  
  return 0;
}

