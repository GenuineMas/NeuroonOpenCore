#include "logger.h"

void configure_logger() {

#ifdef CAPTURE_LOGS_FROM_EASYLOGGING
	el::Helpers::installLogDispatchCallback<callback>("dummy");
#endif
	el::Loggers::addFlag(el::LoggingFlag::ColoredTerminalOutput);
	el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime %level %logger | %func@%loc\n%msg");
	CLOG(INFO, "default") << "Logger initialized";
}
