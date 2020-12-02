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
  
    
    //switch (key){
    //  default: {
    //    printf("\nTecla:: %d", key);
    //    break;
    //  }
    //  case KEY_ARROW_UP: {
    //    printf("\nTecla: ↑ : %d", key);
    //    break;
    //  }
    //  case KEY_ARROW_DOWN: {
    //    printf("\nTecla: ↓ : %d", key);
    //    break;
    //  }
    //  case KEY_ARROW_RIGHT: {
    //    printf("\nTecla: → : %d", key);
    //    break;
    //  }
    //  case KEY_ARROW_LEFT: {
    //    printf("\nTecla: ← : %d", key);
    //    break;
    //  }
    //
    //}

  } while (!gameState.gameOver);

  close_keyboard();
  clear();

  if(boxes.list) free(boxes.list);
  if(goals.list) free(goals.list);
  if(gameState.currrentMap.field) {
    for(int i = 0; i < gameState.currrentMap.height; i++) {
      free(gameState.currrentMap.field[i]);
    }
  }

  return 0;
}

