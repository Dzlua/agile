/*****************************************************\
* Copyright (c) 2019 The Agile Authors. All rights reserved.
  Use of this source code is governed by a BSD-style license that can be
  found in the LICENSE file.

* Author:         dzlua - https://github.com/dzlua/
* Email:          505544956@qq.com
* FileName:       base.cc
* Create Time:    2019/05/10 14:49:41
* Description:    /
\****************************************************/
#include "base.h"
#include "target.h"

#include <vector>

namespace {
  std::vector<std::unique_ptr<agile::Target>> targets_;
}

namespace agile {
  Rect::Rect()
    : x_(0.f), y_(0.f), w_(0.f), h_(0.f) {}
  Rect::Rect(float x, float y, float w, float h)
    : x_(x), y_(y), w_(w), h_(h) {}
  Rect::~Rect() {}

  void Rect::set(float x, float y, float w, float h) {
    x_ = x; y_ = y; w_ = w; h_ = h; 
  }

  float Rect::x() const { return x_; }
  float Rect::y() const { return y_; }
  float Rect::w() const { return w_; }
  float Rect::h() const { return h_; }

  Target* get_target(const char *name) {
    if (!name) return nullptr;
    for (auto &t : targets_) {
      if (strcmp(t->get_name(), name) == 0)
        return t.get();
    }
    return nullptr;
  }
  Target* target_at(size_t idx) {
    return targets_.at(idx).get();
  }
  bool add_target(std::unique_ptr<Target>& target) {
    if (get_target(target->get_name()))
      return false;
    targets_.push_back(std::move(target));
    return true;
  }
  void remove_target(const char *name) {
    if (!name) return;
    for (auto it = targets_.begin(); it != targets_.end(); ++it) {
      if (strcmp((*it)->get_name(), name) == 0) {
        targets_.erase(it);
        break;
      }
    }
  }
  void remove_target(Target *target) {
    if (!target) return;
    for (auto it = targets_.begin(); it != targets_.end(); ++it) {
      if ((*it).get() == target) {
        targets_.erase(it);
        break;
      }
    }
  }
  size_t target_count() {
    return targets_.size();
  }
}  // namespace agile