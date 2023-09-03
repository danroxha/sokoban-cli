#ifndef __SETTING_SOKOBAN_H__
#define __SETTING_SOKOBAN_H__

#include <stdlib.h>
#include <time.h>
#include "../lib/types.h"
#include "savestate.h"

void config_character(Object*, GameState*);
void config_boxes(Boxes*, GameState*);
void config_goals(Goals*, GameState*);
void config_game_state(GameState*);

void config_character(Object *character, GameState *game_state) {
  
  character->body = DOLL;
  character->redraw = true;
 
  for (int y = 0; y < game_state->current_map.height; y++)  {
    for (int x = 0; x < game_state->current_map.width; x++) {
      if (game_state->current_map.field[y][x] == DOLL) {
        character->x = x + 1;
        character->y = y + 1;
        game_state->current_map.field[y][x] = ' ';
        break;
      }
    }
  }
  character->sx = character->x;
  character->sy = character->y;
}

void config_boxes(Boxes *boxes, GameState *game_state) {
  
  boxes->list   = NULL;
  boxes->lenght = 0;

 for (int y = 0; y < game_state->current_map.height; y++) 
    for (int x = 0; x < game_state->current_map.width; x++) {
      if(game_state->current_map.field[y][x] == BOX) {
        boxes->lenght++;
      }
    }

  boxes->list = (Box*) calloc(boxes->lenght, sizeof(Box));

  for(int i = 0; i < boxes->lenght; i++) {
    boxes->list[i].body = BOX;
    boxes->list[i].enable = false;
    boxes->list[i].id = rand();
    boxes->list[i].redraw = true;
  }

  int index = 0;

  for (int y = 0; y < game_state->current_map.height; y++) 
    for (int x = 0; x < game_state->current_map.width; x++) {
      if(game_state->current_map.field[y][x] == BOX) {
        boxes->list[index].x = x + 1;
        boxes->list[index].y = y + 1;
        game_state->current_map.field[y][x] = ' ';
        index++;
      }
    }
}

void config_goals(Goals *goals, GameState *game_state) {
  
  if(goals->lenght != 0) {
    free(goals->list);
  }

  goals->lenght = 0;
  goals->list = NULL;
  game_state->goals = goals;

  
  for(int y = 0; y < game_state->current_map.height; y++) {
    for(int x = 0; x < game_state->current_map.width; x++) {
      if(game_state->current_map.field[y][x] == TARGET) {
        goals->lenght++;
        goals->list = (Object*) realloc(goals->list, goals->lenght * sizeof(Object));
        goals->list[goals->lenght - 1].redraw = true;
        goals->list[goals->lenght - 1].body = TARGET;
        goals->list[goals->lenght - 1].x = x + 1;
        goals->list[goals->lenght - 1].y = y + 1;
      }
    }
  }

  return;
}

void config_game_state(GameState *game_state) {
  game_state->win = false;
  game_state->force_draw = true;
  game_state->time = time(0);
}

void next_level(GameState *game_state, SaveState *save_state, World *world) {
  
  save_state->level++;

  if(world->levels[save_state->world].total - 1 < save_state->level) {
    save_state->world++;
    save_state->level = 0;
  }

  if(world->total <= save_state->world) {
    draw_win_message();
    save_state->world = 0;
    save_state->level = 0;
    game_state->running = false;
  }
  else {
    draw_next_level_message();
  }
  
  define_save_state(*save_state);
  
  destroy(&game_state->current_map, "Map");
  
  game_state->current_map = load_map(world->levels[save_state->world].paths[save_state->level]);
  
  config_game_state(game_state);
  config_character(game_state->character, game_state);
  config_boxes(game_state->boxes, game_state);
  config_goals(game_state->goals, game_state);

}

void reset_level(GameState *game_state, SaveState *save_state, World *world) {
  
  game_state->current_map = load_map(world->levels[save_state->world].paths[save_state->level]);

  config_game_state(game_state);
  config_character(game_state->character, game_state);
  config_boxes(game_state->boxes, game_state);
  config_goals(game_state->goals, game_state);
}

#endif // __SETTING_SOKOBAN_H__