/*****************************************************\
* Copyright (c) 2019 The Agile Authors. All rights reserved.
  Use of this source code is governed by a BSD-style license that can be
  found in the LICENSE file.

* Author:         dzlua - https://gitee.com/dzlua/
* Email:          505544956@qq.com
* FileName:       test.h
* Create Time:    2019/06/11 15:18:49
* Description:    /
\****************************************************/
#ifndef AG_TEST_H_
#define AG_TEST_H_

#include <stdlib.h>
#include <stdio.h>

static float g_eqf_range = 0.01f;
static const char *g_test_name = "";
static int g_err_counts = 0;
static int g_pass_counts = 0;

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
    printf("error: %s in %s:%d\n", msg, file, line);
  } else {
    ++g_pass_counts;
  }
}

static inline void ag_set_eqf(float range) {
  if (range < 0.f) {
    g_eqf_range = -range;
  } else {
    g_eqf_range = range;
  }
}

static void ag_test_begin(const char *name) {
  g_test_name = name;
  g_err_counts = 0;
  g_pass_counts = 0;
  printf("----------\n");
  printf("Begin test %s\n", g_test_name);
}
static void ag_test_end() {
  printf("\nerror: %d, pass: %d\n", g_err_counts, g_pass_counts);
  if (g_err_counts == 0) {
    printf("PASSED!\n");
  } else {
    printf("FAILED!\n");
  }
}

#define AG_TEST_EQ(l,r) { _test_assert((l) - (r), 0, __FILE__, __LINE__, "AG_TEST_EQ("#l","#r")"); }
#define AG_TEST_NEQ(l,r) { _test_assert((l) - (r), 0, __FILE__, __LINE__, "AG_TEST_NEQ("#l","#r")"); }
#define AG_TEST_EQf(l,r) { _test_assert((l) - (r), 1, __FILE__, __LINE__, "AG_TEST_EQ("#l","#r")"); }
#define AG_TEST_NEQf(l,r) { _test_assert((l) - (r), -1, __FILE__, __LINE__, "AG_TEST_NEQ("#l","#r")"); }

#endif // end define AG_TEST_H_