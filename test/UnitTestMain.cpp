#include <boost/version.hpp>
#define BOOST_TEST_MODULE thrift
#if BOOST_VERSION >= 103400
#include <boost/test/included/unit_test.hpp>
#else
// Use the deprecated header with old boost versions.
#include <boost/test/included/unit_test_framework.hpp>
#endif
