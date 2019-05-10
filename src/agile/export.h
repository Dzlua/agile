/*****************************************************\
* Copyright (c) 2019 The Agile Authors. All rights reserved.
  Use of this source code is governed by a BSD-style license that can be
  found in the LICENSE file.

* Author:         dzlua - https://github.com/dzlua/
* Email:          505544956@qq.com
* FileName:       export.h
* Create Time:    2019/05/10 15:51:12
* Description:    /
\****************************************************/
#ifndef __AGILE_EXPORT_H_
#define __AGILE_EXPORT_H_

#define AGILE_USE_SHARED

#if defined(_WIN32)
#   ifdef AGILE_USE_SHARED
#       ifdef AGILE_EXPORTS
#           define AGILE_API __declspec(dllexport)
#       else
#           define AGILE_API __declspec(dllimport)
#       endif
#   else
#       define AGILE_API
#   endif
#elif defined(__GNUC__) && ((__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 3))
#   ifdef AGILE_USE_SHARED
#       ifdef AGILE_EXPORTS
#           define AGILE_API __attribute__((visibility("default")))
#       else
#           define AGILE_API
#       endif
#   else
#       define AGILE_API
#   endif
#else
#   define AGILE_API      
#endif

#endif // __AGILE_EXPORT_H_