#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__


#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

static struct termios initial_settings, handle_input;
static int peek_character = -1;

enum Keys {
  CTRL_C          = 3,
  KEY_ESC         = 27,
  KEY_ENTER       = 13,
  KEY_ARROW_UP    = 65,
  KEY_ARROW_DOWN  = 66,
  KEY_ARROW_LEFT  = 68,
  KEY_ARROW_RIGHT = 67,
  KEY_R_U         = 82,  // KEY R UPPERCASE
  KEY_H_U         = 72,  // KEY H UPPERCASE
  KEY_H_L         = 104, // KEY H UPPERCASE
  KEY_R_L         = 114  // KEY R LOWERCASE
};

void init_keyboard()
{
  tcgetattr(0, &initial_settings);
}

void close_keyboard()
{
  tcsetattr(0, TCSANOW, &initial_settings);
}

int kbhit()
{
  unsigned char ch;
  int nread;

  if (peek_character != -1) return 1;
  handle_input.c_cc[VMIN]=0;
  tcsetattr(0, TCSANOW, &handle_input);
  nread = read(0,&ch,1);
  handle_input.c_cc[VMIN]=1;
  tcsetattr(0, TCSANOW, &handle_input);
  if(nread == 1)
  {
    peek_character = ch;
    return 1;
  }
  return 0;
}

int readch()
{
  char ch;

  if(peek_character != -1)
  {
    ch = peek_character;
    peek_character = -1;
    return ch;
  }
  
  read(0,&ch,1);
  return ch;
}

#endif //__KEYBOARD_H__