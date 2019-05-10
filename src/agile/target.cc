/*****************************************************\
* Copyright (c) 2019 The Agile Authors. All rights reserved.
  Use of this source code is governed by a BSD-style license that can be
  found in the LICENSE file.

* Author:         dzlua - https://github.com/dzlua/
* Email:          505544956@qq.com
* FileName:       target.cc
* Create Time:    2019/05/10 14:49:34
* Description:    /
\****************************************************/
#include "target.h"
#include "base.h"

namespace agile {
  Target::Target() {
    name_ = std::to_string((size_t)this);
  }
  Target::~Target() {}

  std::unique_ptr<Target> Target::instance() {
    return std::unique_ptr<Target>(new Target);
  }

  void Target::set_name(const char *name) {
    if (name) 
      name_ = name;
  }
  const char* Target::get_name() const {
    return name_.c_str();
  }

  void Target::set_rect(float x, float y, float w, float h) {
    rect_.set(x, y, w, h);
  }
  Rect Target::get_rect() const {
    return rect_;
  }
} // namespace agile