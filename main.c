#include <stdio.h>
#include <stdbool.h>
#include "lib/types.h"
#include "lib/screen.h"
#include "lib/keyboard.h"  
#include <string.h>
#include "game.h"

void menu(Screen, Cursor*, int*);
void howToPlay();
void bannerHowToPlay();



int main() {

	Screen screen =  getScreenSize();
	Cursor cursor = {0, 0};
	Program program = {true};

	int menuOption = 0;
	
	nocursor();
	clear();

	
	menu(screen, &cursor, &menuOption);

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
			menu(screen, &cursor, &menuOption);
		}
		
		gotoxy(cursor.x, cursor.y);
		printf("\033[31;1m>\033[0;0m");
		
	}
	while(program.running);
	
	clear();
	showcursor();
	
	return 0;
}


void menu(Screen screen, Cursor *cursor, int *option) {

	int padding  = 1;
	int height   = 2;
	bool isContinue = false;
	
	const char* line = "==================================================";
	const char* banner = "\
        ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄   ▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄ ▄▄    ▄  \r\n\
       █       █       █   █ █ █  ▄    █      █  █  █ █ \r\n\
       █  ▄▄▄▄▄█   ▄   █   █▄█ █ █▄█   █  ▄   █   █▄█ █ \r\n\
       █ █▄▄▄▄▄█  █ █  █      ▄█       █ █▄█  █       █ \r\n\
       █▄▄▄▄▄  █  █▄█  █     █▄█  ▄   ██      █  ▄    █ \r\n\
        ▄▄▄▄▄█ █       █    ▄  █ █▄█   █  ▄   █ █ █   █ \r\n\
       █▄▄▄▄▄▄▄█▄▄▄▄▄▄▄█▄▄▄█ █▄█▄▄▄▄▄▄▄█▄█ █▄▄█▄█  █▄▄█ \r\n\
	";


	int centerWidth     = screen.centerWidth - strlen(line) / 2;
	int centerHeight    = screen.height / 4;
	int centerSelection = centerWidth + strlen(line) / 2.5;
	int centerBanner    = centerWidth - 6 ;
	int selection       = 0;


	cursor->x = centerSelection - 2;
	
	if(cursor->y <  centerHeight + 11) cursor->y = centerHeight + 15 - ((isContinue)? padding : height);
	if(cursor->y >  centerHeight + 15 - ((isContinue)? padding : height)) cursor->y = centerHeight + 11;

	selection = cursor->y - centerHeight - 10;
	
	textcolor(IRED);

	int h = centerHeight;
	gotoxy(centerBanner, h + 1);
	
	for(int i = 0; i < strlen(banner); i++){
		if(banner[i] == '\n'){
			h++;
			gotoxy(centerBanner, h);
		}

		printf("%c", banner[i]);
	}
	
	reset_video();
	gotoxy(centerWidth,8 + height + centerHeight);  printf("%s", line);

	if(isContinue){
		padding = 0;
		gotoxy(centerSelection, 9 + height + centerHeight);  printf("\033[32;1mC\033[0;0montinue "); 
	}else {
		selection++;
	}

	*option = selection;
	
	gotoxy(centerSelection, 10 - padding + height + centerHeight); printf("\033[32;1mN\033[0;0mew Game ");
	gotoxy(centerSelection, 11 - padding + height + centerHeight); printf("\033[32;1mH\033[0;0mow to play ");
	gotoxy(centerSelection, 12 - padding + height + centerHeight); printf("\033[32;1mE\033[0;0mxit     ");
	gotoxy(centerWidth, 13 - padding + height + centerHeight); printf("%s", line);

}



void howToPlay() {
	
	int key;
	clear();
	drawBannerHowToPlay();
	
	do {
		
		if(kbhit()){
			
			key = readch();
			clear();
		}
		drawBannerHowToPlay();
	}
	while(key != KEY_ENTER);
}
