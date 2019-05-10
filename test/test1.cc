/*****************************************************\
* Copyright (c) 2019 The Agile Authors. All rights reserved.
  Use of this source code is governed by a BSD-style license that can be
  found in the LICENSE file.

* Author:         dzlua - https://github.com/dzlua/
* Email:          505544956@qq.com
* FileName:       test1.cc
* Create Time:    2019/05/10 15:30:06
* Description:    /
\****************************************************/
#include <agile/agile.h>

#include <iostream>
using namespace std;

void show_target_info() {
  auto show_one = [](agile::Target *target) {
    if (!target) return;
    auto rc = target->get_rect();
    cout << "target name:" << target->get_name()
      << " pos: (" << rc.x() << "," << rc.y() << "),"
      << "size: (" << rc.w() << "," << rc.h() << ")"
      << endl;
  };
  
  cout << "target count: " << agile::target_count() << endl;
  for (size_t i = 0; i < agile::target_count(); ++i) {
    auto target = agile::target_at(i);
    show_one(target);
  }
}

int main(int argc, char ** argv) {
  {
    auto target1 = agile::Target::instance();
    target1->set_name("target1");
    target1->set_rect(0.f, 0.f, 100.f, 100.f);
    agile::add_target(target1);

    auto target2 = agile::Target::instance();
    target2->set_rect(10.f, 10.f, 10.f, 10.f);
    agile::add_target(target2);
  }

  show_target_info();
  
  cout << "remove target1" << endl;
  agile::remove_target("target1");

  show_target_info();
  return 0;
}