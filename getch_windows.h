// Copyright 2018 Hanpil Kang

#ifndef _GETCH_WINDOWS_H_
#define _GETCH_WINDOWS_H_

#include <conio.h>

const int KEY_UP    = 257;
const int KEY_DOWN  = 258;
const int KEY_LEFT  = 259;
const int KEY_RIGHT = 260;
const int KEY_HOME  = 261;
const int KEY_END   = 262;
const int KEY_DEL   = 127;
const int KEY_DEL2  = 8;

int GetKeyInput() {
  int v = _getch();
  if (v == 224) {
    v = _getch();
    switch (v) {
      case 72: return KEY_UP;
      case 80: return KEY_DOWN;
      case 77: return KEY_RIGHT;
      case 75: return KEY_LEFT;
      case 71: return KEY_HOME;
      case 79: return KEY_END;
	  case KEY_DEL2: return KEY_DEL;
      default: return v;
    }
  }
  return v;
}

#endif  // _GETCH_WINDOWS_H_
