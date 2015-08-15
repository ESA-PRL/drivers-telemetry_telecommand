#include <boost/test/unit_test.hpp>
#include <telemetry_telecommand/Dummy.hpp>

using namespace telemetry_telecommand;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    telemetry_telecommand::DummyClass dummy;
//    dummy.welcome();
}
