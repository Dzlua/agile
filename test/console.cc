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
#include <thread>

void test_console() {
  agile::console::print("----- test console -----");
  agile::console::print("first {green:green} print");
  agile::console::print("second {red:red} print");
  agile::console::printf("third {blue:blue} printf");
  agile::console::print("");
  agile::console::print("this {red:is} a {green:color} {blue:text}!");
}

void test_thread() {
  agile::console::print("----- test thread -----");
  auto fun = [] (int id) {
    for (int i = 0; i < 10; ++i) {
      agile::console::print("thread {blue:%d} is running...", id);
      std::this_thread::sleep_for(std::chrono::microseconds(10));
    }
    agile::console::print("thread {blue:%d} is ended.", id);
  };

  std::thread td1(fun, 1);
  std::thread td2(fun, 2);
  td1.join();
  td2.join();
}

int main(int argc, char **argv) {
    test_console();
    test_thread();
    return 0;
}