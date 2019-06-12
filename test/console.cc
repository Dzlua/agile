/*****************************************************\
* Copyright (c) 2019 The Agile Authors. All rights reserved.
  Use of this source code is governed by a BSD-style license that can be
  found in the LICENSE file.

* Author:         dzlua - https://github.com/dzlua/
* Email:          505544956@qq.com
* FileName:       console.cc
* Create Time:    2019/06/12 11:20:35
* Description:    /
\****************************************************/
#include <agile/console.hpp>

void test_console() {
  agile::console::print("first {green:green} print");
  agile::console::print("second {red:red} print");
  agile::console::printf("third {blue:blue} printf");
  agile::console::print("");
  agile::console::print("this {red:is} a {green:color} {blue:text}!");
}

int main(int argc, char **argv) {
    test_console();
    return 0;
}