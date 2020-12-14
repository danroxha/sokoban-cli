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



void drawMenu(Cursor *cursor, int *option) {

  Screen screen = getScreenSize();
  const char* banner[] =  {
   "\033[31;1m",
   " ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄   ▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄ ▄▄    ▄ ",
   "█       █       █   █ █ █       █  ▄    █      █  █  █ █",
   "█  ▄▄▄▄▄█   ▄   █   █▄█ █   ▄   █ █▄█   █  ▄   █   █▄█ █",
   "█ █▄▄▄▄▄█  █ █  █      ▄█  █ █  █       █ █▄█  █       █",
   "█▄▄▄▄▄  █  █▄█  █     █▄█  █▄█  █  ▄   ██      █  ▄    █",
   " ▄▄▄▄▄█ █       █    ▄  █       █ █▄█   █  ▄   █ █ █   █",
   "█▄▄▄▄▄▄▄█▄▄▄▄▄▄▄█▄▄▄█ █▄█▄▄▄▄▄▄▄█▄▄▄▄▄▄▄█▄█ █▄▄█▄█  █▄▄█",
   "\033[0;0m",
   "                                                        ",
   "                       \033[32;1mC\033[0;0montinue      ",
   "                       \033[32;1mN\033[0;0mew Game      ",
   "                       \033[32;1mH\033[0;0mow to play   ",
   "                       \033[32;1mE\033[0;0mxit          ",
  };


  enum BannerLine {
    LINE_NINE     = 9,
    LINE_TEN      = 10,
    LINE_THIRTEEN = 13,
  };

  bool isContinue  = thereIsSavestate("savestate/");
  int centerWidth  = screen.centerWidth - strlen(banner[LINE_NINE]) / 2;
  int centerHeight = screen.height / 4;
  int centerBanner = centerWidth;
  int selection    = 0;


  cursor->x = centerWidth + strlen(banner[LINE_NINE]) / 2.6;
  if(cursor->y <  centerHeight + LINE_TEN)
    cursor->y = centerHeight + LINE_THIRTEEN - (int) !isContinue;
  if(cursor->y > centerHeight + LINE_THIRTEEN - (int) !isContinue)
    cursor->y = centerHeight + LINE_TEN;

  selection = cursor->y - centerHeight - LINE_NINE + (int)!isContinue;
  
  int hidenOption = 0;
  int size = sizeof(banner) / sizeof(char*);
  for(int i = 0; i < size; i++) {
    if(!isContinue && i == LINE_TEN) {
      hidenOption = 1;
      continue;
    }

    gotoxy(centerBanner, centerHeight + i - hidenOption); 
    printf("%s", banner[i]);
  }
 
  *option = selection;
}

#endif // __MENU_SOKOBAN_H__
