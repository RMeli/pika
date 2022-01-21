//  Copyright (c) 2020 John Biddiscombe
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <pika/config.hpp>
#if defined(PIKA_HAVE_CUDA)
#include <pika/async_cuda/custom_lapack_api.hpp>
#include <pika/errors/exception.hpp>

#include <string>

namespace pika::cuda::experimental {
    namespace detail {
        PIKA_EXPORT const char* cusolver_get_error_string(
            cusolverStatus_t error);
    }    // namespace detail

    struct cusolver_exception : pika::exception
    {
        PIKA_EXPORT cusolver_exception(
            const std::string& msg, cusolverStatus_t err);
        PIKA_EXPORT cusolverStatus_t get_cusolver_errorcode() const noexcept;

    protected:
        cusolverStatus_t err_;
    };

    PIKA_EXPORT cusolverStatus_t check_cusolver_error(cusolverStatus_t err);
}    // namespace pika::cuda::experimental
#endif
