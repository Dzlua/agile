/*****************************************************\
* Copyright (c) 2019 The Agile Authors. All rights reserved.
  Use of this source code is governed by a BSD-style license that can be
  found in the LICENSE file.

* Author:         dzlua - https://github.com/dzlua/
* Email:          505544956@qq.com
* FileName:       console.hpp
* Create Time:    2019/06/12 10:47:19
* Description:    /
\****************************************************/
#ifndef AGILE_CONSOLE_HPP_
#define AGILE_CONSOLE_HPP_

#include "osplatformutil.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#ifdef I_OS_WIN
#include <windows.h>
#endif

namespace agile {
namespace console {
  namespace __detail {
    #ifdef I_OS_WIN
      struct __sinit {
        unsigned short oldattr;
        __sinit() {
          CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
          HANDLE handle = ::GetStdHandle(STD_OUTPUT_HANDLE);
          ::GetConsoleScreenBufferInfo(handle, &csbiInfo);
          oldattr = csbiInfo.wAttributes;
        }
        ~__sinit() {}
        void set_color(unsigned short color) {
          ::SetConsoleTextAttribute(::GetStdHandle(STD_OUTPUT_HANDLE), color | FOREGROUND_INTENSITY);
        }
        void set_color(const char *bkcolor, int bklen, const char *fgcolor, int fglen) {
          unsigned short color = 0;

          if (strncmp("red", fgcolor, fglen) == 0) {
            color |= FOREGROUND_RED;
          } else if (strncmp("green", fgcolor, fglen) == 0) {
            color |= FOREGROUND_GREEN;
          } else if (strncmp("blue", fgcolor, fglen) == 0) {
            color |= FOREGROUND_BLUE;
          }

          set_color(color);
        }
        void rset_color() {
          ::SetConsoleTextAttribute(::GetStdHandle(STD_OUTPUT_HANDLE), oldattr);
        }
      };
    #else
      struct __sinit {
        __sinit() {}
        ~__sinit() {}
        void set_color(unsigned short color) {
          printf("\033[1m\033[%dm",color);
        }
        void set_color(const char *bkcolor, int bklen, const char *fgcolor, int fglen) {
          unsigned short color = 0;

          if (strncmp("red", fgcolor, fglen) == 0) {
            color |= 31;
          } else if (strncmp("green", fgcolor, fglen) == 0) {
            color |= 32;
          } else if (strncmp("blue", fgcolor, fglen) == 0) {
            color |= 34;
          }

          set_color(color);
        }
        void rset_color() {
          printf("\033[0m");
        }
      };
    #endif
    static __sinit sinit_;

    static inline void set_color(const char *bkcolor, int bklen, const char *fgcolor, int fglen) {
      if ( (bkcolor && bklen > 0) || (fgcolor && fglen > 0) )
        sinit_.set_color(bkcolor, bklen, fgcolor, fglen);      
    }
    static inline void set_color_default() {
      sinit_.rset_color();
    }

    void print_color(const char *msg) {
      bool opened = false, colored = false;
      const char *p = msg;
      const char *color = nullptr;
      int len = 0;
      while (*p) {
        if (opened && (*p == '}')) {
          if (*(p + 1) != '}') {
            opened = false;
            ++p;
            set_color_default();
            continue;
          }
        }

        if (!opened && (*p == '{')) {
          if (*(p + 1) != '{') {
            opened = true;
            colored = false;
            ++p;
            color = p;
            continue;
          }
        }

        if (opened && !colored) {
          if (*p == ',') {
            len = p - color;
          } else if (*p == ':') {
            colored = true;
            if (len > 0) {
              set_color(color, len, color + len + 1, p - color - len - 1);
            } else {
              set_color(nullptr, 0, color, p - color);
            }
          }
        } else {
          if (*p == '{' && (*(p+1) == '{')) {
            ++p;
          }
          if (*p == '}' && (*(p+1) == '}')) {
            ++p;
          }
          ::putchar((int)(*p));
        }

        ++p;
      }
    }
    void print(const char *fmt, va_list arg) {
      static char msg[2048];
	    vsnprintf(msg, 2048, fmt, arg);
	    msg[2047] = '\0';
      print_color(msg);
      set_color_default();
    }
  } // end namespace __detail

  /*
    such as:
      agile::console::print("this {red:is} a {green:color} {blue:text}!");
    detail see:
      test/console.cc
  */
  void printf(const char *fmt, ...) {
    va_list arg;
    va_start(arg, fmt);
    __detail::print(fmt, arg);
    va_end(arg);
  }
  void print(const char *fmt, ...) {
    va_list arg;
    va_start(arg, fmt);
    __detail::print(fmt, arg);
    va_end(arg);
    ::printf("\n");
  }
} // end namespace test
} // end namespace console

#endif // end define AGILE_CONSOLE_HPP_