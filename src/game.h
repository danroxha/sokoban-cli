#ifndef __GAME_SOKOBAN_INIT_H__
#define __GAME_SOKOBAN_INIT_H__

#include "sokoban.h"


//#define __DEBUGGER_BUILD_MAP_TEST__
void game();

void game() {
  
  srand(time(0));
  
  #ifdef __DEBUGGER_BUILD_MAP_TEST__
    has_issue_in_maps_file("world/");
    return 0;
  #endif
  
  Boxes boxes;
  Goals goals;
  GameState game_state;
  Object character;
  Screen status_old_screen = get_screen_size();
  
  game_state.boxes = &boxes;
  game_state.character = &character;
  game_state.running = true;

  SaveState save_state = load_save_state(SAVE_STATE_PATH);
  World world = load_worlds("world/");

  bool is_corrupted_save_state = save_state.world > world.total || save_state.level > world.levels[save_state.world].total;
  
  if(is_corrupted_save_state) {
    remove_save_state(SAVE_STATE_PATH);
    destroy(&save_state, "SaveState");
    save_state = load_save_state(SAVE_STATE_PATH);
  }

  game_state.current_map = load_map(world.levels[save_state.world].paths[save_state.level]);

  config_game_state(&game_state);
  config_character(&character, &game_state);
  config_boxes(&boxes, &game_state);
  config_goals(&goals, &game_state);

  clear();

  draw(&game_state);

  int key;
  
  do {
    
    draw_time_bar(&game_state);

    Screen status_new_screen = get_screen_size();
    
    if(diff_screen(&status_old_screen, &status_new_screen)) {
      status_old_screen = status_new_screen;
      game_state.force_draw = true;
      clear();
      draw(&game_state);
    }
  
    if (kbhit()) {

      key = readch();

      switch(key) {
        case CTRL_C: {
          game_state.running = false;
          break;
        }
        case KEY_H_L:
        case KEY_H_U: {
          how_to_play();
          game_state.force_draw = true;
          break;
        }
        case KEY_R_L:
        case KEY_R_U: {
          clear();
          reset_level(&game_state, &save_state, &world);  
        }
      }

      move_character(&game_state, &character, key);
      move_boxes(&game_state, &boxes, &character, key);

      handle_boxes_on_target(&boxes, &goals);

      for(int i = 0; i < goals.lenght; i++) {
        if(goals.list[i].x == character.x && goals.list[i].y == character.y) {
          goals.list[i].redraw = false;
        }
      }

      check_puzzle_solution(&game_state);
      
      if(game_state.win) {
        next_level(&game_state, &save_state, &world);
        clear();
      }
      
      draw(&game_state);
    }

  } while (key != KEY_ENTER && game_state.running);

 
  destroy(&boxes, "Boxes");
  destroy(&goals, "Goals");
  destroy(&world, "World");
  destroy(&game_state, "GameState");
  destroy(&save_state, "SaveState");
  clear();
}

#endif //__GAME_SOKOBAN_INIT_H__
