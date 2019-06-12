/*****************************************************\
* Copyright (c) 2019 The Agile Authors. All rights reserved.
  Use of this source code is governed by a BSD-style license that can be
  found in the LICENSE file.

* Author:         dzlua - https://github.com/dzlua/
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

namespace agile {
namespace test {

enum class __color : unsigned short {
  #ifdef _MSC_VER
    kGreen = 2,
    kRed = 4,
    kDefault = 7,
  #else
    kDefault = 30,
    kRed = 31,
    kGreen = 32,
  #endif
};

struct __print_info {
  int failed;
  int passed;
  float eqf_range;
  const char *test_name;
  int err_counts;
  int pass_counts;
  __print_info();
  ~__print_info();
};

__print_info g_info;

void _set_color(__color color) {
  auto col = static_cast<unsigned short>(color);
  #ifdef _MSC_VER
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), col);
  #else
      printf("/033[1;40;%dm",col);
  #endif
}

static inline void _test_assert(float exp, int tp, const char *file, int line, const char *msg) {
  bool bexp = false;
  if (tp == 0) {
    bexp = exp == 0.f;
  } else if (tp > 0) {
    if (exp < g_info.eqf_range && exp > -g_info.eqf_range)
      bexp = true;
  } else if (tp < 0) {
    if (exp > g_info.eqf_range || exp < -g_info.eqf_range)
      bexp = true;
  }

  if (!bexp) {
    ++g_info.err_counts;
    _set_color(__color::kRed);
    printf("failed: ");
  } else {
    ++g_info.pass_counts;
    _set_color(__color::kGreen);
    printf("passed: ");
  }

  _set_color(__color::kDefault);
  printf("%s in %s:%d\n", msg, file, line);
}

static inline void _set_eqf(float range) {
  if (range < 0.f) {
    g_info.eqf_range = -range;
  } else {
    g_info.eqf_range = range;
  }
}

static void _test_begin(const char *name) {
  g_info.test_name = name;
  g_info.err_counts = 0;
  g_info.pass_counts = 0;
  printf("----- %d -----\n"
    , g_info.passed + g_info.failed + 1);
  printf("Begin %s\n", g_info.test_name);
}
static void _test_end() {
  if (g_info.err_counts == 0) {
    g_info.passed++;
    _set_color(__color::kGreen);
    printf("\nPASSED! ");
  } else {
    g_info.failed++;
    _set_color(__color::kRed);
    printf("\nFAILED! ");
  }

  _set_color(__color::kDefault);
  printf("failed: ");
  _set_color(__color::kRed);
  printf("%d", g_info.err_counts);
  _set_color(__color::kDefault);
  printf(", passed: ");
  _set_color(__color::kGreen);
  printf("%d", g_info.pass_counts);
  _set_color(__color::kDefault);
  printf(", count: %d\n"
    , g_info.err_counts + g_info.pass_counts);
}

__print_info::__print_info()
  : failed(0), passed(0), eqf_range(0.001f)
  , test_name(""), err_counts(0), pass_counts(0) {}
__print_info::~__print_info() {
  printf("\n----- Summary -----\n");
  printf("failed tests: ");
  _set_color(__color::kRed);
  printf("%d", failed);
  _set_color(__color::kDefault);
  printf("\npassed tests: ");
  _set_color(__color::kGreen);
  printf("%d", passed);
  _set_color(__color::kDefault);
  printf("\ntotal  tests: %d\n"
    , failed + passed);

  if (failed == 0) {
    _set_color(__color::kGreen);
    printf("PASSED! ");
  } else {
    _set_color(__color::kRed);
    printf("FAILED! ");
  }

  _set_color(__color::kDefault);
}

#define AG_TEST_BEGIN(name) { agile::test::_test_begin(name); }
#define AG_TEST_END() { agile::test::_test_end(); }
#define AG_TEST_SET_EQf(range) { agile::test::_set_eqf(range); }

#define AG_TEST_EQ(l,r) { agile::test::_test_assert((l) - (r), 0, __FILE__, __LINE__, "AG_TEST_EQ("#l","#r")"); }
#define AG_TEST_NEQ(l,r) { agile::test::_test_assert((l) - (r), 0, __FILE__, __LINE__, "AG_TEST_NEQ("#l","#r")"); }
#define AG_TEST_EQf(l,r) { agile::test::_test_assert((l) - (r), 1, __FILE__, __LINE__, "AG_TEST_EQf("#l","#r")"); }
#define AG_TEST_NEQf(l,r) { agile::test::_test_assert((l) - (r), -1, __FILE__, __LINE__, "AG_TEST_NEQf("#l","#r")"); }

} // end namespace test
} // end namespace agile

#endif // end define AG_TEST_HPP_