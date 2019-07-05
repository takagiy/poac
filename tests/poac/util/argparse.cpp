#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include <string>
#include <vector>

#include <poac/util/argparse.hpp>


// bool use(SinglePassRange& rng, T... args)
BOOST_AUTO_TEST_CASE( poac_util_argparse_use_test )
{
    using poac::util::argparse::use;

    std::vector<std::string> temp{ "-h", "--help", "--flag" };
    BOOST_CHECK( use(temp, "-h") );
    BOOST_CHECK( use(temp, "-h", "--help") );
    BOOST_CHECK( use(temp, "-h", "--help", "--no") );
    BOOST_CHECK( !use(temp, "-n", "--no") );
}

// bool use_rm(SinglePassRange& rng, T... args)
BOOST_AUTO_TEST_CASE( poac_util_argparse_use_rm_test )
{
    using poac::util::argparse::use;
    using poac::util::argparse::use_rm;

    std::vector<std::string> temp{ "-h", "--help", "--flag" };
    BOOST_CHECK( use_rm(temp, "-h") );
    BOOST_CHECK( !use(temp, "-h") );
    BOOST_CHECK( use(temp, "--help") );
    BOOST_CHECK( use(temp, "--flag") );

    temp = { "-h", "--help", "--flag" };
    BOOST_CHECK( use_rm(temp, "-h", "--help") );
    BOOST_CHECK( !use(temp, "-h", "--help") );
    BOOST_CHECK( use(temp, "--flag") );

    temp = { "-h", "--help", "--flag" };
    BOOST_CHECK( !use_rm(temp, "-n", "--no") );
    BOOST_CHECK( use(temp, "-h", "--help", "--flag") );
}

// 1. std::optional<std::string> use_get(SinglePassRange& rng, T arg)
// 2. std::optional<std::string> use_get(SinglePassRange& rng, T arg1, T arg2)
BOOST_AUTO_TEST_CASE( poac_util_argparse_use_get_test )
{
    using poac::util::argparse::use_get;

    std::vector<std::string> temp{ "-o", "output.o", "--flag" };

    auto res = use_get(temp, "-o"); // 1
    BOOST_CHECK( static_cast<bool>(res) );
    BOOST_CHECK( *res == "output.o" );

    temp = { "-h", "--help", "--flag" };
    res = use_get(temp, "-o");
    BOOST_CHECK( !static_cast<bool>(res) );

    res = use_get(temp, "-o", "--output"); // 2
    BOOST_CHECK( static_cast<bool>(res) );
    BOOST_CHECK( *res == "output.o" );

    res = use_get(temp, "--no", "-o");
    BOOST_CHECK( static_cast<bool>(res) );
    BOOST_CHECK( *res == "output.o" );

    temp = { "-h", "--help", "--flag" };
    res = use_get(temp, "-o", "--output");
    BOOST_CHECK( !static_cast<bool>(res) );
}
