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
  Screen status_old_screen = get_screen_size();

  int menu_option = 0;
  
  init_keyboard();
  no_cursor();
  clear();
  
  draw_menu(&cursor, &menu_option);

  do {

    Screen status_new_screen = get_screen_size();

      if(diff_screen(&status_old_screen, &status_new_screen)) {
        status_old_screen = status_new_screen;
        clear();
        draw_menu(&cursor, &menu_option);
      }
      
    if(kbhit()) {

      int key = readch();

      if(key == CTRL_C)
        break;

      if(key == KEY_ARROW_UP) cursor.y--;
      if(key == KEY_ARROW_DOWN) cursor.y++;
      if(key == KEY_ENTER) {
        switch(menu_option){
          case MENU_CONTINUE: {
            game();
            break;
          }
          case MENU_NEW_GAME: {
            remove_save_state(SAVE_STATE_PATH);
            game();
            break;
          }
          case MENU_HOW_TO_PLAY: {
            how_to_play();
            break;
          }
          case MENU_EXIT: {
            program.running = false;
            break;
          }
        }	
      }
        
      draw_menu(&cursor, &menu_option);
    }
    
    goto_xy(cursor.x, cursor.y);
    text_color(IRED);
    printf("%c", cursor.pointer);
    reset_video();

  }
  while(program.running);
  
  close_keyboard();
  show_cursor();
  clear();
  
  return 0;
}

