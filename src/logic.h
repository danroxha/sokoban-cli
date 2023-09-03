#ifndef __LOGIC_SOKOBAN_H__
#define __LOGIC_SOKOBAN_H__

#include <stdbool.h>
#include "../lib/types.h"

bool check_collision_between_boxes(Boxes*);
void check_puzzle_solution(GameState*);
void handle_boxes_on_target(Boxes*, Goals*);


bool check_collision_between_boxes(Boxes *boxes) {
  
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

void check_puzzle_solution(GameState *game_state) {
  
  int completed_puzzle = 0;
  
  for(int i = 0; i < game_state->boxes->lenght; i++) {
    if(game_state->boxes->list[i].enable)
      completed_puzzle++;
  }

  game_state->win = completed_puzzle == game_state->boxes->lenght;

}

void handle_boxes_on_target(Boxes *boxes, Goals *goals) {

  for(int i = 0; i < boxes->lenght; i++) {
    
    boxes->list[i].enable = false;
  

    for(int j = 0; j < goals->lenght; j++) {
      goals->list[j].redraw = true;
      if(boxes->list[i].x == goals->list[j].x && boxes->list[i].y == goals->list[j].y) {
        boxes->list[i].enable = true;
        boxes->list[i].redraw = true;
        goals->list[j].redraw = false;
      }
    }
  }
}

#endif // __LOGIC_SOKOBAN_H__