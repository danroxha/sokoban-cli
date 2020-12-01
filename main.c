#include "sokoban.h"


int main() {
  
  srand(time(0));

  #define SIZE 21
  
  Boxes boxes;
  Goals goals;
  GameState gameState;
  Object character;
  

  gameState.currrentMap.width = SIZE;
  gameState.currrentMap.height = SIZE;
  gameState.boxes = &boxes;
  gameState.character = &character;

 

  char map[SIZE][SIZE] = {
  "                    \n",
  "                    \n",
  "      LEVEL 1       \n",
  "                    \n",
  "                    \n",
  "    *****           \n",
  "    *   *           \n",
  "    *#  *           \n",
  "  ***  #**          \n",
  "  *  # # *          \n",
  "*** * ** *    ******\n",
  "*   * ** ******  ??*\n",
  "* #  #           ??*\n",
  "***** ***  *@**  ??*\n",
  "    *     **********\n",
  "    *******         \n",
  "                    \n",
  "                    \n",
  "                    \n",
  "                    \n",
  "                    \n",
  };
  
  // char map[SIZE][SIZE] = {
      // "          \n",
      // "  Level 1 \n",
      // "          \n",
      // "          \n",
      // "   ##     \n",
      // "          \n",
      // "   @ #    \n",
      // "     #    \n",
      // "          \n",
      // "          \n",
      // "          \n",
  // };
  

  init_keyboard();
  nocursor();

   // COPY MAP START
  gameState.currrentMap.field = (char**) calloc(SIZE, sizeof(char*));
  
  for(int i = 0; i < SIZE; i++){
    gameState.currrentMap.field[i] = (char*) calloc(SIZE, sizeof(char));
  }
  
  for (int i = 0; i < SIZE; i++) 
    for (int j = 0; j < SIZE; j++) {
      gameState.currrentMap.field[i][j] = map[i][j];
    }
  // COPY MAP END  

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

      bool collision_wall_top = map[character.y - 2][character.x - 1]    == WALL;
      bool collision_wall_bottom = map[character.y][character.x - 1]     == WALL;
      bool collision_wall_left = map[character.y - 1][character.x]       == WALL;
      bool collision_wall_right = map[character.y - 1][character.x - 2]  == WALL;

      if (key == KEY_ARROW_UP && !collision_wall_top)
        character.y--;
      else if (key == KEY_ARROW_DOWN && !collision_wall_bottom)
        character.y++;
      else if (key == KEY_ARROW_RIGHT && !collision_wall_left)
        character.x++;
      else if (key == KEY_ARROW_LEFT && !collision_wall_right)
        character.x--;




      for(int i = 0; i < boxes.lenght; i++) {
        
        collision_wall_top    = map[boxes.list[i].y - 2][boxes.list[i].x - 1] == WALL;
        collision_wall_bottom = map[boxes.list[i].y][boxes.list[i].x - 1]     == WALL;
        collision_wall_left   = map[boxes.list[i].y - 1][boxes.list[i].x]     == WALL;
        collision_wall_right  = map[boxes.list[i].y - 1][boxes.list[i].x - 2] == WALL;
        

        bool collision_box = boxes.list[i].x == character.x && boxes.list[i].y == character.y;

        if (key == KEY_ARROW_UP && collision_box && !collision_wall_top) {
          
          boxes.list[i].y--;
          for(int j = 0; j < boxes.lenght; j++) {
            if(boxes.list[i].id != boxes.list[j].id && boxes.list[i].x == boxes.list[j].x 
            && boxes.list[i].y == boxes.list[j].y) {
              boxes.list[i].y++;
              character.y++;
            }
          }
          
        }
        else if (key == KEY_ARROW_DOWN && collision_box && !collision_wall_bottom) {
          boxes.list[i].y++;
          
          for(int j = 0; j < boxes.lenght; j++) {
            if(boxes.list[i].id != boxes.list[j].id && boxes.list[i].x == boxes.list[j].x 
            && boxes.list[i].y == boxes.list[j].y) {
              boxes.list[i].y--;
              character.y--;
            }
          }
        }
        else if (key == KEY_ARROW_RIGHT && collision_box && !collision_wall_left) {
          boxes.list[i].x++;
          for(int j = 0; j < boxes.lenght; j++) {
            if(boxes.list[i].id != boxes.list[j].id && boxes.list[i].x == boxes.list[j].x 
            && boxes.list[i].y == boxes.list[j].y) {
              boxes.list[i].x--;
              character.x--;
            }
          }
        }
        else if (key == KEY_ARROW_LEFT && collision_box && !collision_wall_right) {
          boxes.list[i].x--;
          for(int j = 0; j < boxes.lenght; j++) {
            if(boxes.list[i].id != boxes.list[j].id && boxes.list[i].x == boxes.list[j].x 
            && boxes.list[i].y == boxes.list[j].y) {
              boxes.list[i].x++;
              character.x++;
            }
          }
        }
        

        // No run throungh on Box;
        if (key == KEY_ARROW_UP && collision_box && collision_wall_top) {
          character.y++;
        }
        else if (key == KEY_ARROW_DOWN && collision_box && collision_wall_bottom) {
          character.y--;
        }
        else if (key == KEY_ARROW_LEFT && collision_box && collision_wall_left) {
          character.x--;
        }
        else if (key == KEY_ARROW_RIGHT && collision_box && collision_wall_right) {
          character.x++;
        }
      }

      handleBoxesOnTarget(&boxes, &goals);
      checkPuzzleSolution(&gameState);
      
      clear();
      drawMap(&gameState);
      
    }

    drawObject(&character);
    drawBoxes(&boxes);
    printf("\n\n");
    switch (key){
      default: {
        printf("\nTecla:: %d", key);
        break;
      }
      case KEY_ARROW_UP: {
        printf("\nTecla: ↑ : %d", key);
        break;
      }
      case KEY_ARROW_DOWN: {
        printf("\nTecla: ↓ : %d", key);
        break;
      }
      case KEY_ARROW_RIGHT: {
        printf("\nTecla: → : %d", key);
        break;
      }
      case KEY_ARROW_LEFT: {
        printf("\nTecla: ← : %d", key);
        break;
      }

    }

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

