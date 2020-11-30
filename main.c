#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "keyboard.h"
#include "screen.h"
#include "types.h"


void drawMap(GameState*);
void drawBoxes(Boxes*);
void drawObject(Object*);
bool checkCollisionBetweenBoxes(Boxes*);
void checkPuzzleSolution(GameState*);
void handleBoxesOnTarget(Boxes*, Goals*);
void configCharacter(Object*, GameState*);
void configBoxes(Boxes*, GameState*);
void configGoals(Goals*, GameState*);
void configGameState(GameState*);


int main() {
  
  srand(time(0));

  #define SIZE 11
  
  Boxes boxes;
  Goals goals;
  GameState gameState;
  Object character;
  


  gameState.currrentMap.width = SIZE;
  gameState.currrentMap.height = SIZE;
  gameState.boxes = &boxes;
  gameState.character = &character;

 

  char map[SIZE][SIZE] = {
      "          \n",
      "  Level 1 \n",
      "   ****   \n",
      "   *  *   \n",
      "   *? ****\n",
      " ***# # ?*\n",
      " *?# @****\n",
      " ****#*   \n",
      "    *?*   \n",
      "    ***   \n",
      "          \n",
  };
  

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


  do {

    if (kbhit()) {

      int key = readch();
      if (key == CTRL_C)
        break;

      bool collision_wall_top = map[character.y - 2][character.x - 1]    == WALL;
      bool collision_wall_bottom = map[character.y][character.x - 1]     == WALL;
      bool collision_wall_left = map[character.y - 1][character.x]       == WALL;
      bool collision_wall_right = map[character.y - 1][character.x - 2]  == WALL;

      if (key == KEY_UP && !collision_wall_top)
        character.y--;
      else if (key == KEY_DOWN && !collision_wall_bottom)
        character.y++;
      else if (key == KEY_LEFT && !collision_wall_left)
        character.x++;
      else if (key == KEY_RIGHT && !collision_wall_right)
        character.x--;


      collision_wall_right  = map[character.y - 1][character.x - 2] == WALL;
      collision_wall_top    = map[character.y - 2][character.x - 1] == WALL;
      collision_wall_bottom = map[character.y][character.x - 1]     == WALL;
      collision_wall_left   = map[character.y - 1][character.x]     == WALL;


      for(int i = 0; i < boxes.lenght; i++) {
        
        bool collision_box = boxes.list[i].x == character.x && boxes.list[i].y == character.y;

        if (key == KEY_UP && collision_box && !collision_wall_top) {
          boxes.list[i].y--;
        }
        else if (key == KEY_DOWN && collision_box && !collision_wall_bottom) {
          boxes.list[i].y++;
        }
        else if (key == KEY_LEFT && collision_box && !collision_wall_left) {
          boxes.list[i].x++;
        }
        else if (key == KEY_RIGHT && collision_box && !collision_wall_right) {
          boxes.list[i].x--;
        }
        

        // No run throungh on Box;
        if (key == KEY_UP && collision_box && collision_wall_top) {
          character.y++;
        }
        else if (key == KEY_DOWN && collision_box && collision_wall_bottom) {
          character.y--;
        }
        else if (key == KEY_LEFT && collision_box && collision_wall_left) {
          character.x--;
        }
        else if (key == KEY_RIGHT && collision_box && collision_wall_right) {
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


  } while (!gameState.gameOver);

  close_keyboard();
  clear();

  for(int i = 0; i < goals.lenght; i++) {
    //printf("Goals::(%d, %d)\n", goals.list[i].x, goals.list[i].y);
  }

  return 0;
}

void drawBoxes(Boxes *boxes) {
  for(int i = 0; i < boxes->lenght; i++) {
    gotoxy(boxes->list[i].x, boxes->list[i].y);
    if(boxes->list[i].enable) {
      printf("\x1b[37;42;1m");
    }
    else {
      printf("\x1b[41;1m");
    }
    printf("%c", boxes->list[i].body);
    printf("\x1b[0m");
  }
}

void drawMap(GameState *gameState) {

  for(int i = 0; i < gameState->currrentMap.height; i++)
    for(int j = 0; j < gameState->currrentMap.width; j++) {
   
      if (gameState->currrentMap.field[i][j] == TARGET) {
        printf("\x1b[32;1m");
        printf("%c", gameState->currrentMap.field[i][j]);
        printf("\x1b[0m");
      }
      // DRAW WALL
      else if (gameState->currrentMap.field[i][j] == WALL) {
        printf("\x1b[46m");
        printf("%c", gameState->currrentMap.field[i][j]);
        printf("\x1b[0m");
      }
      // DRAW ANY
      else {
        printf("%c", gameState->currrentMap.field[i][j]);
      }
    }

    gotoxy(gameState->character->x, gameState->character->y);
}

void drawObject(Object *object) {
  
  gotoxy(object->x, object->y);
  printf("\x1b[33;1m");
  printf("%c", object->body);

}

bool checkCollisionBetweenBoxes(Boxes *boxes) {
  
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

void checkPuzzleSolution(GameState *gameState) {
  
  int completePuzzle = 0;
  
  for(int i = 0; i < gameState->boxes->lenght; i++) {
    if(gameState->boxes->list[i].enable)
      completePuzzle++;
  }

  gameState->gameOver = completePuzzle == gameState->boxes->lenght;

}

void handleBoxesOnTarget(Boxes *boxes, Goals *goals) {

  for(int i = 0; i < boxes->lenght; i++) {
    
    boxes->list[i].enable = false;

    for(int j = 0; j < goals->lenght; j++) {
      if(boxes->list[i].x == goals->list[j].x && boxes->list[i].y == goals->list[j].y) {
        boxes->list[i].enable = true;
      }
    }
  }
}

void configCharacter(Object *character, GameState *gameState) {
  
  character->body = DOLL;

  for (int y = 0; y < gameState->currrentMap.height; y++) 
    for (int x = 0; x < gameState->currrentMap.width; x++) {
      if (gameState->currrentMap.field[y][x] == DOLL) {
        character->x = x + 1;
        character->y = y + 1;
        gameState->currrentMap.field[y][x] = ' ';
        break;
      }
    }
}

void configBoxes(Boxes *boxes, GameState *gameState) {
  
  boxes->list   = NULL;
  boxes->lenght = 0;

 for (int y = 0; y < gameState->currrentMap.height; y++) 
    for (int x = 0; x < gameState->currrentMap.width; x++) {
      if(gameState->currrentMap.field[y][x] == BOX) {
        boxes->lenght++;
      }
    }

  boxes->list = (Box*) calloc(boxes->lenght, sizeof(Box));

  for(int i = 0; i < boxes->lenght; i++) {
    boxes->list[i].body = BOX;
    boxes->list[i].enable = false;
    boxes->list[i].id = rand();
  }

  int index = 0;

  for (int y = 0; y < gameState->currrentMap.height; y++) 
    for (int x = 0; x < gameState->currrentMap.width; x++) {
      if(gameState->currrentMap.field[y][x] == BOX) {
        boxes->list[index].x = x + 1;
        boxes->list[index].y = y + 1;
        gameState->currrentMap.field[y][x] = ' ';
        index++;
      }
    }
}

void configGoals(Goals *goals, GameState *gameState) {
  
  goals->lenght = 0;
  if(goals->list)
    free(goals->list);

  for(int y = 0; y < gameState->currrentMap.height; y++) {
    for(int x = 0; x < gameState->currrentMap.width; x++) {
      if(gameState->currrentMap.field[y][x] == TARGET) {
        goals->lenght++;
        goals->list = (Object*) realloc(goals->list, goals->lenght * sizeof(Object));
        goals->list[goals->lenght - 1].body = TARGET;
        goals->list[goals->lenght - 1].x = x + 1;
        goals->list[goals->lenght - 1].y = y + 1;
      }
    }
  }
}

void configGameState(GameState *gameState) {
  gameState->gameOver = false;
}