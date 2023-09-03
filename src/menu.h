#ifndef __MENU_SOKOBAN_H__
#define __MENU_SOKOBAN_H__
#include "sokoban.h"

void how_to_play();

void how_to_play() {
  
  int key;
  clear();
  draw_banner_how_to_play();
  Screen statusScreenOld = get_screen_size();
  
  do {

  	Screen statusScreenNew = get_screen_size();

	if(diff_screen(&statusScreenOld, &statusScreenNew)) {
		statusScreenOld = statusScreenNew;
		clear();
		draw_banner_how_to_play();	
	}
    
    if(kbhit()){
      
      key = readch();
      clear();
    }
    draw_banner_how_to_play();
  }
  while(key != KEY_ENTER && key != KEY_H_U && key != KEY_H_L);
  clear();
}

void draw_menu(Cursor *cursor, int *option) {

  Screen screen = get_screen_size();
  const char* banner[] =  {
   "\033[31;1m",
   " ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄   ▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄ ▄▄    ▄ ",
   "█       █       █   █ █ █       █  ▄    █      █  █  █ █",
   "█  ▄▄▄▄▄█   ▄   █   █▄█ █   ▄   █ █▄█   █  ▄   █   █▄█ █",
   "█ █▄▄▄▄▄█  █ █  █      ▄█  █ █  █       █ █▄█  █       █",
   "█▄▄▄▄▄  █  █▄█  █     █▄█  █▄█  █  ▄   ██      █  ▄    █",
   " ▄▄▄▄▄█ █       █    ▄  █       █ █▄█   █  ▄   █ █ █   █",
   "█▄▄▄▄▄▄▄█▄▄▄▄▄▄▄█▄▄▄█ █▄█▄▄▄▄▄▄▄█▄▄▄▄▄▄▄█▄█ █▄▄█▄█  █▄▄█",
   "\033[0;0m",
   "                                                        ",
   "                       \033[32;1mC\033[0;0montinue      ",
   "                       \033[32;1mN\033[0;0mew Game      ",
   "                       \033[32;1mH\033[0;0mow to play   ",
   "                       \033[32;1mE\033[0;0mxit          ",
  };


  enum BannerLine {
    LINE_NINE     = 9,
    LINE_TEN      = 10,
    LINE_THIRTEEN = 13,
  };

  bool is_continue  = there_is_save_state("savestate/");
  int center_width  = screen.center_width - strlen(banner[LINE_NINE]) / 2;
  int center_height = screen.height / 4;
  int center_banner = center_width;
  int selection    = 0;


  cursor->x = center_width + strlen(banner[LINE_NINE]) / 2.6;
  if(cursor->y <  center_height + LINE_TEN)
    cursor->y = center_height + LINE_THIRTEEN - (int) !is_continue;
  if(cursor->y > center_height + LINE_THIRTEEN - (int) !is_continue)
    cursor->y = center_height + LINE_TEN;

  selection = cursor->y - center_height - LINE_NINE + (int)!is_continue;
  
  int hiden_option = 0;
  int size = sizeof(banner) / sizeof(char*);
  for(int i = 0; i < size; i++) {
    if(!is_continue && i == LINE_TEN) {
      hiden_option = 1;
      continue;
    }

    goto_xy(center_banner, center_height + i - hiden_option); 
    printf("%s", banner[i]);
  }
 
  *option = selection;
}

#endif // __MENU_SOKOBAN_H__
