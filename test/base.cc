/*****************************************************\
* Copyright (c) 2019 The Agile Authors. All rights reserved.
  Use of this source code is governed by a BSD-style license that can be
  found in the LICENSE file.

* Author:         dzlua - https://gitee.com/dzlua/
* Email:          505544956@qq.com
* FileName:       base.cc
* Create Time:    2019/06/11 15:02:03
* Description:    /
\****************************************************/
#include <agile/base.hpp>
#include "test.h"

void test_radian_degrees() {
  ag_test_begin("radian_degrees");

  AG_TEST_EQf(0.f, agile::base::to_radian(0));
  AG_TEST_EQf(0.7853982f, agile::base::to_radian(45));
  AG_TEST_EQf(1.5707964f, agile::base::to_radian(90));
  AG_TEST_EQf(2.3561946f, agile::base::to_radian(135));
  AG_TEST_EQf(3.1415926f, agile::base::to_radian(180));
  AG_TEST_EQf(3.9269909f, agile::base::to_radian(225));
  AG_TEST_EQf(4.7123891f, agile::base::to_radian(270));
  AG_TEST_EQf(5.4977873f, agile::base::to_radian(315));
  AG_TEST_EQf(6.2831855f, agile::base::to_radian(360));

  AG_TEST_EQf(0, agile::base::to_degrees(0.f));
  AG_TEST_EQf(45, agile::base::to_degrees(0.7853982f));
  AG_TEST_EQf(90, agile::base::to_degrees(1.5707964f));
  AG_TEST_EQf(135, agile::base::to_degrees(2.3561946f));
  AG_TEST_EQf(180, agile::base::to_degrees(3.1415926f));
  AG_TEST_EQf(225, agile::base::to_degrees(3.9269909f));
  AG_TEST_EQf(270, agile::base::to_degrees(4.7123891f));
  AG_TEST_EQf(315, agile::base::to_degrees(5.4977873f));
  AG_TEST_EQf(360, agile::base::to_degrees(6.2831855f));

  ag_test_end();
}

void test() {
  ag_test_begin("test");
  AG_TEST_EQ(-1, 1);
  ag_test_end();
}

int main(int argc, char **argv) {
  test_radian_degrees();
  test();
  return 0;
}