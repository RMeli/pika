//  Copyright (c) 2007-2017 Hartmut Kaiser
//  Copyright (c)      2017 Shoshana Jakobovits
//  Copyright (c) 2010-2011 Phillip LeBlanc, Dylan Stark
//  Copyright (c)      2011 Bryce Lelbach
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <pika/config.hpp>
#include <pika/assert.hpp>
#include <pika/threading_base/thread_pool_base.hpp>

#include <cstddef>
#include <string>

namespace pika { namespace detail {
    PIKA_NORETURN PIKA_EXPORT void assertion_handler(
        pika::assertion::source_location const& loc, const char* expr,
        std::string const& msg);
#if defined(PIKA_HAVE_APEX)
    PIKA_EXPORT bool enable_parent_task_handler();
#endif
#if defined(PIKA_HAVE_VERIFY_LOCKS)
    PIKA_EXPORT void registered_locks_error_handler();
    PIKA_EXPORT bool register_locks_predicate();
#endif
    PIKA_EXPORT threads::thread_pool_base* get_default_pool();
    PIKA_EXPORT threads::mask_cref_type get_pu_mask(
        threads::topology& topo, std::size_t thread_num);
}}    // namespace pika::detail