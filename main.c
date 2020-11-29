#include <stdio.h>
#include <stdbool.h>
#include "keyboard.h"
#include "screen.h"

typedef struct object {
	
	int x, y;
	char body;
	
} Object;



#define BOX  '#'
#define WALL '*'
#define DOLL '@'
#define GOAL '?'



int main() {
	
	#define SIZE 11

  char map[SIZE][SIZE] = {
    "          \n",
    "  Level 1 \n",
    "   ***    \n",
    "   *?*    \n",
    "   * *****\n",
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
		CTRL_C    =  3,
		KEY_UP    = 65,
		KEY_DOWN  = 66,
	  KEY_LEFT  = 67,
		KEY_RIGHT = 68,
	};


  Object character;


	for(int i = 0; i < SIZE; i++) {
		for(int j = 0; j < SIZE; j++)
			if(map[i][j] == DOLL) {
				character.x = j + 1;
				character.y = i + 1;
				map[i][j] = ' ';
				break;
			}
	}
  
  character.body = DOLL;

  
  
	clear();

	for(int i = 0; i < SIZE; i++)
		for(int j = 0; j < SIZE; j++) {
			printf("%c", map[i][j]);
	}



	gotoxy(character.x, character.y);

  do {  

  	if(kbhit()) {

      int key = readch();
			if(key == CTRL_C) break;


			bool collision_wall_top    =  map[character.y - 2][character.x - 1] == WALL;
			bool collision_wall_bottom =  map[character.y]    [character.x - 1] == WALL;
			bool collision_wall_letf   =  map[character.y - 1][character.x]     == WALL;
			bool collision_wall_right	 =  map[character.y - 1][character.x - 2] == WALL;

			 
  		if(key == KEY_UP && !collision_wall_top ) character.y--;
  		else if(key == KEY_DOWN && !collision_wall_bottom) character.y++;
  		else if(key == KEY_LEFT && !collision_wall_letf)   character.x++;
  		else if(key == KEY_RIGHT && !collision_wall_right) character.x--;


			collision_wall_right	=  map[character.y - 1][character.x - 2] == WALL;
			collision_wall_top    =  map[character.y - 2][character.x - 1] == WALL;
			collision_wall_bottom =  map[character.y]    [character.x - 1] == WALL;
			collision_wall_letf   =  map[character.y - 1][character.x]     == WALL;


			bool collision_box = map[character.y - 1][character.x - 1] == BOX;    
      
			if(key == KEY_UP && collision_box && !collision_wall_top )
			{
				map[character.y - 2][character.x - 1] = map[character.y - 1][character.x - 1];
				map[character.y - 1][character.x - 1] = ' ';
			}
			else if(key == KEY_DOWN && collision_box && !collision_wall_bottom)
			{
				map[character.y]    [character.x - 1] = map[character.y - 1][character.x - 1];
				map[character.y - 1][character.x - 1] = ' ';
			}
			else if(key == KEY_LEFT &&  collision_box && !collision_wall_letf)
			{
				map[character.y - 1][character.x] = map[character.y - 1][character.x - 1];
				map[character.y - 1][character.x - 1] = ' ';
			}
			else if(key == KEY_RIGHT && collision_box && !collision_wall_right) 
			{
				map[character.y - 1][character.x - 2] = map[character.y - 1][character.x - 1];
				map[character.y - 1][character.x - 1] = ' ';
			}
	
			clear();

			// DRAW
			for(int i = 0; i < SIZE; i++)
				for(int j = 0; j < SIZE; j++) {
					if( map[i][j] == BOX) {
						printf("\x1b[41;1m");
						printf("%c", map[i][j]);
						printf("\x1b[0m");
					}
					else if(map[i][j] == GOAL)
					{
						printf("\x1b[32;1m");
						printf("%c", map[i][j]);
						printf("\x1b[0m");
					}
					else if(map[i][j] == WALL)
					{
						printf("\x1b[46m");
						printf("%c", map[i][j]);
						printf("\x1b[0m");
					}
					else {
						// printf("\x1b[47;1m");
						printf("%c", map[i][j]);
						// printf("\x1b[0m");
					}
				}
						
			gotoxy(character.x, character.y);
  	}
  	
		printf("\x1b[33;1m");
    printf("%c", character.body);
		gotoxy(character.x, character.y);


		
	} while(true);

  close_keyboard();
  clear();

	return 0;
}



