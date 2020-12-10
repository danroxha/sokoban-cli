#include <stdio.h>
#include <stdbool.h>
#include "lib/types.h"
#include "lib/screen.h"
#include "src/game.h"
#include "src/menu.h"


int main() {

	Screen screen =  getScreenSize();
	Cursor cursor = {0, 0};
	Program program = {true};

	int menuOption = 0;
	
	nocursor();
	clear();

	
	drawMenu(screen, &cursor, &menuOption);

	do {
	  
	  screen =  getScreenSize();
		
		if(kbhit()) {

			int key = readch();

			if(key == CTRL_C)
				break;

			if(key == KEY_ARROW_UP) cursor.y--;
			if(key == KEY_ARROW_DOWN) cursor.y++;
			if(key == KEY_ENTER) {
				switch(menuOption){
					case MENU_CONTINUE: {
						game();
						break;
					}
					case MENU_NEW_GAME: {
						removeSaveState("savestate/");
						game();
						break;
					}
					case MENU_HOW_TO_PLAY: {
						howToPlay();
						break;
					}
					case MENU_EXIT: {
						program.running = false;
						break;
					}
				}	
			}
				
			clear();
			drawMenu(screen, &cursor, &menuOption);
		}
		
		gotoxy(cursor.x, cursor.y);
		textcolor(IRED);
		printf(">");
		reset_video();

	}
	while(program.running);
	
	clear();
	showcursor();
	
	return 0;
}

