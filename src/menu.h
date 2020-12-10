#ifndef __MENU_SOKOBAN_H__
#define __MENU_SOKOBAN_H__

void howToPlay();

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



void drawMenu(Screen screen, Cursor *cursor, int *option) {

  int padding  = 1;
  int height   = 2;
  bool isContinue = thereIsSavestate("savestate/");
  
  const char* line = "==================================================";
  const char* banner = "\
    ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄   ▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄ ▄▄    ▄ \r\n\
   █       █       █   █ █ █       █  ▄    █      █  █  █ █\r\n\
   █  ▄▄▄▄▄█   ▄   █   █▄█ █   ▄   █ █▄█   █  ▄   █   █▄█ █\r\n\
   █ █▄▄▄▄▄█  █ █  █      ▄█  █ █  █       █ █▄█  █       █\r\n\
   █▄▄▄▄▄  █  █▄█  █     █▄█  █▄█  █  ▄   ██      █  ▄    █\r\n\
    ▄▄▄▄▄█ █       █    ▄  █       █ █▄█   █  ▄   █ █ █   █\r\n\
   █▄▄▄▄▄▄▄█▄▄▄▄▄▄▄█▄▄▄█ █▄█▄▄▄▄▄▄▄█▄▄▄▄▄▄▄█▄█ █▄▄█▄█  █▄▄█\r\n\
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

#endif // __MENU_SOKOBAN_H__
