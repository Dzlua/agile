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
#else
  #include <unistd.h>
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
    char buf[1024] = { 0 };

    #ifdef I_OS_WIN
      if (::GetModuleFileNameA(::GetModuleHandleA(0), buf, sizeof(buf))) {
        file_name = buf;
        return true;
      }
    #else
      int len = readlink("/proc/self/exe", buf, sizeof(buf));
      if (len > 0 && len < sizeof(buf)) {
        file_name = buf;
        return true;
      }
    #endif
  
    file_name.clear();
    return false;
  }
} // end namespace base
} // end namespace agile

#endif // end define AGILE_MATH_HPP_