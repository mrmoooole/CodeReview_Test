// Copyright 2018 Hanpil Kang

#ifndef _GETCH_LINUX_H_
#define _GETCH_LINUX_H_

#include <termios.h>
#include <unistd.h>
#include <stdio.h>

const int KEY_UP    = 257;
const int KEY_DOWN  = 258;
const int KEY_LEFT  = 259;
const int KEY_RIGHT = 260;
const int KEY_HOME  = 261;
const int KEY_END   = 262;
const int KEY_DEL   = 127;

int getch(void) {
  struct termios oldattr, newattr;
  int ch;
  tcgetattr(STDIN_FILENO, &oldattr);
  newattr = oldattr;
  newattr.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
  return ch;
}

int GetKeyInput() {
  int v = getch();
  if (v == 27) {
    v = getch();
    if (v != 91) return v;
    v = getch();
    switch (v) {
      case 65: return KEY_UP;
      case 66: return KEY_DOWN;
      case 67: return KEY_RIGHT;
      case 68: return KEY_LEFT;
      case 72: return KEY_HOME;
      case 70: return KEY_END;
      default: return v;
    }
  }
  return v;
}

#endif  // _GETCH_LINUX_H_
