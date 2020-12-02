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

  #define SIZE 21
  
  Boxes boxes;
  Goals goals;
  GameState gameState;
  Object character;
  

  gameState.currrentMap.width = SIZE;
  gameState.currrentMap.height = SIZE;
  gameState.boxes = &boxes;
  gameState.character = &character;

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
  int timeStart = time(0);
  
  do {
    
    gotoxy(0, 0);
    printf("Time: %lds", time(0) - timeStart);

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

  destroy(&boxes, "Boxes");
  destroy(&goals, "Goals");
  destroy(&gameState, "GameState");

  return 0;
}
