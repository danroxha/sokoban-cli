#ifndef __GAME_SOKOBAN_INIT_H__
#define __GAME_SOKOBAN_INIT_H__

#include "../lib/sokoban.h"
#include "setting.h"
#include "logic.h"
#include "move.h"
#include "savestate.h"

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

  gameState.currrentMap = loadMap(world.levels[savestate.world].paths[savestate.level]);

  
  configGameState(&gameState);
  configCharacter(&character, &gameState);
  configBoxes(&boxes, &gameState);
  configGoals(&goals, &gameState);

  clear();

  drawMap(&gameState);
  gotoxy(character.x, character.y);


  int key;
 
  
  do {
    
    drawTimeBar(&gameState);
    drawHelpBar(&gameState);

    if (kbhit()) {

      key = readch();
      if (key == CTRL_C)
        break;

      moveDoll(&gameState, &character, key);
      moveBoxes(&gameState, &boxes, &character, key);

      handleBoxesOnTarget(&boxes, &goals);
      gameState.win = checkPuzzleSolution(&gameState);
      
      
      if(gameState.win)
        nextLevel(&gameState, &savestate, &world);

      if(key == KEY_R_U || key == KEY_R_L)
        resetLevel(&gameState, &savestate, &world);
      
      clear();
      drawMap(&gameState);
      
    }

    drawObject(&character);
    drawBoxes(&boxes);

  } while (key != KEY_ENTER);

  clear();

  destroy(&boxes, "Boxes");
  destroy(&goals, "Goals");
  destroy(&world, "World");
  destroy(&gameState, "GameState");
  destroy(&savestate, "SaveState");

}

#endif //__GAME_SOKOBAN_INIT_H__