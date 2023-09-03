#ifndef __DRAW_SOKOBAN_H__
#define __DRAW_SOKOBAN_H__

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../lib/types.h"
#include "../lib/screen.h"
#include "../lib/util.h"

void draw(GameState*);
void draw_map(GameState*);
void draw_boxes(GameState*);
void draw_goals(GameState*);
void draw_object(Object*, char*, bool);
void draw_time_bar(GameState*);
void draw_help_bar(GameState*);
void draw_caption(GameState*);
void draw_character(GameState *);
void draw_banner_how_to_play(void);
void draw_win_message(void);
void draw_next_level_message(void);
void clear_shadow(Object *);

static int center_width = 0;
static int center_height = 0;

void draw(GameState *game_state) { 
  clear_shadow(game_state->character);
  draw_help_bar(game_state);
  draw_caption(game_state);
  draw_map(game_state);
  draw_goals(game_state);
  draw_boxes(game_state);
  draw_character(game_state);

  game_state->force_draw = false;
}

void draw_character(GameState *game_state) {
    Object character = *game_state->character;
    bool different_from_the_shadow = character.x != character.sx || character.y != character.sy;
    
    if(different_from_the_shadow || game_state->force_draw) {
      draw_object(game_state->character, BGC_IYELLOW, false);
    }
      
}

void draw_boxes(GameState *game_state) {
  for(int i = 0; i < game_state->boxes->lenght; i++) {
    if(!game_state->boxes->list[i].redraw && !game_state->force_draw) continue;
    game_state->boxes->list[i].redraw = false;
    goto_xy(center_width + game_state->boxes->list[i].x, center_height + game_state->boxes->list[i].y);
    
    if(game_state->boxes->list[i].enable) {
      text_color(BGC_IGREEN);
    }
    else {
      text_color(BGC_IRED);
    }
  
    printf(" ");
    reset_video();
  }
}

void draw_goals(GameState *game_state) {
  for(int i = 0; i < game_state->goals->lenght; i++) { 
    if(game_state->goals->list[i].redraw || game_state->force_draw) {
      draw_object(&game_state->goals->list[i], "\033[32;1m\033[32;5m", true);
    }
  }
}

void clear_shadow(Object *object) {
  bool different_from_the_shadow = object->x != object->sx || object->y != object->sy;
  if(different_from_the_shadow) {
    goto_xy(center_width + object->sx, center_height + object->sy);
    printf(" ");
  }
}

void draw_map(GameState *game_state) {

  Screen screen = get_screen_size();
  center_width  = screen.center_width - game_state->current_map.width / 2;
  center_height = screen.center_height - game_state->current_map.height / 2;
  

  for(int y = 0; y < game_state->current_map.height; y++) {
    enum  {
      LINE_STRING_WORLD = 1,
      LINE_STRING_LEVEL = 2,
    };

    if(y == LINE_STRING_WORLD || y == LINE_STRING_LEVEL) {
      goto_xy(center_width + 1, center_height + y + 1);
      text_color(IYELLOW);
      printf("%s", game_state->current_map.field[y]);
      reset_video();
      continue;
    }

    for(int x = 0; x < game_state->current_map.width; x++) {
      
      goto_xy(center_width + x + 1, center_height + y + 1);

      // DRAW WALL
      if (game_state->current_map.field[y][x] == WALL) {
        text_color(BGC_CYAN);
        printf(" ");
        reset_video();
      }
    }
  }
}

void draw_object(Object *object,char *color, bool enable_char) {
  
  goto_xy(center_width + object->x, center_height + object->y);
  text_color(color);
  
  if(enable_char)
    printf("%c", object->body);
  else
    printf(" ");

  reset_video();
}

void draw_time_bar(GameState *game_state) {

  Screen screen = get_screen_size();
  
  int stopwatch = time(0) - game_state->time;
  char* textTime = "Time: ";
  char* label_time = (char*) calloc(strlen(textTime) + number_length(stopwatch), sizeof(char));
  
  sprintf(label_time, "%s%ds", textTime, stopwatch);

  int x  = screen.center_width - strlen(label_time) / 2.5;
  int y = screen.center_height + game_state->current_map.height / 1.5;

  goto_xy(x, y);
  printf("%s", label_time);
  
  free(label_time);
}

