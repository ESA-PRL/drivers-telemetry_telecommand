#include <boost/test/unit_test.hpp>
#include <data_handling/Dummy.hpp>

using namespace data_handling;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    data_handling::DummyClass dummy;
    dummy.welcome();
}
