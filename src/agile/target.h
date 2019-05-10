/*****************************************************\
* Copyright (c) 2019 The Agile Authors. All rights reserved.
  Use of this source code is governed by a BSD-style license that can be
  found in the LICENSE file.

* Author:         dzlua - https://github.com/dzlua/
* Email:          505544956@qq.com
* FileName:       target.h
* Create Time:    2019/05/10 14:35:31
* Description:    /
\****************************************************/
#ifndef __AGILE_TARGET_H_
#define __AGILE_TARGET_H_

#include "base.h"

namespace agile {
  class AGILE_API Target {
  private:
    Target();
  public:
    static std::unique_ptr<Target> instance();
    ~Target();
  public:
    void set_name(const char *name);
    const char* get_name() const;
    void set_rect(float x, float y, float w, float h);
    Rect get_rect() const;
  protected:
    Rect rect_;
    std::string name_;
  };
} // namespace agile

#endif // __AGILE_TARGET_H_