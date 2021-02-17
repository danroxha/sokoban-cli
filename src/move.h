#ifndef __MOVE_SOKOBAN_H__
#define __MOVE_SOKOBAN_H__

#include "../lib/types.h"
#include "../lib/keyboard.h"


void moveDoll(GameState*, Object*, int);
void moveBoxes(GameState*, Boxes*, Object*, int);


void moveDoll(GameState *gameState, Object *character, int key) {
  
  bool collision_wall_top = gameState->currrentMap.field[character->y - 2][character->x - 1]    == WALL;
  bool collision_wall_bottom = gameState->currrentMap.field[character->y][character->x - 1]     == WALL;
  bool collision_wall_left = gameState->currrentMap.field[character->y - 1][character->x]       == WALL;
  bool collision_wall_right = gameState->currrentMap.field[character->y - 1][character->x - 2]  == WALL;
  
  /*
    move doll
  */
  
  character->sx = character->x;
  character->sy = character->y;
  character->redraw = true;

  if (key == KEY_ARROW_UP && !collision_wall_top) {
    character->y--;
    character->redraw = true;
  }
  else if (key == KEY_ARROW_DOWN && !collision_wall_bottom) {
    character->y++;
  }
  else if (key == KEY_ARROW_RIGHT && !collision_wall_left) {
    character->x++;
    character->redraw = true;
  }
  else if (key == KEY_ARROW_LEFT && !collision_wall_right) {
    character->x--;
    character->redraw = true;
  }
}


void moveBoxes(GameState *gameState, Boxes *boxes, Object *character, int key) {
  
  for(int i = 0; i < boxes->lenght; i++) {
    
    bool collision_wall_top    = gameState->currrentMap.field[boxes->list[i].y - 2][boxes->list[i].x - 1] == WALL;
    bool collision_wall_bottom = gameState->currrentMap.field[boxes->list[i].y][boxes->list[i].x - 1]     == WALL;
    bool collision_wall_left   = gameState->currrentMap.field[boxes->list[i].y - 1][boxes->list[i].x - 2] == WALL;
    bool collision_wall_right  = gameState->currrentMap.field[boxes->list[i].y - 1][boxes->list[i].x]     == WALL;
    

    bool collision_box = boxes->list[i].x == character->x && boxes->list[i].y == character->y;

    if (key == KEY_ARROW_UP && collision_box && !collision_wall_top) {
      
      boxes->list[i].y--;

      for(int j = 0; j < boxes->lenght; j++) {
        if(boxes->list[i].id != boxes->list[j].id && boxes->list[i].x == boxes->list[j].x 
        && boxes->list[i].y == boxes->list[j].y) {
          boxes->list[i].y++;
          character->y++;
        }
        else {
          boxes->list[i].redraw = true;
        }
      }
    }
    else if (key == KEY_ARROW_DOWN && collision_box && !collision_wall_bottom) {
      boxes->list[i].y++;
      
      for(int j = 0; j < boxes->lenght; j++) {
        if(boxes->list[i].id != boxes->list[j].id && boxes->list[i].x == boxes->list[j].x 
        && boxes->list[i].y == boxes->list[j].y) {
          boxes->list[i].y--;
          character->y--;
        }
        else {
          boxes->list[i].redraw = true;
        }
      }
    }
    else if (key == KEY_ARROW_RIGHT && collision_box && !collision_wall_right) {
      boxes->list[i].x++;
      for(int j = 0; j < boxes->lenght; j++) {
        if(boxes->list[i].id != boxes->list[j].id && boxes->list[i].x == boxes->list[j].x 
        && boxes->list[i].y == boxes->list[j].y) {
          boxes->list[i].x--;
          character->x--;
        }
        else {
          boxes->list[i].redraw = true;
        }
      }
    }
    else if (key == KEY_ARROW_LEFT && collision_box && !collision_wall_left) {
      boxes->list[i].x--;
      for(int j = 0; j < boxes->lenght; j++) {
        if(boxes->list[i].id != boxes->list[j].id && boxes->list[i].x == boxes->list[j].x 
        && boxes->list[i].y == boxes->list[j].y) {
          boxes->list[i].x++;
          character->x++;
        }
        else {
          boxes->list[i].redraw = true;
        }
      }
    }
    
    /*
      limit the movement of the doll in relation to the boxes
    */
    if (key == KEY_ARROW_UP && collision_box && collision_wall_top) {
      character->y++;
    }
    else if (key == KEY_ARROW_DOWN && collision_box && collision_wall_bottom) {
      character->y--;
    }
    else if (key == KEY_ARROW_LEFT && collision_box && collision_wall_left) {
      character->x++;
    }
    else if (key == KEY_ARROW_RIGHT && collision_box && collision_wall_right) {
      character->x--;
    }
  }
}


#endif
