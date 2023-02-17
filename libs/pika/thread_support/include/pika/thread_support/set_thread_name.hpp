//  Copyright (c) 2007-2013 Hartmut Kaiser
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <pika/config.hpp>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#include <windows.h>

namespace pika::detail {
    PIKA_EXPORT void set_thread_name(char const* /*threadName*/, DWORD /*dwThreadID*/ = DWORD(-1));
}    // namespace pika::detail

#else

namespace pika::detail {
    inline void set_thread_name(char const* /*thread_name*/) {}
}    // namespace pika::detail

#endif
