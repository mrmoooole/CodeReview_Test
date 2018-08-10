// Copyright 2018 Hanpil Kang

#ifndef _GETCH_H_
#define _GETCH_H_

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)&&!defined(__CYGWIN__)
#include "getch_windows.h"
#else
#include "getch_linux.h"
#endif

#endif  // _GETCH_H_
