//  Copyright (c) 2014-2015 Hartmut Kaiser
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <pika/init.hpp>
#include <pika/thread.hpp>

#include <iostream>
#include <string>
#include <vector>

#include "foreach_tests_projection.hpp"

///////////////////////////////////////////////////////////////////////////////
template <typename IteratorTag, typename Proj>
void test_for_each()
{
    using namespace pika::execution;

    test_for_each_seq(IteratorTag(), Proj());

    test_for_each(seq, IteratorTag(), Proj());
    test_for_each(par, IteratorTag(), Proj());
    test_for_each(par_unseq, IteratorTag(), Proj());

    test_for_each_async(seq(task), IteratorTag(), Proj());
    test_for_each_async(par(task), IteratorTag(), Proj());
}

template <typename Proj>
void for_each_test()
{
    test_for_each<std::random_access_iterator_tag, Proj>();
    test_for_each<std::forward_iterator_tag, Proj>();
}

///////////////////////////////////////////////////////////////////////////////
template <typename IteratorTag, typename Proj>
void test_for_each_exception()
{
    using namespace pika::execution;

    // If the execution policy object is of type vector_execution_policy,
    // std::terminate shall be called. therefore we do not test exceptions
    // with a vector execution policy
    test_for_each_exception_seq(IteratorTag(), Proj());

    test_for_each_exception(seq, IteratorTag(), Proj());
    test_for_each_exception(par, IteratorTag(), Proj());

    test_for_each_exception_async(seq(task), IteratorTag(), Proj());
    test_for_each_exception_async(par(task), IteratorTag(), Proj());
}

template <typename Proj>
void for_each_exception_test()
{
    test_for_each_exception<std::random_access_iterator_tag, Proj>();
    test_for_each_exception<std::forward_iterator_tag, Proj>();
}

///////////////////////////////////////////////////////////////////////////////
template <typename IteratorTag, typename Proj>
void test_for_each_bad_alloc()
{
    using namespace pika::execution;

    // If the execution policy object is of type vector_execution_policy,
    // std::terminate shall be called. therefore we do not test exceptions
    // with a vector execution policy
    test_for_each_bad_alloc_seq(IteratorTag(), Proj());

    test_for_each_bad_alloc(seq, IteratorTag(), Proj());
    test_for_each_bad_alloc(par, IteratorTag(), Proj());

    test_for_each_bad_alloc_async(seq(task), IteratorTag(), Proj());
    test_for_each_bad_alloc_async(par(task), IteratorTag(), Proj());
}

template <typename Proj>
void for_each_bad_alloc_test()
{
    test_for_each_bad_alloc<std::random_access_iterator_tag, Proj>();
    test_for_each_bad_alloc<std::forward_iterator_tag, Proj>();
}

///////////////////////////////////////////////////////////////////////////////
struct projection_square
{
    template <typename T>
    T operator()(T const& val) const
    {
        return val * val;
    }
};

int pika_main(pika::program_options::variables_map& vm)
{
    unsigned int seed = (unsigned int) std::time(nullptr);
    if (vm.count("seed"))
        seed = vm["seed"].as<unsigned int>();

    std::cout << "using seed: " << seed << std::endl;
    std::srand(seed);

    for_each_test<pika::parallel::util::detail::projection_identity>();
    for_each_exception_test<
        pika::parallel::util::detail::projection_identity>();
    for_each_bad_alloc_test<
        pika::parallel::util::detail::projection_identity>();

    for_each_test<projection_square>();
    for_each_exception_test<projection_square>();
    for_each_bad_alloc_test<projection_square>();

    return pika::finalize();
}

int main(int argc, char* argv[])
{
    // add command line option which controls the random number generator seed
    using namespace pika::program_options;
    options_description desc_commandline(
        "Usage: " PIKA_APPLICATION_STRING " [options]");

    desc_commandline.add_options()("seed,s", value<unsigned int>(),
        "the random number generator seed to use for this run");

    // By default this test should run on all available cores
    std::vector<std::string> const cfg = {"pika.os_threads=all"};

    // Initialize and run pika
    pika::init_params init_args;
    init_args.desc_cmdline = desc_commandline;
    init_args.cfg = cfg;

    PIKA_TEST_EQ_MSG(pika::init(pika_main, argc, argv, init_args), 0,
        "pika main exited with non-zero status");

    return 0;
}
