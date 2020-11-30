#include <stdio.h>
#include <stdbool.h>
#include "keyboard.h"
#include "screen.h"

typedef struct object {

  int x, y;
  char body;

} Object;

typedef struct box {
  int x, y;
  char body;
  bool enable;
} Box;

typedef struct 
{
  Box *list;
  int lenght;
} Boxs;

typedef struct currentMap {
  char**map;
  int width;
  int height;

} CurrentMap;
typedef struct gameState {
  Boxs *boxs;
  CurrentMap currrentMap;
  Object *character;
  bool gameOver;
} GameState;


void draw(GameState);

int main() {
  
  #define BOX  '#'
  #define WALL '*'
  #define DOLL '@'
  #define GOAL '?'
  #define SIZE 11
  
  Boxs boxs;
  GameState gameState;
  Object character;

  gameState.gameOver = false;
  gameState.currrentMap.width = SIZE;
  gameState.currrentMap.height = SIZE;
  gameState.boxs = &boxs;
  gameState.character = &character;

  boxs.list   = NULL;
  boxs.lenght = 0;
  bool gameOver = false;
  

  char map[SIZE][SIZE] = {
      "          \n",
      "  Level 1 \n",
      "   ***    \n",
      "   *?*    \n",
      "   *#*****\n",
      " ***# # ?*\n",
      " *? #@****\n",
      " ****#*   \n",
      "    *?*   \n",
      "    ***   \n",
      "          \n",
  };
  

  init_keyboard();
  nocursor();

  enum Keys {
    CTRL_C = 3,
    KEY_UP = 65,
    KEY_DOWN = 66,
    KEY_LEFT = 67,
    KEY_RIGHT = 68,
  };


  for (int i = 0; i < SIZE; i++) 
    for (int j = 0; j < SIZE; j++) {
      if (map[i][j] == DOLL)
      {
        character.x = j + 1;
        character.y = i + 1;
        map[i][j] = ' ';
        break;
      }
    }

  for (int i = 0; i < SIZE; i++) 
    for (int j = 0; j < SIZE; j++) {
      if(map[i][j] == BOX) {
        boxs.lenght++;
      }
    }

  boxs.list = (Box*) calloc(boxs.lenght, sizeof(Box));


  for(int i = 0; i < boxs.lenght; i++) {
    boxs.list[i].body = BOX;
    boxs.list[i].enable = false;
  }

  int index = 0;
  for (int i = 0; i < SIZE; i++) 
    for (int j = 0; j < SIZE; j++) {
      if(map[i][j] == BOX) {
        boxs.list[index].x = j + 1;
        boxs.list[index].y = i + 1;
        index++;
        map[i][j] = ' ';
      }
    }
   // COPY MAP START
  gameState.currrentMap.map = (char**) calloc(SIZE, sizeof(char*));
  
  for(int i = 0; i < SIZE; i++){
    gameState.currrentMap.map[i] = (char*) calloc(SIZE, sizeof(char));
  }
  
  for (int i = 0; i < SIZE; i++) 
    for (int j = 0; j < SIZE; j++) {
      gameState.currrentMap.map[i][j] = map[i][j];
    }
  // COPY MAP END  

  character.body = DOLL;


  clear();

  draw(gameState);
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

      collision_wall_right = map[character.y - 1][character.x - 2] == WALL;
      collision_wall_top = map[character.y - 2][character.x - 1]   == WALL;
      collision_wall_bottom = map[character.y][character.x - 1]    == WALL;
      collision_wall_left = map[character.y - 1][character.x]      == WALL;

      for(int i = 0; i < boxs.lenght; i++) {
        
        bool collision_box = boxs.list[i].x == character.x && boxs.list[i].y == character.y;

        if (key == KEY_UP && collision_box && !collision_wall_top) {
          Box bk = boxs.list[i];
          boxs.list[i].y--;
          
          for(int j = 0; j < boxs.lenght; j++)
            if(boxs.list[i].x == boxs.list[j].x && boxs.list[i].y == boxs.list[j].y) {
              boxs.list[i] = bk;
              
            }
        }
        else if (key == KEY_DOWN && collision_box && !collision_wall_bottom) {
          boxs.list[i].y++;
        }
        else if (key == KEY_LEFT && collision_box && !collision_wall_left) {
          boxs.list[i].x++;
        }
        else if (key == KEY_RIGHT && collision_box && !collision_wall_right) {
          boxs.list[i].x--;
        }


        // No run throungh on Box;
        if (key == KEY_UP && collision_box && collision_wall_top ) {
          character.y++;
        }
        else if (key == KEY_DOWN && collision_box && collision_wall_bottom ) {
          character.y--;
        }
        else if (key == KEY_LEFT && collision_box && collision_wall_left) {
          character.x--;
        }
        else if (key == KEY_RIGHT && collision_box && collision_wall_right) {
          character.x++;
        }
      }

      for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
          if(map[i][j] == GOAL) {
            

            for(int z = 0; z < boxs.lenght; z++) {
              if(boxs.list[z].y == i + 1 && boxs.list[z].x == j + 1) {
                boxs.list[z].enable = true;
              }
            }
          }
        }
      
      int complete = 0;
      for(int i = 0; i < boxs.lenght; i++ ) {
        if(boxs.list[i].enable) {
          complete++;
        }
      }

      if(complete == boxs.lenght){
        gameState.gameOver = true;
      }

      clear();


      // DRAW MAP
      draw(gameState);

      
    }

    printf("\x1b[33;1m");
    printf("%c", character.body);
    gotoxy(character.x, character.y);
    // DRAW BOX

    for(int i = 0; i < boxs.lenght; i++) {
      gotoxy(boxs.list[i].x, boxs.list[i].y);
      if(boxs.list[i].enable) {
        printf("\x1b[37;42;1m");
      }
      else {
        printf("\x1b[41;1m");
      }
      printf("%c", boxs.list[i].body);
      printf("\x1b[0m");
      
    }

    gotoxy(character.x, character.y);

  } while (!gameState.gameOver);

  close_keyboard();
  clear();

  return 0;
}


void draw(GameState gameState) {

  for(int i = 0; i < gameState.currrentMap.height; i++)
    for(int j = 0; j < gameState.currrentMap.width; j++) {
   
      if (gameState.currrentMap.map[i][j] == GOAL) {
        printf("\x1b[32;1m");
        printf("%c", gameState.currrentMap.map[i][j]);
        printf("\x1b[0m");
      }
      // DRAW WALL
      else if (gameState.currrentMap.map[i][j] == WALL) {
        printf("\x1b[46m");
        printf("%c", gameState.currrentMap.map[i][j]);
        printf("\x1b[0m");
      }
      // DRAW ANY
      else {
        printf("%c", gameState.currrentMap.map[i][j]);
      }
    }

    gotoxy(gameState.character->x, gameState.character->y);
}