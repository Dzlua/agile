/*****************************************************\
* Copyright (c) 2019 The Agile Authors. All rights reserved.
  Use of this source code is governed by a BSD-style license that can be
  found in the LICENSE file.

* Author:         dzlua - https://github.com/dzlua/
* Email:          505544956@qq.com
* FileName:       base.hpp
* Create Time:    2019/06/11 14:58:45
* Description:    /
\****************************************************/
#ifndef AGILE_MATH_HPP_
#define AGILE_MATH_HPP_

#include <string>

#include "osplatformutil.h"

#ifdef I_OS_WIN
#include <windows.h>
#endif

namespace agile {
namespace base {
  inline float to_radian(float angle) {
		return angle * 0.0174532925f;
	}

	inline float to_degrees(float radian) {
		return radian * 57.29577951f;
	}

  bool module_file_name(std::string &file_name) {
    #ifdef I_OS_WIN
      char buf[512] = {0};
      if (::GetModuleFileNameA(::GetModuleHandleA(0), buf, 512)) {
        file_name = buf;
        return true;
      }
    #else
    #endif
  
    file_name.clear();
    return false;
  }
} // end namespace base
} // end namespace agile

#endif // end define AGILE_MATH_HPP_