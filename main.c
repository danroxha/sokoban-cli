#include "./lib/sokoban.h"
#include "setting.h"
#include "logic.h"
#include "move.h"

//#define __DEBUGGER_BUILD_MAP_TEST__


int main() {
  
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
  gameState.time = time(0);

  gameState.currrentMap = loadMap("./world/level_2/level_2_1.map");
  
  
  init_keyboard();
  nocursor();

  
  configGameState(&gameState);
  configCharacter(&character, &gameState);
  configBoxes(&boxes, &gameState);
  configGoals(&goals, &gameState);

  clear();

  drawMap(&gameState);
  gotoxy(character.x, character.y);


  int key;
 
  
  do {
    
    drawIimeBar(&gameState);

    if (kbhit()) {

      key = readch();
      if (key == CTRL_C)
        break;

      moveDoll(&gameState, &character, key);
      moveBoxes(&gameState, &boxes, &character, key);

      handleBoxesOnTarget(&boxes, &goals);
      checkPuzzleSolution(&gameState);
      
      clear();
      drawMap(&gameState);
      
    }

    drawObject(&character);
    drawBoxes(&boxes);


  } while (!gameState.gameOver);

  close_keyboard();
  clear();
  showcursor();

  destroy(&boxes, "Boxes");
  destroy(&goals, "Goals");
  destroy(&gameState, "GameState");

  return 0;
}
