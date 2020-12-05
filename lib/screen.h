#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <err.h> 
#include <fcntl.h>    
#include <unistd.h>   
#include <termios.h>
#include "types.h"

#define BLACK "\x1b[30m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define WHITE "\x1b[37m"

// FG Intense Colors
#define IBLACK "\x1b[30;1m"
#define IRED "\x1b[31;1m"
#define IGREEN "\x1b[32;1m"
#define IYELLOW "\x1b[33;1m"
#define IBLUE "\x1b[34;1m"
#define IMAGENTA "\x1b[35;1m"
#define ICYAN "\x1b[36;1m"
#define IWHITE "\x1b[37;1m"

// BG Colors
#define BGC_BLACK "\x1b[40m"
#define BGC_RED "\x1b[41m"
#define BGC_GREEN "\x1b[42m"
#define BGC_YELLOW "\x1b[43m"
#define BGC_BLUE "\x1b[44m"
#define BGC_MAGENTA "\x1b[45m"
#define BGC_CYAN "\x1b[46m"
#define BGC_WHITE "\x1b[47m"

// BG Intense Colors
#define BGC_IBLACK "\x1b[40;1m"
#define BGC_IRED "\x1b[41;1m"
#define BGC_IGREEN "\x1b[42;1m"
#define BGC_IYELLOW "\x1b[43;1m"
#define BGC_IBLUE "\x1b[44;1m"
#define BGC_IMAGENTA "\x1b[45;1m"
#define BGC_ICYAN "\x1b[46;1m"
#define BGC_IWHITE "\x1b[47;1m"



void nocursor() {
  printf("\x1b[?25l");
}

void showcursor() {
  printf("\x1b[?25h");
}

void gotoxy(unsigned int x, unsigned int y) {
  printf("\x1b[%d;%df", y, x);
}

void clear() {
  printf("\x1b[H\x1b[J"); 
}

void textcolor(char *color) {
  printf("%s", color);
}

void reset_video() {
  printf("\x1b[0m");
}

Screen getScreenSize() {

  struct screen sc;
  struct winsize ws;
  int fd;

  fd = open("/dev/tty", O_RDWR);
  if(fd < 0 || ioctl(fd, TIOCGWINSZ, &ws) < 0) err(8, "/dev/tty");
	
  sc.width  = (int) ws.ws_col;
  sc.height = (int) ws.ws_row;
  sc.centerWidth  = sc.width / 2;
  sc.centerHeight = sc.height / 2;

  close(fd);

  return sc;
}

#endif // __SCREEN_H__