#include "pocotest.hpp"

void POCOLoggingTest(Arguments args, Options options) {
    Poco::AutoPtr<Poco::ConsoleChannel> consoleChannel(new Poco::ConsoleChannel);

    // Get the root logger and set the channel
    Poco::Logger& logger = Poco::Logger::root();
    logger.setChannel(consoleChannel);

    // Log messages with different severity levels
    logger.information("This is an informational message");
    logger.warning("This is a warning message");
    logger.error("This is an error message");
}