//  Copyright (c) 2007-2015 Hartmut Kaiser
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// #pragma once to silence inshpect check for #pragma once

#include <pika/config/compiler_specific.hpp>

// re-enable warnings about dependent classes not being exported from the dll
#if defined(PIKA_MSVC_WARNING_PRAGMA)
# pragma warning(pop)
#endif
