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
      if (key == CTRL_C)
        break;
      
      if(key == KEY_H_L || key == KEY_H_U)
        howToPlay();

      moveDoll(&gameState, &character, key);
      moveBoxes(&gameState, &boxes, &character, key);

      handleBoxesOnTarget(&boxes, &goals);
      gameState.win = checkPuzzleSolution(&gameState);
      
      
      if(gameState.win)
        nextLevel(&gameState, &savestate, &world);

      if(key == KEY_R_U || key == KEY_R_L)
        resetLevel(&gameState, &savestate, &world);
      
      clear();
      draw(&gameState);

    }

  } while (key != KEY_ENTER);

  clear();

  destroy(&boxes, "Boxes");
  destroy(&goals, "Goals");
  destroy(&world, "World");
  destroy(&gameState, "GameState");
  destroy(&savestate, "SaveState");

}

#endif //__GAME_SOKOBAN_INIT_H__