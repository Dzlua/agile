/*****************************************************\
* Copyright (c) 2019 The Agile Authors. All rights reserved.
  Use of this source code is governed by a BSD-style license that can be
  found in the LICENSE file.

* Author:         dzlua - https://gitee.com/dzlua/
* Email:          505544956@qq.com
* FileName:       test.hpp
* Create Time:    2019/06/11 15:18:49
* Description:    /
\****************************************************/
#ifndef AG_TEST_HPP_
#define AG_TEST_HPP_

#include <stdlib.h>
#include <stdio.h>

#ifdef _MSC_VER
#include <windows.h>
#endif

struct __print_total_info {
  int failed;
  int passed;
  __print_total_info();
  ~__print_total_info();
};

static float g_eqf_range = 0.01f;
static const char *g_test_name = "";
static int g_err_counts = 0;
static int g_pass_counts = 0;

__print_total_info g_total_info;

void _set_color(unsigned short color) {
  #ifdef _MSC_VER
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
  #else
      printf("/033[1;40;%dm",color);
  #endif
}
void _color_red() {
  #ifdef _MSC_VER
    _set_color(4);
  #else
    _set_color(31);
  #endif
}
void _color_green() {
  #ifdef _MSC_VER
    _set_color(2);
  #else
    _set_color(32);
  #endif
}
void _color_default() {
  #ifdef _MSC_VER
    _set_color(7);
  #else
    _set_color(30;
  #endif
}

static inline void _test_assert(float exp, int tp, const char *file, int line, const char *msg) {
  bool bexp = false;
  if (tp == 0) {
    bexp = exp == 0.f;
  } else if (tp > 0) {
    if (exp < g_eqf_range && exp > -g_eqf_range)
      bexp = true;
  } else if (tp < 0) {
    if (exp > g_eqf_range || exp < -g_eqf_range)
      bexp = true;
  }

  if (!bexp) {
    ++g_err_counts;
    _color_red();
    printf("failed: ");
  } else {
    ++g_pass_counts;
    _color_green();
    printf("passed: ");
  }

  _color_default();
  printf("%s in %s:%d\n", msg, file, line);
}

static inline void _set_eqf(float range) {
  if (range < 0.f) {
    g_eqf_range = -range;
  } else {
    g_eqf_range = range;
  }
}

static void _test_begin(const char *name) {
  g_test_name = name;
  g_err_counts = 0;
  g_pass_counts = 0;
  printf("----- %d -----\n"
    , g_total_info.passed + g_total_info.failed + 1);
  printf("Begin %s\n", g_test_name);
}
static void _test_end() {
  if (g_err_counts == 0) {
    g_total_info.passed++;
    _color_green();
    printf("\nPASSED! ");
  } else {
    g_total_info.failed++;
    _color_red();
    printf("\nFAILED! ");
  }

  _color_default();
  printf("failed: %d, passed: %d, count: %d\n"
    , g_err_counts, g_pass_counts
    , g_err_counts + g_pass_counts);
}

__print_total_info::__print_total_info() : failed(0), passed(0) {}
__print_total_info::~__print_total_info() {
  printf("\n----- Summary -----\n");
  printf("failed tests: %d\npassed tests: %d\ntotal  tests: %d\n"
    , failed, passed
    , failed + passed);

  if (failed == 0) {
    _color_green();
    printf("PASSED! ");
  } else {
    _color_red();
    printf("FAILED! ");
  }

  _color_default();
}

#define AG_TEST_BEGIN(name) { _test_begin(name); }
#define AG_TEST_END() { _test_end(); }
#define AG_TEST_SET_EQf(range) { _set_eqf(range); }

#define AG_TEST_EQ(l,r) { _test_assert((l) - (r), 0, __FILE__, __LINE__, "AG_TEST_EQ("#l","#r")"); }
#define AG_TEST_NEQ(l,r) { _test_assert((l) - (r), 0, __FILE__, __LINE__, "AG_TEST_NEQ("#l","#r")"); }
#define AG_TEST_EQf(l,r) { _test_assert((l) - (r), 1, __FILE__, __LINE__, "AG_TEST_EQ("#l","#r")"); }
#define AG_TEST_NEQf(l,r) { _test_assert((l) - (r), -1, __FILE__, __LINE__, "AG_TEST_NEQ("#l","#r")"); }

#endif // end define AG_TEST_HPP_