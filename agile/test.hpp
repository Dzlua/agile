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

#include "agile/console.hpp"

namespace agile {
namespace test {

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
    agile::console::print("{red:[Failed]:} %s {red:in %s:%d}"
      , msg, file, line);
  } else {
    ++g_info.pass_counts;
    agile::console::print("{green:[Passed]:} %s {cyan:in} %s{cyan::%d}"
      , msg, file, line);
  }
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
  agile::console::print("----- %d -----"
    , g_info.passed + g_info.failed + 1);
  agile::console::print("Begin %s", g_info.test_name);
}
static void _test_end() {
  if (g_info.err_counts == 0) {
    g_info.passed++;
    agile::console::printf("\n{green:PASSED!} ");
  } else {
    g_info.failed++;
    agile::console::printf("\n{red:FAILED}! ");
  }

  agile::console::print("failed: {red:%d}, passed: {green:%d}, count: {cyan:%d}"
    , g_info.err_counts, g_info.pass_counts
    , g_info.err_counts + g_info.pass_counts);
}

__print_info::__print_info()
  : failed(0), passed(0), eqf_range(0.001f)
  , test_name(""), err_counts(0), pass_counts(0) {
    agile::console::set_default_color("white");
  }
__print_info::~__print_info() {
  agile::console::printf("\n----- Summary -----\n");
  agile::console::print("failed tests: {red:%d}\npassed tests: {green:%d}\ntotal  tests: {cyan:%d}"
    , failed, passed, failed + passed);

  if (failed == 0) {
    agile::console::print("{green:PASSED!}");
  } else {
    agile::console::print("{red:FAILED!}");
  }

  agile::console::rset_default_color();
}

#define AG_TEST_BEGIN(name) { agile::test::_test_begin(name); }
#define AG_TEST_END() { agile::test::_test_end(); }
#define AG_TEST_SET_EQf(range) { agile::test::_set_eqf(range); }

#define AG_TEST_EQ(l,r) { agile::test::_test_assert((l) - (r), 0, __FILE__, __LINE__, "{blue:AG_TEST_EQ}("#l",{cyan:"#r"})"); }
#define AG_TEST_NEQ(l,r) { agile::test::_test_assert((l) - (r), 0, __FILE__, __LINE__, "{blue:AG_TEST_NEQ}("#l",{cyan:"#r"})"); }
#define AG_TEST_EQf(l,r) { agile::test::_test_assert((l) - (r), 1, __FILE__, __LINE__, "{blue:AG_TEST_EQf}("#l",{cyan:"#r"})"); }
#define AG_TEST_NEQf(l,r) { agile::test::_test_assert((l) - (r), -1, __FILE__, __LINE__, "{blue:AG_TEST_NEQf}("#l",{cyan:"#r"})"); }

} // end namespace test
} // end namespace agile

#endif // end define AG_TEST_HPP_