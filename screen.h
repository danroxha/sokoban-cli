#ifndef __SCREEN_H__
#define __SCREEN_H__


void nocursor()
{
  printf("\x1b[?25l");
}


void gotoxy(unsigned int x, unsigned int y)
{
  printf("\x1b[%d;%df", y, x);
}

void clear()
{
  printf("\x1b[H\x1b[J"); 
}

#endif // __SCREEN_H__