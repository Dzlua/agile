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
  agile::console::log("----- test thread -----");
  auto fun = [] (int id) {
    for (int i = 0; i < 10; ++i) {
      agile::console::print("thread {blue:%d} is running...", id);
      agile::console::log("thread %d is running...", id);
      std::this_thread::sleep_for(std::chrono::microseconds(10));
    }
    agile::console::print("thread {blue:%d} is ended.", id);
    agile::console::log("thread %d is ended.", id);
  };

  std::thread td1(fun, 1);
  std::thread td2(fun, 2);
  td1.join();
  td2.join();
}

void test_log() {
  agile::console::print("----- test log -----");

  const char *msg = "hello";
  agile::console::print(msg);
  agile::console::log(msg);

  msg = "this is a %s %d";
  agile::console::print(msg, "test", 1);
  agile::console::log(msg, "test", 1);

  msg = "this is a %s %d";
  agile::console::print(msg, "ok", 2);
  agile::console::log(msg, "ok", 2);
}

int main(int argc, char **argv) {
  agile::console::print(argv[0]);
    test_console();
    test_thread();
    test_log();
    return 0;
}