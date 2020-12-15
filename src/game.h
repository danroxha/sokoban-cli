#ifndef __GAME_SOKOBAN_INIT_H__
#define __GAME_SOKOBAN_INIT_H__

#include "sokoban.h"


//#define __DEBUGGER_BUILD_MAP_TEST__


void game() {
  
  srand(time(0));
  
  #ifdef __DEBUGGER_BUILD_MAP_TEST__
    hasIssueInMapsFile("world/");
    return 0;
  #endif
  
  Boxes boxes;
  Goals goals;
  GameState gameState;
  Object character;
  
  gameState.boxes = &boxes;
  gameState.character = &character;
  gameState.running = true;

  SaveState savestate = loadSaveState("savestate/");
  World world = loadWorlds("world/");

  bool isCorruptedSavestate = savestate.world > world.total || savestate.level > world.levels[savestate.world].total;
  
  if(isCorruptedSavestate) {
    removeSaveState("savestate/");
    savestate = loadSaveState("savestate/");
  }

  gameState.currrentMap = loadMap(world.levels[savestate.world].paths[savestate.level]);

  
  configGameState(&gameState);
  configCharacter(&character, &gameState);
  configBoxes(&boxes, &gameState);
  configGoals(&goals, &gameState);

  clear();

  draw(&gameState);

  int key;
  
  do {
    
    drawTimeBar(&gameState);
  
    if (kbhit()) {

      key = readch();

      switch(key) {
        case CTRL_C: {
          gameState.running = false;
          break;
        }
        case KEY_H_L:
        case KEY_H_U: {
          howToPlay();
          break;
        }
        case KEY_R_L:
        case KEY_R_U: {
          resetLevel(&gameState, &savestate, &world);  
        }
      }
        

      moveDoll(&gameState, &character, key);
      moveBoxes(&gameState, &boxes, &character, key);

      handleBoxesOnTarget(&boxes, &goals);
      gameState.win = checkPuzzleSolution(&gameState);
      
      
      if(gameState.win)
        nextLevel(&gameState, &savestate, &world);
      
      clear();
      draw(&gameState);

    }

  } while (key != KEY_ENTER && gameState.running);

  clear();

  destroy(&boxes, "Boxes");
  destroy(&goals, "Goals");
  destroy(&world, "World");
  destroy(&gameState, "GameState");
  destroy(&savestate, "SaveState");

}

#endif //__GAME_SOKOBAN_INIT_H__