void draw_help_bar(GameState *game_state) {
  
  Screen screen = get_screen_size();
  const float MARGIN_X = 6.0;
  const float MARGIN_Y = 2.0;
  
  const char* helpText = "\033[36;1m'Menu'\033[0;0m - \033[32;1mENTER\033[0;0m |\
 \033[36;1m'Restart'\033[0;0m - \033[32;1mR\033[0;0m";
  
  int x = screen.center_width - strlen(helpText) / MARGIN_X;
  int y = screen.center_height - game_state->current_map.height / MARGIN_Y;

  goto_xy(x, y);
  text_color(ICYAN);
  text_color(ICYAN);
  printf("%s", helpText);
  reset_video();
  
}

void draw_banner_how_to_play(void) {
	
  Screen screen = get_screen_size();
  
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
    "          \033[0;34;5mPress ENTER or H to return\033[0m",
  };

  const float MARGIN_X = 6.0;
  const float MARGIN_Y = 4.0;

  int size =  (int)sizeof(tutorial) / sizeof(char*);
  int vertical_align   = screen.center_width - strlen(tutorial[0]) / MARGIN_X;
  int horizontal_align = screen.height / MARGIN_Y;

  for(int i = 0; i < size; i++) {
    goto_xy(vertical_align, horizontal_align + i);
    printf("%s", tutorial[i]);
  }

  reset_video();

}

void draw_caption(GameState *game_state) {

  Screen screen = get_screen_size();

  const char* caption[] = {
    "\033[43m \033[0;0m - Character",
    "\033[41m \033[0;0m - Boxes    ",
    "\033[32;1m?\033[0;0m - Goals  ",
    "\033[31;1mH\033[0;0m - Tutorial  ",
  };

  
  int size = sizeof(caption) / sizeof(char*);
  for(int i = 0; i < size; i++) {
    goto_xy(screen.center_width + game_state->current_map.width , screen.center_height + i);
    printf("%s", caption[i]);
  }
}

void draw_win_message(void) {
  const char* message[] = {
    "                         ",
    "█░░▒█ █ █▄░█ █▄░█ ██▀ █▀▄",
    "▀▄▀▄▀ █ █▒▀█ █▒▀█ █▄▄ █▀▄",
    "                         ",
    "       ___________       ",
    "      '._==_==_=_.'      ",
    "      .-\\:      /-.     ",
    "     | (|:.     |) |     ",
    "      '-|:.     |-'      ",
    "        \\::.    /       ",
    "         '::. .'         ",
    "           ) (           ",
    "         _.' '._         ",
    "        `\"\"\"\"\"\"\"` "
  };
  
  Screen screen = get_screen_size();
  const float MARGIN_X = 2.0;
  const float MARGIN_Y = 4.0;

  int size =  (int)sizeof(message) / sizeof(char*);
  int vertical_align   = screen.center_width - strlen(message[0]) / MARGIN_X;
  int horizontal_align = screen.height / MARGIN_Y;

  const int seconds = 3;
  int times = time(0);
  
  clear();
  text_color(IYELLOW);
  do {
    for(int i = 0; i < size; i++) {
      goto_xy(vertical_align, horizontal_align + i);
      printf("%s", message[i]);
    }

  }while(times + seconds > time(0));

  reset_video();

}

void draw_next_level_message(void) {
  
  
  Screen screen = get_screen_size();
  
  
  const char* message[] = {
   "  █▄░█ █▀▀ ▀▄▀ ▀█▀ ",
   "  █░▀█ ██▄ █░█ ░█░ ",
   "                   ",
   "█░░ █▀▀ █░█ █▀▀ █░░",
   "█▄▄ ██▄ ▀▄▀ ██▄ █▄▄",
  };
  
  
  const float MARGIN_X = 5.0;
  const float MARGIN_Y = 2.5;

  int size =  (int)sizeof(message) / sizeof(char*);
  int vertical_align   = screen.center_width - strlen(message[0]) / MARGIN_X;
  int horizontal_align = screen.height / MARGIN_Y;

  const int seconds = 3;
  int times = time(0);
  
  clear();
  text_color(ICYAN);

  do {
    for(int i = 0; i < size; i++) {
      goto_xy(vertical_align, horizontal_align + i);
      printf("%s", message[i]);
    }
  }
  while(times + seconds > time(0));

  reset_video();
}

#endif //__DRAW_SOKOBAN_H__
