/*****************************************************\
* Copyright (c) 2019 The Agile Authors. All rights reserved.
  Use of this source code is governed by a BSD-style license that can be
  found in the LICENSE file.

* Author:         dzlua - https://github.com/dzlua/
* Email:          505544956@qq.com
* FileName:       base.h
* Create Time:    2019/05/10 14:32:22
* Description:    /
\****************************************************/
#ifndef __AGILE_BASH_H_
#define __AGILE_BASH_H_

#include "export.h"

#include <memory>
#include <string>

namespace agile {
  class Target;

  class AGILE_API Rect {
  public:
    Rect();
    Rect(float x, float y, float w, float h);
    ~Rect();
  public:
    void set(float x, float y, float w, float h);
    float x() const;
    float y() const;
    float w() const;
    float h() const;
  private:
    float x_, y_, w_, h_;
  };

  AGILE_API Target* get_target(const char *name);
  AGILE_API Target* target_at(size_t idx);
  AGILE_API bool add_target(std::unique_ptr<Target> &target);
  AGILE_API void remove_target(const char *name);
  AGILE_API void remove_target(Target *target);
  AGILE_API size_t target_count();
} // namespace agile

#endif // __AGILE_BASH_H_